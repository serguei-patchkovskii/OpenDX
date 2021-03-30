/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"




#include "ImageRedoCommand.h"
#include "ImageWindow.h"

ImageRedoCommand::ImageRedoCommand(const char   *name,
						 CommandScope *scope,
						 bool       active,
						 ImageWindow  *w):
    NoUndoCommand(name, scope, active)
{
    this->imageWindow = w;
}

bool ImageRedoCommand::doIt(CommandInterface *ci)
{
    this->imageWindow->redoCamera();
    return true;
}
