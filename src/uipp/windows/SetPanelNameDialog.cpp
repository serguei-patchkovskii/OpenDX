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
#include "SetPanelNameDialog.h"
#include "ControlPanel.h"
#include "Network.h"
#include "ErrorDialogManager.h"

bool SetPanelNameDialog::ClassInitialized = false;

//String SetPanelNameDialog::DefaultResources[] =
//{
//    "*dialogTitle:               	Change Control Panel Name...", 
//    "*nameLabel.labelString:            Control Panel Name:",
//    NULL
//};


SetPanelNameDialog::SetPanelNameDialog(ControlPanel *cp) :
    SetNameDialog("setPanelNameDialog")
{
    this->controlPanel = cp;
  
    if (NOT SetPanelNameDialog::ClassInitialized)
    {
        SetPanelNameDialog::ClassInitialized = true;
	//this->installDefaultResources(theApplication->getRootWidget());
    }
}

SetPanelNameDialog::~SetPanelNameDialog()
{
}

//
// Install the default resources for this class.
//
//void SetPanelNameDialog::installDefaultResources(Widget  baseWidget)
//{
//    this->setDefaultResources(baseWidget,
//				SetPanelNameDialog::DefaultResources);
//    this->SetNameDialog::installDefaultResources( baseWidget);
//}

const char *SetPanelNameDialog::getText()
{
    return this->controlPanel->getPanelNameString();
}

bool SetPanelNameDialog::saveText(const char *s)
{
    if (IsBlankString(s)) {
	ModalErrorMessage(
		"The name string cannot be blank.");
        return false;
    } else {
	ControlPanel *panel = this->controlPanel;
    	panel->setPanelName(s);
    	panel->getNetwork()->setFileDirty();
    }

    return true;
}

