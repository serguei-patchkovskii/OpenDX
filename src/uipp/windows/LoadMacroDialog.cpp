/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

#include "LoadMacroDialog.h"
#include "MacroDefinition.h"
#include "ErrorDialogManager.h"


bool LoadMacroDialog::ClassInitialized = false;

//String LoadMacroDialog::DefaultResources[] =
//{
//        "*dialogTitle:    			Load Macro...",
//        "*loadDirectory.labelString:  		Load All Macros",
//	".fileSelectionBox.okLabelString:	Load Macro",
//	".fileSelectionBox.cancelLabelString:	Close",
//        NULL
//};

LoadMacroDialog::LoadMacroDialog() : 
                       OpenNetworkDialog("loadMacroDialog")
{
    this->doingOk = false;

    if (NOT LoadMacroDialog::ClassInitialized)
    {
        LoadMacroDialog::ClassInitialized = true;
	//this->installDefaultResources(theApplication->getRootWidget());
    }
}
LoadMacroDialog::LoadMacroDialog(const char *name) : 
                       OpenNetworkDialog(name)
{
    this->doingOk = false;
}

bool LoadMacroDialog::okCallback(Dialog *d)
{
    ASSERT(this);
    this->doingOk = true; 
    bool r = this->OpenNetworkDialog::okCallback(d);
    this->doingOk = false; 
    return r;
}
void LoadMacroDialog::okFileWork(const char *string)
{
    char *errmsg;
    if (!MacroDefinition::LoadMacro(string, &errmsg)) {
	ModalErrorMessage(errmsg);
	delete errmsg;
    }
}

void LoadMacroDialog::unmanage()
{
    if (!this->doingOk)
	this->OpenNetworkDialog::unmanage();
}

//
// Install the default resources for this class.
//
//void LoadMacroDialog::installDefaultResources(Widget  baseWidget)
//{
//    this->setDefaultResources(baseWidget, LoadMacroDialog::DefaultResources);
//    this->OpenNetworkDialog::installDefaultResources( baseWidget);
//}
void LoadMacroDialog::createDialog()
{
 //   Dimension width, ok_width, ok_height, ok_shadow_width;
 //   Arg arg[15];
 //   int n = 0;
 //   Widget button;

 //   XtSetArg(arg[n], XmNautoUnmanage, False);           n++;
 //   Widget form = this->Dialog::CreateMainForm(parent,this->name, arg, n);

 //   this->fsb = this->createFileSelectionBox(form, "fileSelectionBox");

 //   button = XmFileSelectionBoxGetChild(fsb, XmDIALOG_OK_BUTTON);
 //   XtVaGetValues(button, 
	//		XmNwidth, &ok_width, 
	//		XmNheight, &ok_height, 
	//		XmNshadowThickness, &ok_shadow_width, 
	//		NULL);


 //   //
 //   // Set up the 'load all' button.
 //   //
 //   Widget loadDirectory =  XtCreateManagedWidget(
 //       "loadDirectory", xmPushButtonWidgetClass, form, NULL, 0);


 //   n = 0;
 //   //XtSetArg(arg[n],XmNtopAttachment, 	XmATTACH_WIDGET); n++;
 //   //XtSetArg(arg[n],XmNtopWidget, 	fsb); n++;
 //   //XtSetArg(arg[n],XmNtopOffset, 	10); n++;
 //   XtSetArg(arg[n],XmNbottomAttachment,XmATTACH_FORM); n++;
 //   XtSetArg(arg[n],XmNbottomOffset, 	10); n++;
 //   //XtSetArg(arg[n],XmNleftAttachment, 	XmATTACH_FORM); n++;
 //   //XtSetArg(arg[n],XmNleftOffset, 	10); n++;
 //   XtSetArg(arg[n],XmNleftAttachment, 	XmATTACH_POSITION); n++;
 //   XtSetArg(arg[n],XmNleftPosition, 	38); n++;
 //   XtSetArg(arg[n],XmNheight, 		ok_height); n++;
 //   XtSetArg(arg[n],XmNshadowThickness, ok_shadow_width); n++;
 //   XtVaGetValues(loadDirectory,XmNwidth, &width, NULL);
 //   if (width < ok_width) {
	//XtSetArg(arg[n],XmNwidth, 	 ok_width); n++;
 //	XtSetArg(arg[n],XmNrecomputeSize,False ); n++;
 //   } 
 //   XtSetValues(loadDirectory,arg,n);

 //   XtAddCallback(loadDirectory,                   
	//		XmNactivateCallback,
	//		(XtCallbackProc)LoadMacroDialog_LoadDirectoryCB,
	//		(XtPointer)this);


 //   n = 0;
 //   XtSetArg(arg[n],XmNtopAttachment, 	XmATTACH_FORM); n++;
 //   XtSetArg(arg[n],XmNleftAttachment, 	XmATTACH_FORM); n++;
 //   XtSetArg(arg[n],XmNrightAttachment, XmATTACH_FORM); n++;
 //   XtSetArg(arg[n],XmNbottomAttachment, XmATTACH_WIDGET); n++;
 //   XtSetArg(arg[n],XmNbottomWidget, loadDirectory); n++;
 //   XtSetValues(this->fsb,arg,n);
 //   XtManageChild(this->fsb);

 //  
 //   return form;

}

//extern "C" void LoadMacroDialog_LoadDirectoryCB(Widget widget,
//                                     XtPointer clientData,
//                                     XtPointer callData)
//{
//    LoadMacroDialog *dialog = (LoadMacroDialog*)clientData;
//    char *errmsg;
//    char *dir = dialog->getCurrentDirectory();
//    ASSERT(dir);
//
//    theApplication->setBusyCursor(true);
//    if (!MacroDefinition::LoadMacroDirectories(dir, true, &errmsg)) {
//	ModalErrorMessage(dialog->getRootWidget(),errmsg);
//	delete errmsg;
//    }
//    delete dir;
//    theApplication->setBusyCursor(false);
//}
