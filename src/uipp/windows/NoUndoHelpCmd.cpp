/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"




#include "NoUndoHelpCmd.h"
#include "HelpWin.h"


NoUndoHelpCmd::NoUndoHelpCmd(const char   *name,
			 CommandScope* scope,
			 bool       active,
			 HelpWin      *helpWin,
			 HelpCmdType     comType):
    NoUndoCommand(name, scope, active)
{
    this->commandType = comType;
    this->helpWin = helpWin;
}


bool NoUndoHelpCmd::doIt(CommandInterface *ci)
{
    HelpWin *helpWin = this->helpWin;
    bool     ret = true;

    ASSERT(helpWin);

    switch (this->commandType) {
    case NoUndoHelpCmd::Close:
        helpWin->unmanage();
        break;
    default:
	ASSERT(0);
    }

    return ret;
}
