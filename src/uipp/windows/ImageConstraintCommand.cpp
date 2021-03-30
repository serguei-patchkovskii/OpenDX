/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"




#include "ImageConstraintCommand.h"
#include "ImageWindow.h"

ImageConstraintCommand::ImageConstraintCommand(const char   *name,
						 CommandScope *scope,
						 bool       active,
						 ImageWindow  *w,
						 ConstraintDirection dir):
    NoUndoCommand(name, scope, active)
{
    this->imageWindow = w;
    this->direction = dir;
}

bool ImageConstraintCommand::doIt(CommandInterface *ci)
{
    return this->imageWindow->setConstraint(this->direction);
}
