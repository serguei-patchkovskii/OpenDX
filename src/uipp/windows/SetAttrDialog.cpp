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
#include "SetAttrDialog.h"
#include "InteractorInstance.h"
#include "InteractorNode.h"

SetAttrDialog::SetAttrDialog(const char *name, 
                    	     const char *title, InteractorInstance *ii) :
                                Dialog(name)
{
    this->title = DuplicateString(title);
    this->interactorInstance = ii;
}

SetAttrDialog::~SetAttrDialog() 
{ 
    if (this->title) delete this->title; 
}

void SetAttrDialog::cancelCallback(Dialog* dialog)
{
   // We don't need to do anything, since we only send the attributes
   // to the interactor on Ok.
} 
bool SetAttrDialog::okCallback(Dialog* dialog)
{
    bool r;
    SetAttrDialog *sad = (SetAttrDialog*)dialog;
    InteractorNode *inode = 
		(InteractorNode*)sad->interactorInstance->getNode();

    inode->deferVisualNotification();

    if (!sad->storeAttributes())  {
	r = false;
	inode->undeferVisualNotification();
    } else {
	r = true;
	inode->notifyVisualsOfStateChange();
	inode->undeferVisualNotification();
	inode->sendValues(false);
    }
    return r;
} 

void SetAttrDialog::createDialog()
{
//
//    this->initialize();
//
//    int n = 0;
//    Arg wargs[10];
//    XtSetArg(wargs[n], XmNresizePolicy, XmRESIZE_NONE); n++;
//    Widget mainForm = this->CreateMainForm(parent, this->name, wargs, n); 
//
//    XtVaSetValues(mainForm,
//        XmNdialogStyle, XmDIALOG_PRIMARY_APPLICATION_MODAL,
//#if 1
//	XmNautoUnmanage, False,
//#endif
//        NULL);
//
//    XtVaSetValues(XtParent(mainForm),
//        XmNtitle, this->title, 
//#if 0
//        XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL,
//#endif
//        NULL);
//
//    this->createAttributesPart(mainForm);
//
//    return mainForm;
}
//
// Before each display, reload/redisplay the attributes.
//
void SetAttrDialog::manage()
{
    this->refreshDisplayedAttributes();
    this->Dialog::manage();
}
void SetAttrDialog::setAttributeSensitivity()
{
}

//
// load and update the displayed attributes
//
void SetAttrDialog::refreshDisplayedAttributes()
{
    //ASSERT(this->getRootWidget());
    this->loadAttributes();
    this->updateDisplayedAttributes();
    this->setAttributeSensitivity();
}
