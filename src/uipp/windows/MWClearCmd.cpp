/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

#include "MWClearCmd.h"
#include "MsgWin.h"



//
// Constructor:
//
MWClearCmd::MWClearCmd(const char *name,
	   CommandScope *scope,
	   bool active,
	   MsgWin *win):
    NoUndoCommand(name, scope, active)
{
    this->messageWindow = win;
}


bool MWClearCmd::doIt(CommandInterface *ci)
{
    this->messageWindow->clear();

    return true;
}
