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
#include "SetColormapNameDialog.h"

#include "ColormapNode.h"
#include "Network.h"
#include "ErrorDialogManager.h"

bool SetColormapNameDialog::ClassInitialized = false;

//String SetColormapNameDialog::DefaultResources[] =
//{
//    "*dialogTitle:               	Change Colormap Name...", 
//    "*nameLabel.labelString:            Colormap Name:",
//    NULL
//};


SetColormapNameDialog::SetColormapNameDialog(ColormapNode *cn) :
    SetNameDialog("setColormapNameDialog")
{
    this->colormapNode = cn;

    if (NOT SetColormapNameDialog::ClassInitialized)
    {
        SetColormapNameDialog::ClassInitialized = true;
	//this->installDefaultResources(theApplication->getRootWidget());
    }
}

SetColormapNameDialog::~SetColormapNameDialog()
{
}

//
// Install the default resources for this class.
//
//void SetColormapNameDialog::installDefaultResources(Widget  baseWidget)
//{
//    this->setDefaultResources(baseWidget,
//				SetColormapNameDialog::DefaultResources);
//    this->SetNameDialog::installDefaultResources(baseWidget);
//}
//
const char *SetColormapNameDialog::getText()
{
    return this->colormapNode->getTitle();
}

bool SetColormapNameDialog::saveText(const char *s)
{
    if (IsBlankString(s)) {
	ModalErrorMessage(
		"The name string cannot be blank.");
        return false;
    } else {
	ColormapNode *node = this->colormapNode;
    	node->setTitle(s);
    	node->getNetwork()->setFileDirty();
    }

    return true;
}

