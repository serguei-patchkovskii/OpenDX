/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"




#include "ImageSetModeCommand.h"
#include "ImageWindow.h"

ImageSetModeCommand::ImageSetModeCommand(const char   *name,
						 CommandScope *scope,
						 bool       active,
						 ImageWindow  *w,
						 DirectInteractionMode mode):
    NoUndoCommand(name, scope, active)
{
    this->imageWindow = w;
    this->mode = mode;
}

bool ImageSetModeCommand::doIt(CommandInterface *ci)
{
    return this->imageWindow->setInteractionMode(mode);
}
