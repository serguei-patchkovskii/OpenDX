/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
/*
 * $Header: /cvsroot/opendx2/dx/src/exec/dpexec/cache.h,v 1.7 2004/06/09 16:14:27 davidt Exp $
 */

#include <dxconfig.h>


#ifndef _CACHE_H_
#define _CACHE_H_

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

#if 0
These access methods are specifically used to operate on dictionary entries
that are associated with the recipe cache. These are the only access methods
which will be available from the modules.
#endif

#include "d.h"
#include "graph.h"
#include "crc.h"

#if 0
#define EXTAG(tag) ((tag) | 0x80000000)
#else
#define EXTAG(tag) (tag)
#endif

typedef struct pathtag
{
    ModPath     mod_path;		/* module path			*/
    EXCRC       reccrc;                 /* cache tag                    */
    int         outnbr;                 /* nth output of module         */
    int         modnbr;                 /* nth instance of module       */
    int         entry_inuse;
} pathtag;

int     _dxf_ExCacheInit(void);
EXCRC   _dxf_ExGenCacheTag(char *function, int key, int n, EXCRC *in);
int     _dxf_ExCacheInsert(gvar *obj);
int     _dxf_ExCacheDelete(EXCRC key);
gvar   *_dxf_ExCacheSearch(EXCRC key);
Error   _dxf_ExCacheFlush(int all);
int     _dxf_ExCacheInsertRemoteTag (int fd, int swap);
int     _dxf_ExCacheDeleteRemoteTag (int fd, int swap);
int     _dxf_ExCacheListDeleteRemoteTag(int fd, int swap);
extern EXDictionary _dxd_exCacheDict; /* defined in cache.c */

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* _CACHE_H_ */
