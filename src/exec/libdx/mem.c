/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>

#if defined(HAVE_WINDOWS_H)
#include <windows.h>
#endif

#if defined(HAVE_UNISTD_H)
#include <unistd.h>
#endif

#if defined(HAVE_ERRNO_H)
#include <errno.h>
#endif

#include <string.h>
#include <dx/dx.h>
#include "../dpexec/dxmain.h"

/* prototypes - not in a system header file because these are only
 *  called in a couple places, mostly in memory.c but also from the
 *  exec, and they are basically private routines which shouldn't
 *  be exposed.
 */
Error _dxfsetmem(ulong limit);
Error _dxfinitmem();
Pointer _dxfgetmem(Pointer base, ulong size);
Error DXsyncmem();
Error DXmemfork(int);

/* moved out of memstats conditional section.  i'm going to use this to tell
 * what kind of memory we are using - shared or dataseg - so when we are
 * called to extend the segment we can do the right thing.  it's getting 
 * more complicated to tell which one we are using - MP or UP, small vs
 * large on ibm6000, environment variable override, etc.
 */
typedef enum memtype {
    MEM_NOTINIT,       /* memory init routines not called yet */
    MEM_DATASEG,       /* data segment extended with sbrk() */
    MEM_SHARED         /* separate shared memory segment obtained */
} Memtype;

static int num_sbrk_calls = 0;
static int num_failed_calls = 0;

#define MAX_CHUNKS 256
static Pointer alloc_addr_start[MAX_CHUNKS];
static Pointer alloc_addr_end[MAX_CHUNKS];
static int alloc_segments[MAX_CHUNKS];
static int alloc_chunks;

/* some compilers don't let you do math on void *, so cast
 * them to char * first
 */
#define ADD_INT(a, b)  ((Pointer)((byte *)(a) + (b)))
#define SUB_INT(a, b)  ((Pointer)((byte *)(a) - (b)))
#define SUB_PTR(a, b)  ((Pointer)((byte *)(a) - (byte *)(b)))
#define ERR_PTR        ((Pointer)(-1))


/* routines common to all archs - just stubs now 
 */
Error _dxfinitmem() { return OK; }
Error DXsyncmem() { return OK; }
/* is this called from anywhere? */
void _dxfcleanup_mem() { }


#if linux

#define memroutines

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/sysmacros.h>
#include <sys/param.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <fcntl.h>

/* no resizing; allocate enough space initially. 
 *
 * the address space needs to be contiguous, so allow system to pick
 * addr of first segment and then use explicit addresses after that.
 *
 * on solaris, by default the system picks the last available segment, so
 * if multiple segments are necessary, request them in decreasing memory
 * address order - as long as they really are contiguous, it's ok.
 *
 */

Error
_dxfsetmem(ulong limit)
{
    return OK;
}

extern int end;   /* filled in by linker */

Pointer
_dxfgetmem(Pointer base, ulong size)
{
#if 1
    Pointer x = (Pointer)malloc(size);
    if (! x)
    {
        DXSetError(ERROR_NO_MEMORY, "Cannot create a %d byte arena\n", size);
	return NULL;
    }
    return x;
#else
    Pointer x = (Pointer)sbrk(size);

    if (x == ERR_PTR)
        num_failed_calls++;
    else if (num_sbrk_calls < MAX_CHUNKS) {
        alloc_addr_start[num_sbrk_calls] = x;
        alloc_addr_end[num_sbrk_calls] = ADD_INT(x, size);
        alloc_chunks++;
    }
    num_sbrk_calls++;


    if (x == ERR_PTR) {
#if !(defined(cygwin) || defined (macos))
        unsigned int i;
#endif
        x = (Pointer)sbrk(0);
#if defined(cygwin) || defined (macos)
        DXSetError(ERROR_NO_MEMORY,
                "cannot expand the data segment by %u bytes", n);
#else
        i = (unsigned int)((char *)x - (char *)&end);
        DXSetError(ERROR_NO_MEMORY,
        "cannot expand the data segment by %u bytes, current size is %u bytes",
                   size, i);
#endif
        return NULL;
    } else
        return x;
#endif
}

#endif   /* linux */

#if !defined(memroutines)
#define memroutines

/* Still need to write shared memory routines */

void *sh_base = NULL;   /* starting virtual address */

Error _dxfsetmem(ulong limit)
{
    sh_base = malloc(limit);
    if (sh_base == NULL) {
	DXErrorReturn(ERROR_NO_MEMORY, "getmem can't commit memory");
    }
    else {
	/*   memset(sh_base, 0, limit);   */
	return OK;
    }
}

Pointer _dxfgetmem(Pointer base, ulong size)
{
    if (!base)	
	base = (Pointer) sh_base;

    return base;
}
#endif /* defined(macos)|| defined(intelnt) || defined(WIN32) */


/* the default case for all platforms which aren't MP or
 * aren't using shared memory.
 */


#define MEMSTATS 1  /* change to 0 to comment out this code.  (needs a
                     * corresponding change in usage.m if you do.)
		     */

/* the NT linker doesn't define 'end' as the end of the data segment, 
 * so the calculations about the size of the data segment can't be done 
 * on the NT.  thus this section is disabled on that platform.
 */
#if defined(intelnt) || defined(WIN32)
#if defined(MEMSTATS)
#undef MEMSTATS
#endif
#define MEMSTATS 0
#endif

#if MEMSTATS   /* memory stats */

/* information about what was allocated & where.  it's hard to print this
 * out at startup time because the memory arenas aren't initialized yet and 
 * calling printf() can cause malloc to be called internally by the libc
 * routine for formatting, which on some architectures is caught and replaced
 * by a call to the dx memory manager, which isn't initialized yet...
 * so save it in global structs and you can look at it with the debugger
 * in case something bad happens.  or print it out with Usage("memory info");
 */

#if !defined(cygwin) && !defined(macos)
extern int end;   /* filled in by linker */
#endif

#define min(a,b)  ((a) < (b) ? (a) : (b))

/* public */
void DXPrintMemoryInfo()
{
    uint i;
    ulong total;

    DXMessage("using data segment for arenas; sbrk called %d times", 
	  num_sbrk_calls);
    if (num_failed_calls > 0) {
	DXMessage("sbrk failed %d times", num_failed_calls);
	num_sbrk_calls -= num_failed_calls;
    }
    for (i=0; i<min(num_sbrk_calls, MAX_CHUNKS); i++)
	DXMessage("sbrk %d returned 0x%08x, %lu bytes allocated", 
		  i+1, alloc_addr_start[i], 
		  (ulong)SUB_PTR(alloc_addr_end[i], alloc_addr_start[i]));
	
#if !defined(cygwin) && !defined(macos)
    DXMessage("end address = 0x%08x, data segment extended by %lu bytes", 
		  alloc_addr_end[i-1],
		  (ulong)SUB_PTR(alloc_addr_end[i-1], &end));
#endif
    return;
}
#endif  /* memory stats */

