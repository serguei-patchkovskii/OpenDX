/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

#include <stdio.h>

#if defined(HAVE_UNISTD_H)
#include <unistd.h>
#endif

#if defined(HAVE_SYS_STAT_H)
#include <sys/stat.h>
#endif

#include "ControlPanel.h" 
#include "DropSite.h"
#include "DXDropSite.h" 
#include "DXApplication.h"
#include "Network.h"
#include "DXStrings.h"
#include "WarningDialogManager.h"

#if defined(HAVE_NETDB_H)
#include <netdb.h>
#endif

#if defined(NEEDS_GETHOSTNAME_DECL)
extern "C" int gethostname(char *address, int address_len);
#endif

//static char *header_fmt = "%s:%d, net length = %d, cfg length = %d\n";
//static char *header_fmt = "%d, net length = %d, cfg length = %d\n";
static char *header_fmt = "%[^:]:%d, net length = %d, cfg length = %d";

DXDropSite::DXDropSite (bool intraExecutable): DropSite()
{
    this->intraExecutable = intraExecutable;
}

DXDropSite::~DXDropSite() { }


//
// Kick off the recieving end of the transfer using .net and .cfg files.  
//
//bool DXDropSite::transfer(char *type, XtPointer value, unsigned long len, int x, int y)
//{
//FILE            *netf;
//FILE            *cfgf;
//char            netfilename[1024];
//char            cfgfilename[1024];
//int             header_len;
//int             net_len;
//int             cfg_len;
//char            *buf = (char *)value; // you want to read 1 byte past the end?
//char            *newline;
//char		draghost[MAXHOSTNAMELEN], hostname[MAXHOSTNAMELEN];
//int		dragpid;
//Boolean		ret;
//
//
//    ASSERT (buf);
//    if(sscanf(buf, header_fmt, draghost, &dragpid, &net_len, &cfg_len) < 4)
//    {
//        WarningMessage("DXDropSite:transfer drop failed");
//        return false;
//    }
//    newline = strchr(buf, '\n');
//    header_len = newline - buf;
//
//    //
//    // prevent dnd between programs... silly goal?  We set intraExecutable==true
//    // for dnd from vpe to c.p.   The proper way to implement this is with
//    // root window properties.  The drag source is setting HOST_NAME and PROCESS.
//    // It could also set LENGTH and 1 other to handle the entire header or even
//    // split the entire transfer into logical peices.
//    //
//    if (this->intraExecutable) 
//    {
//        Boolean mismatch = false;
//        gethostname (hostname, sizeof(hostname));
//        if (strcmp(hostname, draghost)) mismatch = true;
//        else if (dragpid != getpid()) mismatch = true;
//	if (mismatch) return false;
//    }
//
//    //
//    // Create the net file
//    //
//    sprintf(netfilename, "%s/dx%d.net", theDXApplication->getTmpDirectory(), getpid());
//    netf = fopen(netfilename, "w");
//    if (!netf) {
//        WarningMessage("DXDropSite:no file write permission");
//	return false;
//    }
//
//    fwrite(&(buf[header_len]), sizeof(char), (unsigned int)net_len, netf);
//    fclose(netf);
//
//    //
//    // Create the cfg file
//    //
//    if(cfg_len > 0)
//    {
//        sprintf(cfgfilename, "%s/dx%d.cfg", theDXApplication->getTmpDirectory(), getpid());
//        cfgf = fopen(cfgfilename, "w");
//        fwrite(&(buf[header_len+net_len]),
//            sizeof(char), (unsigned int)cfg_len, cfgf);
//        fclose(cfgf);
//    } else
//	cfgfilename[0] = '\0';
//
//    Network *tmpnet = theDXApplication->newNetwork(true);
//    if ((cfgfilename)&&(cfgfilename[0]))
//        ret = tmpnet->readNetwork(netfilename, cfgfilename, true);
//    else
//        ret = tmpnet->readNetwork(netfilename, NULL, true);
//
//    List *tmppanels = NUL(List*);
//    if (ret) {
//	tmppanels = tmpnet->getNonEmptyPanels();
//	ret = this->mergeNetElements (tmpnet, tmppanels, x, y);
//    } 
//
//    if (tmppanels) delete tmppanels;
//    delete tmpnet;
//    unlink (netfilename);
//    unlink (cfgfilename);
//
//    return ret;
//}
//
//
