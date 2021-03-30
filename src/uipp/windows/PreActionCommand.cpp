/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

#include "PreActionCommand.h"
#include "DialogManager.h"
#include "QuestionDialogManager.h"
#include "CommandInterface.h"

struct PreActionData {
    PreActionCommand 	*cmd;
    CommandInterface 	*DXinterface;
};

PreActionCommand::PreActionCommand(const char*   name,
				   CommandScope* scope,
				   bool       active,
				   char*         dialogTitle,
				   char*         dialogQuestion) :
	NoUndoCommand(name, scope, active)
{
    ASSERT(dialogTitle);
    ASSERT(dialogQuestion);

    this->dialogTitle    = dialogTitle;
    this->dialogQuestion = dialogQuestion;
//    this->dialogParent = parent;
}

void PreActionCommand::YesDCB(void* clientData)
{
    ASSERT(clientData);
    PreActionData *ped = (PreActionData*)clientData;

    //
    // Call the "Yes" function first, then do all the
    // normal command processing....
    //
    ped->cmd->doPreAction();
   delete ped;
}

void PreActionCommand::NoDCB(void* clientData)
{
    ASSERT(clientData);
    PreActionData *ped = (PreActionData*)clientData;

    //
    // Call the superclass execute() function to do all the
    // normal command processing....
    //
    ped->cmd->NoUndoCommand::execute(ped->DXinterface);
    delete ped;
}

void PreActionCommand::CancelDCB(void* clientData)
{
    PreActionData *ped = (PreActionData*)clientData;
    delete ped;

//    Widget dialog = theQuestionDialogManager->getRootWidget();
  
//    DialogManager::CleanUp(dialog, theQuestionDialogManager->getData());

    //XtUnmanageChild(dialog);
}



bool PreActionCommand::execute(CommandInterface *ci)
{

//    Widget parent = this->dialogParent;
    //if (!parent)  {
    //    if (ci)
    //        parent = ci->getDialogParent();
    //    else
    //        parent = theApplication->getRootWidget();
    //}   


    //
    // post the confirmation dialog.
    //
    PreActionData *ped = new PreActionData;
    ped->cmd = this;
    ped->DXinterface = ci;
    theQuestionDialogManager->modalPost(
				   this->dialogQuestion,
				   this->dialogTitle,
				   (void*)ped,
				   PreActionCommand::YesDCB,
				   PreActionCommand::NoDCB,
				   PreActionCommand::CancelDCB,
				   "Yes",
				   "No",
				   "Cancel",
				   0,
				   3);
    

    return false;
}


