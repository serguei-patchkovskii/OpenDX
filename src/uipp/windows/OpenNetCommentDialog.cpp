/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

#include "OpenNetCommentDialog.h"

bool OpenNetCommentDialog::ClassInitialized = false;

//String OpenNetCommentDialog::DefaultResources[] =
//{
//       "*dialogTitle:		Application Comment..." ,
//       "*nameLabel.labelString:	Application Comment:" ,
//        //
//        // These two must match what is in SetNetworkCommentDialog
//        //
//        "*editorText.columns:           45",  
//        "*editorText.rows:              16",
//
//	NULL
//};

OpenNetCommentDialog::OpenNetCommentDialog()
			: TextEditDialog("openNetComment", true)
{
    //this->dialogModality = XmDIALOG_APPLICATION_MODAL;

    if (NOT OpenNetCommentDialog::ClassInitialized)
    {
        OpenNetCommentDialog::ClassInitialized = true;
	//this->installDefaultResources(theApplication->getRootWidget());
    }
}

OpenNetCommentDialog::~OpenNetCommentDialog()
{
}

//
// Install the default resources for this class.
//
//void OpenNetCommentDialog::installDefaultResources(Widget  baseWidget)
//{
//    this->setDefaultResources(baseWidget,
//				OpenNetCommentDialog::DefaultResources);
//    this->TextEditDialog::installDefaultResources( baseWidget);
//}
