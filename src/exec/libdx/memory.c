/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#define MEMALLOC_DEBUG 1

#include <dxconfig.h>
#include <stdlib.h>
#include <assert.h>

#define DX_MEMORY_C

#include <stdio.h>

#define NO_STD_H
#include <dx/dx.h>
#if defined(HAVE_UNISTD_H)
#include <unistd.h>
#endif

#include <string.h>

#if defined(macos)
extern mach_port_t host_self(void);
#endif

#if DXD_HAS_RLIMIT
#include <sys/time.h>
#include <sys/resource.h>
#endif

extern void _dxfemergency(void);

#define K   *((ulong)1024)
#define MEG K K
#define GIG K K K

static lock_type lock;
static ulong _maxmem = 500 MEG;
static ulong _memused = 0;
static int use_lock = 1;
static int locked_by = -1;
static int nalloc = 0;

struct memblk
{
    struct memblk *last;
    struct memblk *next;
    ulong size;
    int tag;
} *freelist = NULL;

static int all_malloc = 1;
static int set_all_malloc(int s)
{
    int os = all_malloc;
    all_malloc = s;
    return os;
};

int
found_memory_problem()
{
    fprintf(stderr, "memory problem!\n");
}

void
aprint(int how)
{
    struct memblk *m; int i; ulong sum = 0;
    struct memblk *saved_freelist;
    FILE *f = NULL;
    int my_lock = 0;

    if (how == 2)
    {   
	pid_t p = getpid();
	char tmp[256];
	sprintf(tmp, "/tmp/dx.datadump.%d", (int)p);
        f = fopen(tmp, "w");
	if (!f)
	{
	    fprintf(stderr, "could not open file %s\n", tmp);
	    f = stderr;
	}
    }

    if (use_lock)
    {
	DXlock(&lock, 1);
	my_lock = 1;
	use_lock = 0;
	locked_by = DXGetThreadPid();
    }

    saved_freelist = freelist;
    freelist = NULL;

    DXMessage("%ld of %ld bytes allocated\n", _memused, _maxmem);
    for (i = 0, m = saved_freelist; i < nalloc && m; m = m->next, i++)
    {
        if (how == 1)
            DXMessage(" 0x%016lx 0x%016lx (0x%016lx 0x%016lx) %ld\n",
                m, m+1, m->last, m->next, m->size);
	else if (how == 2)
            fprintf(f, " 0x%016lx 0x%016lx (0x%016lx 0x%016lx) %ld\n",
                m, m+1, m->last, m->next, m->size);
        m->tag = 0;
        sum += m->size;
    }

    if (f) fclose(f);

    if (m) DXMessage("XXXXXXXXXXX linking corruption! XXXXXXXXXXXXXXX\n");

    for (m = freelist; m; m = freelist)
    {
        freelist = m->next;
        m->next = saved_freelist;
        m->last = NULL;
        if (saved_freelist)
            saved_freelist->last = m;
        saved_freelist = m;

    }

    for (m = freelist; m; m = m->next)
        m->tag = 0;

    freelist = saved_freelist;

    if (my_lock)
    {
	use_lock = 1;
	locked_by = -1;
	DXunlock(&lock, 2);
    }
}

int
acheck()
{
    Error err = OK;

#if 0
    ulong sum = 0;

    if (freelist)
    {
        struct memblk *m, *l; int i;

        for (i = 0, m = freelist; i < nalloc && m; m = m->next, i++)
        {
            l = m;
            sum += m->size;
        }

        if (sum != _memused)
        {
            found_memory_problem();
            err = ERROR;
        }

        if (m)
        {
            found_memory_problem();
            err = ERROR;
        }

        for (i = 0, m = l; i < nalloc && m; m = m->last, i++);
        if (m)
        {
            found_memory_problem();
            err = ERROR;
        }
    }
#endif

    return err;
}

 

#if MEMALLOC_DEBUG
static Pointer find_allocation = (Pointer)0x4;
#endif

static int total_allocated = 0, high_water = 0;

static void
memstats(long n)
{
    total_allocated += n;
    if (total_allocated > high_water) high_water = total_allocated;
}

int
_dxf_initmemory(void)
{
    DXcreate_lock(&lock, "lock");
    return OK;
}

static int trace = 0;
static int every = 0;
Error DXTraceAlloc(int t)
{
    if (every++ < trace) {
	if (trace != t)
	    trace = t;
	return OK;
    }

    if (!acheck())
	return ERROR;

    if (trace != t)
	trace = t;

    every = 0;
    return OK;
}

/* new code */

/*
 * request the memory manager to call the callback routine with one or more
 *  of the following types of memory blocks:  free, allocated, private.
 */
Error
DXDebugAlloc(int arena, int blocktype, MemDebug m, Pointer p)
{
    fprintf(stderr, "DXDebugAlloc has been removed\n");
    return OK;
}

void
DXPrintAlloc(int how)
{
    aprint(2);
}

/*
 *  Scavengers
 */

int nscavengers = 0;
static Scavenger scavengers[10];

#define NORECURSE 0

int scavenging = 0;

Scavenger DXRegisterScavenger(Scavenger s)
{
    if (nscavengers >= 10)
        return NULL;
    scavengers[nscavengers++] = s;
    return s;
}

Error
_dxfscavenge(ulong n)
{
    int i; struct memblk *saved_freelist, *m;

    use_lock = 0;
    scavenging = 1;

    DXMessage("scavenging memory");

    saved_freelist = freelist;
    freelist = NULL;

    for (i=0; i<nscavengers; i++)
        if (scavengers[i](n))
            break;

    for (m = freelist; m; m = freelist)
    {
	freelist = m->next;
        m->next = saved_freelist;
	m->last = NULL;
	if (saved_freelist)
	    saved_freelist->last = m;
	saved_freelist = m;

    }

    freelist = saved_freelist;

    scavenging = 0;
    use_lock = 1;

    return ERROR;
}


static ulong alloc_size(Pointer x)
{
    struct memblk *m = ((struct memblk *)x) - 1;
    return m->size;
}

ulong
DXAvailableMemory()
{
    if (_memused > _maxmem) return 0;
    else return _maxmem - _memused;
}

#if MEMALLOC_DEBUG
static ulong alloc_knt = 0, alloc_target = 0;
#endif

Pointer
DXAllocate(unsigned int n)
{
    Pointer x;
    int ok_to_allocate;
    int my_lock = 0;

    if (use_lock && locked_by != DXGetThreadPid())
    {
	DXlock(&lock, 3);
	my_lock = 1;
	locked_by = DXGetThreadPid();
    }

#if MEMALLOC_DEBUG
    alloc_knt++;
    if (alloc_target && alloc_knt >= alloc_target)
        found_memory_problem();
#endif

    /*
     * If we are scavenging, then we can't limit allocations or we may get
     * into infinite recursion
     */
    if (scavenging || (_memused + n) <= _maxmem)
        ok_to_allocate = 1;
    else
    {
	_dxfscavenge(n);
	ok_to_allocate = ((_memused + n) <= _maxmem);
    }

    if (! ok_to_allocate)
        x = NULL;
    else
    {
        struct memblk *m = (struct memblk *)malloc(n + sizeof(struct memblk));
	m->tag = 1;
	m->size = n;
	m->last = NULL;
	
	m->next = freelist;
	if (freelist) freelist->last = m;
	freelist = m;
	x = (Pointer)(m+1);
	_memused += n;
	nalloc ++;
    }

    if (my_lock)
    {
	locked_by = -1;
	DXunlock(&lock, 4);
    }

    if (!x)
	if (DXGetError() == ERROR_NONE)
	    DXSetError(ERROR_NO_MEMORY, "allocate of %d bytes failed", n);

#if MEMALLOC_DEBUG
    if (x == find_allocation)
	found_memory_problem();
#endif

    return x;
}

Pointer 
DXReAllocate(Pointer x, unsigned int n)
{
    Pointer y;

#if MEMALLOC_DEBUG
    if (x == find_allocation)
	found_memory_problem();
#endif

    y = DXAllocate(n);

    if (x)
    {
	ulong sz;

	if (trace && !DXTraceAlloc(trace))
	    return NULL;

  	sz = (alloc_size(x) < n) ? alloc_size(x) : n;
	memcpy(y, x, sz);

	DXFree(x);
    }

#if MEMALLOC_DEBUG
    if (y == find_allocation)
	found_memory_problem();
#endif

    return y;
}


/* malloc and free get redefined depending on how the MALLOC_xxx variables */
/* get set. See comments at beginning of this file.                        */

#if MEMALLOC_DEBUG
static ulong free_knt = 0, free_target = 0;
#endif

static ulong free_byte_count;
void _dxf_init_freed_size() {free_byte_count = 0;}
ulong _dxf_get_freed_size() {return free_byte_count;}


Error
DXFree(Pointer x)
{
#if MEMALLOC_DEBUG
    if (x == find_allocation)
	found_memory_problem();
    if (trace && !DXTraceAlloc(trace))
	return ERROR;
#endif

    if (x)
    {
       
	if (use_lock || locked_by != DXGetThreadPid())
	    DXlock(&lock, 5);

#if MEMALLOC_DEBUG
	free_knt++;
	if (free_target && free_knt >= free_target)
	    found_memory_problem();
#endif

        struct memblk *m = ((struct memblk *)x) - 1;

	free_byte_count += m->size;

	_memused -= m->size;
	if (m->next) m->next->last = m->last;
	if (m->last) m->last->next = m->next;
	if (m == freelist) freelist = m->next;
	free(m);

	nalloc --;

#if MEMALLOC_DEBUG
	if (use_lock && !acheck())
	    found_memory_problem();
#endif

	if (use_lock || locked_by != DXGetThreadPid())
	    DXunlock(&lock, 6);
    }
    return OK;
}

Pointer
DXAllocateZero(unsigned int n)
{
    Pointer x;

    x = DXAllocate(n);
    if (!x)
	return NULL;

    memset(x, 0, n);

    return x;
}

_dxf_set_max_memory_size(int s)
{
    if (s == 0)
    {
        char *a = getenv("DX_MEMORY_SIZE");
	if (a) s = atoi(a);
	else s = 2048;
    }
    _maxmem = ((ulong)s) MEG;
}

