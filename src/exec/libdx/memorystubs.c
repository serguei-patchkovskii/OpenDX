/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>


#define DX_MEMORY_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dx/dx.h>
#if defined(HAVE_UNISTD_H)
#include <unistd.h>
#endif

Error DXsyncmem() { return OK; }
int DXmemfork(int i) { 
#if defined(HAVE_FORK)
	return fork();
#else
	return -1;
#endif
}
void _dxfcleanup_mem() { }


int _dxf_initmemory() { return OK; }

Error DXmemsize(ulong size) { return OK; }

Error DXSetMemorySize(ulong size, int ratio) { return OK; }

/* we can make this work for the pvs - there are #defines for it */
Error DXGetMemorySize(ulong *sm, ulong *lg)
{
    if (sm) *sm = 0;
    if (lg) *lg = 0;
    return OK;
}

/* same here */
Error DXGetMemoryBase(Pointer *sm, Pointer *lg)
{
    if (sm) *sm = 0;
    if (lg) *lg = 0;
    return OK;
}

Error DXTraceAlloc(int t) { return OK; }

Error DXDebugAlloc(int arena, int blocktype, MemDebug m, Pointer p)
{ return OK; }

void DXPrintAlloc(int how) { }

void DXFindAlloc(Pointer f) { }

void DXFoundAlloc(void) { }

Scavenger DXRegisterScavenger(Scavenger s) { return s; }

Error _dxfscavenge(unsigned int n) { return OK; }

int _dxflscavenge(unsigned int n) { return OK; }

Pointer
DXAllocate(unsigned int n)
{
    Pointer p;
    if (n==0)
	n++;
    p = (Pointer)malloc(n);
    if (!p)
	DXSetError(ERROR_NO_MEMORY, "#13000");
    return p;
}

Pointer
DXAllocateZero(unsigned int n)
{
    Pointer p;
    if (n==0)
	n++;
    p = (Pointer)malloc(n);
    if (!p)
	DXSetError(ERROR_NO_MEMORY, "#13000");
    memset(p, '\0', n);
    return p;
}

Pointer 
DXReAllocate(Pointer x, unsigned int n)
{
    Pointer p;
    if (n==0)
	n++;
    if (x == NULL) {
	p = malloc(n);
	if (!p)
	    DXSetError(ERROR_NO_MEMORY, "#13000");
	return p;
    }
    p = (Pointer)realloc(x, n);
    if (!p)
	DXSetError(ERROR_NO_MEMORY, "#13000");
    return p;
}

Error
DXFree(Pointer x)
{
    if (x != NULL)
	free(x);
    return OK;
}

void
DXInitMaxFreedBlock()
{
}

ulong
DXMaxFreedBlock()
{
    return 0;
}

void DXPrintMemoryInfo()
{
}
