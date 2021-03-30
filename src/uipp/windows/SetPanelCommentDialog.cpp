/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

#include "DXStrings.h"
#include "SetPanelCommentDialog.h"
#include "ControlPanel.h"

bool SetPanelCommentDialog::ClassInitialized = false;

//String SetPanelCommentDialog::DefaultResources[] =
//{
//        "*dialogTitle:     		Control Panel Comment...",
//	"*nameLabel.labelString:	Panel Comment:",
//        NULL
//};

SetPanelCommentDialog::SetPanelCommentDialog(
				const char *name,
				bool readonly, ControlPanel *cp) : 
				TextEditDialog(name, readonly)
{
    // Any initializations here, need to go in the other constructor also.
    this->controlPanel = cp;
}

SetPanelCommentDialog::SetPanelCommentDialog(
				bool readonly, ControlPanel *cp) : 
				TextEditDialog("setPanelComment",
				readonly)
{
    // Any initializations here, need to go in the other constructor also.
    this->controlPanel = cp;

    if (NOT SetPanelCommentDialog::ClassInitialized)
    {
        SetPanelCommentDialog::ClassInitialized = true;
	//this->installDefaultResources(theApplication->getRootWidget());
    }
}

SetPanelCommentDialog::~SetPanelCommentDialog()
{
}

char *SetPanelCommentDialog::getDialogTitle()
{
    const char *title = this->controlPanel->getWindowTitle();
    char *dialogTitle = NULL;

    if (title) {
        int len = STRLEN(title) + STRLEN(" Comment ...") + 16;
        dialogTitle = new char[len];
	sprintf(dialogTitle,"%s Comment...",title);
    }
    return dialogTitle;
}
//
// Install the default resources for this class.
//
//void SetPanelCommentDialog::installDefaultResources(Widget  baseWidget)
//{
//    this->setDefaultResources(baseWidget,
//				SetPanelCommentDialog::DefaultResources);
//    this->TextEditDialog::installDefaultResources( baseWidget);
//}
//
// Get the the text that is to be edited. 
//
const char *SetPanelCommentDialog::getText()
{
    return this->controlPanel->getPanelComment();
}

//
// Save the given text. 
//
bool SetPanelCommentDialog::saveText(const char *s)
{
    this->controlPanel->setPanelComment(s);
    return true;
}

