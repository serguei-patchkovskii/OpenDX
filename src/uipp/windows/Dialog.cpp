/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

#include "Dialog.h"

bool Dialog::ClassInitialized = false;


//extern "C" void Dialog_OkCB(Widget, XtPointer clientData, XtPointer)
//{
//    Dialog 	      *dialog = (Dialog*)clientData;
//
//    if (dialog->okCallback(dialog))
//        dialog->unmanage();
//}
//extern "C" void Dialog_CancelCB(Widget, XtPointer clientData, XtPointer)
//{
//    Dialog 	      *dialog = (Dialog*)clientData;
//
//    dialog->cancelCallback(dialog);
//    dialog->unmanage();
//}
//extern "C" void Dialog_HelpCB(Widget widget,
//	        XtPointer clientData,
//	        XtPointer)
//{
//    Dialog 	      *dialog = (Dialog*)clientData;
//
//    dialog->helpCallback(dialog);
//}

Dialog::Dialog(const char *name) : 
    UIComponent(name)
{
    //this->parent = parent;

    this->managed = false;

//    this->help = NULL;
//    this->ok = NULL;
//    this->cancel = NULL;
}
//void Dialog::installDefaultResources(Widget  baseWidget)
//{
//}
void Dialog::initialize()
{
}

void Dialog::post()
{
 //   theApplication->setBusyCursor(true);
 //   if (this->getRootWidget() == NULL)
 //   {
	this->initialize();
	this->createDialog();
	//this->setRootWidget(this->createDialog(this->parent));

	//Widget shell = XtParent(this->getRootWidget());
	//XtVaSetValues(shell, XmNdeleteResponse, XmDO_NOTHING, NULL);
	//Atom WM_DELETE_WINDOW = XmInternAtom(XtDisplay(shell),
	//				    "WM_DELETE_WINDOW", False);
	//XmAddWMProtocolCallback(shell, WM_DELETE_WINDOW,
	//			    (XtCallbackProc)Dialog_CancelCB,
	//			    (void *)(this));


	//if (this->ok != NULL)
	//    XtAddCallback(this->ok,
	//		  XmNactivateCallback,
	//		  (XtCallbackProc)Dialog_OkCB,
	//		  (XtPointer)this);
	//if (this->help != NULL)
	//    XtAddCallback(this->help,
	//		  XmNactivateCallback,
	//		  (XtCallbackProc)Dialog_HelpCB,
	//		  (XtPointer)this);
	//if (this->cancel != NULL)
	//    XtAddCallback(this->cancel,
	//		  XmNactivateCallback,
	//		  (XtCallbackProc)Dialog_CancelCB,
	//		  (XtPointer)this);
 //   }

 //   this->manage();
 //   theApplication->setBusyCursor(false);

 //   XmUpdateDisplay(this->getRootWidget());
}

void Dialog::createDialog(void)
{
    //return NULL;
}

//void Dialog::CreateMainForm(char * name, 
//                              ArgList arglist, Cardinal argcount)
//{
//#ifdef XmFormDialogWorks
//   return XmCreateFormDialog(parent,name,arglist,argcount);
//#else
//   Widget form_shell;
//   Widget form;
//   Arg shell_arglist[2];
//   int shell_argcount = 0;
//   char buffer[256];
//
//   /*  Create a pop-up shell for the form box.  */
//
//   sprintf(buffer,"%sPopup",name);
//   XtSetArg (shell_arglist[0], XmNallowShellResize, True);
//   /* This function causes problem on indigo.
//    * form_shell = XmCreateDialogShell (parent, buffer,
//    *                                 shell_arglist, 1);
//    */
//   /* Use the following instead of the above */
//   form_shell = XtCreateWidget(buffer, xmDialogShellWidgetClass,
//                                parent, shell_arglist, 1);
//
//   /*  Create the widget  */
//
//   form = XtCreateWidget (name, xmFormWidgetClass,
//                          form_shell, arglist, argcount);
//   XtAddCallback (form, XmNdestroyCallback, (XtCallbackProc)DestroyParentCB, NULL);
//   return form;
//#endif // XmFormDialogWorks
//
//}

void Dialog::manage()
{
    this->managed = true;

    //Widget w = this->getRootWidget();

    //while(!XtIsShell(w))
    //    w = XtParent(w);

    //XWindowAttributes attr;
    //XGetWindowAttributes(XtDisplay(w), XtWindow(XtParent(w)), &attr);

    ////
    //// MapRaise its parent only when it's unviewable or iconified.
    ////
    //if(XtParent(w) && (XtParent(w) != theApplication->getRootWidget())
    //   && (attr.map_state==IsUnviewable || attr.map_state==IsUnmapped))
    //    XMapRaised(XtDisplay(w), XtWindow(XtParent(w)));

    //this->UIComponent::manage();
    //XMapRaised(XtDisplay(w), XtWindow(w));
}

void Dialog::unmanage()
{
    this->UIComponent::unmanage();
    this->managed = false;
}

bool Dialog::isManaged()
{
    return this->managed;
}
//
// Set the title of the dialog after this->root has been created.
// Ignored if this->root has not been created yet.
//
void Dialog::setDialogTitle(const char *title)
{
 //   Widget shell;

 //   if ((shell=this->getRootWidget())) {
 //   	while(NOT XtIsShell(shell))
	//     shell = XtParent(shell);

	//if (shell)
	//    XtVaSetValues(shell,  XmNtitle, title , NULL); 
 //   }
}
