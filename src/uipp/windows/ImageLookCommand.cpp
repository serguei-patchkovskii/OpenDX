/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"





#include "ImageLookCommand.h"
#include "ImageWindow.h"

ImageLookCommand::ImageLookCommand(const char   *name,
						 CommandScope *scope,
						 bool       active,
						 ImageWindow  *w,
						 LookDirection dir):
    NoUndoCommand(name, scope, active)
{
    this->imageWindow = w;
    this->direction = dir;
}

bool ImageLookCommand::doIt(CommandInterface *ci)
{
    return this->imageWindow->setLook(this->direction);
}
