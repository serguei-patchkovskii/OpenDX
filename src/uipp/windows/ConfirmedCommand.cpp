/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

#include "ConfirmedCommand.h"
#include "QuestionDialogManager.h"
#include "CommandInterface.h"


void ConfirmedCommand::OkDCB(void* clientData)
{
    ConfirmedCommand* command;

    ASSERT(clientData);

    //
    // Call the superclass execute() function to do all the
    // normal command processing....
    //
    command = (ConfirmedCommand*)clientData;
    command->NoUndoCommand::execute(NULL);
}


ConfirmedCommand::ConfirmedCommand(const char*   name,
				   CommandScope* scope,
				   bool       active,
				   char*         dialogTitle,
				   char*         dialogQuestion):
	NoUndoCommand(name, scope, active)
{
    ASSERT(dialogTitle);
    ASSERT(dialogQuestion);

    this->dialogTitle    = dialogTitle;
    this->dialogQuestion = dialogQuestion;
//    this->dialogParent	 = parent;
}


bool ConfirmedCommand::execute(CommandInterface *ci)
{

 //   Widget parent = this->dialogParent;
 //   if (!parent)  {
	//if (ci)
	//    parent = ci->getDialogParent();
	//else
	//    parent = theApplication->getRootWidget();
 //   }
    //
    // First post the confirmation dialog.
    //
    theQuestionDialogManager->modalPost(
				   this->dialogQuestion,
				   this->dialogTitle,
				   (void*)this,
				   ConfirmedCommand::OkDCB);
				   
    return false;
}


