/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

#include "NoUndoAnchorCommand.h"
#include "DXAnchorWindow.h"
#include "DXApplication.h"
#include "Network.h"

NoUndoAnchorCommand::NoUndoAnchorCommand(const char*   name,
				       CommandScope* scope,
				       bool       active,
				       DXAnchorWindow  *aw,
				       AnchorCommandType comType ) :
	NoUndoCommand(name, scope, active)
{
	this->commandType = comType;
	this->anchorWindow = aw;
}


bool NoUndoAnchorCommand::doIt(CommandInterface *ci)
{
    DXAnchorWindow *aw = this->anchorWindow;

    ASSERT(aw);

    switch (this->commandType) {
	case NoUndoAnchorCommand::OpenVPE:
            aw->postVPE();
	    break;
	default:
	    ASSERT(0);
    }

    return true;
}


