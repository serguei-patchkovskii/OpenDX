/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"




#include "ViewControlWhichCameraCommand.h"
#include "ViewControlDialog.h"

ViewControlWhichCameraCommand::ViewControlWhichCameraCommand(const char   *name,
						 CommandScope *scope,
						 bool       active,
						 ViewControlDialog  *d):
    NoUndoCommand(name, scope, active)
{
    this->viewControlDialog = d;
}

bool ViewControlWhichCameraCommand::doIt(CommandInterface *ci)
{
    this->viewControlDialog->setWhichCameraVector();
    return true;
}
