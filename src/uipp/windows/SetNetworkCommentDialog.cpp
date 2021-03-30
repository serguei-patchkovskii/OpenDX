/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

#include "SetNetworkCommentDialog.h"
#include "Network.h"

bool SetNetworkCommentDialog::ClassInitialized = false;

//String SetNetworkCommentDialog::DefaultResources[] =
//{
//        "*dialogTitle:     		Application Comment...",
//	"*nameLabel.labelString:	Application Comment:",
//        // 
//        // These two must match what is in OpenNetCommentDialog
//        // 
//        "*editorText.columns:           45",  
//        "*editorText.rows:              16",
//        NULL
//};

SetNetworkCommentDialog::SetNetworkCommentDialog(const char *name,
				bool readonly, Network *n) : 
			TextEditDialog(name, readonly)
{
    this->network = n;
}
SetNetworkCommentDialog::SetNetworkCommentDialog(
				bool readonly, Network *n) : 
			TextEditDialog("setNetworkComment", readonly)
{
    this->network = n;

    if (NOT SetNetworkCommentDialog::ClassInitialized)
    {
        SetNetworkCommentDialog::ClassInitialized = true;
	//this->installDefaultResources(theApplication->getRootWidget());
    }
}

SetNetworkCommentDialog::~SetNetworkCommentDialog()
{
}

//
// Install the default resources for this class.
//
//void SetNetworkCommentDialog::installDefaultResources(Widget  baseWidget)
//{
//    this->setDefaultResources(baseWidget,
//				SetNetworkCommentDialog::DefaultResources);
//    this->TextEditDialog::installDefaultResources( baseWidget);
//}
//
// Get the the text that is to be edited. 
//
const char *SetNetworkCommentDialog::getText()
{
    return this->network->getNetworkComment();
}

//
// Save the given text. 
//
bool SetNetworkCommentDialog::saveText(const char *s)
{
    this->network->setNetworkComment(s);
    return true;
}

