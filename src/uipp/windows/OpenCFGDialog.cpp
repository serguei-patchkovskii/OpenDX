/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

#include "Network.h"
#include "OpenCFGDialog.h"
#include "ControlPanel.h"
#include "ErrorDialogManager.h"


bool OpenCFGDialog::ClassInitialized = false;

//String OpenCFGDialog::DefaultResources[] =
//{
//        "*dialogTitle:         Open Configuration...",
//        "*dirMask:         *.cfg",
//        NULL
//};

void OpenCFGDialog::okFileWork(const char *string)
{
    bool  result;
    char *op;

    result = this->network->openCfgFile(string, true);
    op = "reading";

    if(NOT result)
        ErrorMessage("Error while %s configuration file %s", op, string);

}

OpenCFGDialog::OpenCFGDialog(Network *net) : 
                       FileDialog("openCFGDialog")
{

    this->network = net;
    this->hasCommentButton = false;

    if (NOT OpenCFGDialog::ClassInitialized)
    {
        OpenCFGDialog::ClassInitialized = true;
	//this->installDefaultResources(theApplication->getRootWidget());
    }

}

//
// Install the default resources for this class.
//
//void OpenCFGDialog::installDefaultResources(Widget  baseWidget)
//{
//    this->setDefaultResources(baseWidget, OpenCFGDialog::DefaultResources);
//    this->FileDialog::installDefaultResources( baseWidget);
//}
