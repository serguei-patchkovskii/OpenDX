/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"




#include "ImageResetCommand.h"
#include "ImageWindow.h"

ImageResetCommand::ImageResetCommand(const char   *name,
						 CommandScope *scope,
						 bool       active,
						 ImageWindow  *w):
    NoUndoCommand(name, scope, active)
{
    this->imageWindow = w;
}

bool ImageResetCommand::doIt(CommandInterface *ci)
{
    this->imageWindow->resetCamera();
    return true;
}
