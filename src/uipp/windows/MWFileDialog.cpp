/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

#include "MWFileDialog.h"
#include "MsgWin.h"
#include "ToggleButtonInterface.h"


bool MWFileDialog::ClassInitialized = false;

//String MWFileDialog::DefaultResources[] =
//{
//    "*dirMask:         *.log",
//    NULL
//};


void MWFileDialog::okFileWork(const char *file)
{
    if (this->log)
	this->messageWindow->log(file);
    else
	this->messageWindow->save(file);
}

void MWFileDialog::cancelCallback(Dialog *d)
{
    MWFileDialog *fd = (MWFileDialog*)d;

    fd->messageWindow->getLogInterface()->setState(false);
    this->FileDialog::cancelCallback(d);
}

MWFileDialog::MWFileDialog(MsgWin *messageWindow):
    FileDialog("mwFileDialog")
{
    this->log = true;
    this->messageWindow = messageWindow;

    if (NOT MWFileDialog::ClassInitialized)
    {
        MWFileDialog::ClassInitialized = true;
	//this->installDefaultResources(theApplication->getRootWidget());
    }
}
//
// Install the default resources for this class.
//
//void MWFileDialog::installDefaultResources(Widget  baseWidget)
//{
//    this->setDefaultResources(baseWidget, MWFileDialog::DefaultResources);
//    this->FileDialog::installDefaultResources( baseWidget);
//}

//
// True means that this will make a log request next, false means a save
//

void MWFileDialog::postAs(bool log)
{
    this->log = log;

    this->FileDialog::post();

    //XmString title = XmStringCreateSimple(log? (char *)"Log...": (char *)"Save As...");
    //XtVaSetValues(this->getFileSelectionBox(),
		  //XmNdialogTitle, title,
		  //NULL);
    //XmStringFree(title);
}
