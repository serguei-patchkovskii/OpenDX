/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

#include "ApplyFileDialog.h"
#include "ErrorDialogManager.h"



bool ApplyFileDialog::ClassInitialized = false;

//String ApplyFileDialog::DefaultResources[] =
//{
//	"*helpLabelString:	Apply",
//	"*dialogStyle:		DIALOG_MODELESS",
//        NULL
//};


//
// Constructor for instances of THIS class
// (see also the other constructor)
//
ApplyFileDialog::ApplyFileDialog() :
			FileDialog("applyFileDialog")
{
    this->hasCommentButton = true;	// Turn the help button into Apply
    if (NOT ApplyFileDialog::ClassInitialized)
    {
        ApplyFileDialog::ClassInitialized = true;
	//this->installDefaultResources(theApplication->getRootWidget());
    }
}

//
// Constructor for derived  classes (see also the other constructor)
//
ApplyFileDialog::ApplyFileDialog(const char *name) :
			FileDialog(name)
{
    this->hasCommentButton = true;	// Turn the help button into Apply
}

//void ApplyFileDialog::installDefaultResources(Widget  baseWidget)
//{
//    this->setDefaultResources(baseWidget, ApplyFileDialog::DefaultResources);
//    this->FileDialog::installDefaultResources( baseWidget);
//}


//
// Call super class and then set the dialog title and the dirMask resource. 
//
void ApplyFileDialog::createDialog()
{
    //Widget w = this->FileDialog::createDialog(parent);
    //// This apparently must be hardcoded.
    //XtVaSetValues(this->fsb, XmNdialogStyle, XmDIALOG_MODELESS,NULL);
    //return w;
}


//
// Do the ok work using this->okFileWork() with the currently selected file. 
//
void ApplyFileDialog::helpCallback(Dialog *d)
{
//    char *string = this->getSelectedFileName();

	char *string = NULL;
    if (!string) {
        ModalErrorMessage("A filename must be given");
	return;
    } 

    //theApplication->setBusyCursor(true);
    this->okFileWork(string);
    //theApplication->setBusyCursor(false);
    delete string; 
}

