/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

#include "Command.h"
#include "NoUndoCommand.h"
#include "ColormapFileCommand.h"
#include "ColormapEditor.h"

ColormapFileCommand::ColormapFileCommand(const char*   name,
                         CommandScope*   scope,
                         bool         active,
                         ColormapEditor* editor,
			 bool	opening) 
 			:NoUndoCommand(name,scope,active)	
{
    this->editor = editor;
    this->opening = opening;

}

ColormapFileCommand::~ColormapFileCommand()
{
}


bool ColormapFileCommand::doIt(CommandInterface *ci)
{
   editor->postOpenColormapDialog(this->opening);
   return true;
}

