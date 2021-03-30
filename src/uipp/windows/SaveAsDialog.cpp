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
#include "Network.h"
#include "SaveAsDialog.h"
#include "OpenCommand.h"


#include <sys/stat.h>

bool SaveAsDialog::ClassInitialized = false;

//String SaveAsDialog::DefaultResources[] =
//{
//        "*dialogTitle:     Save As...",
//        "*dirMask:         *.net",
//        NULL
//};


void SaveAsDialog::saveFile(const char *filename)
{
    bool success;
    success = this->network->saveNetwork(filename);

    if(success AND this->postCmd)
	((OpenCommand*)this->postCmd)->execute();
}

SaveAsDialog::SaveAsDialog(Network *network) : 
                       SaveFileDialog("saveAsDialog", ".net")
{
    this->network = network;
    this->postCmd = NULL;

    if (NOT SaveAsDialog::ClassInitialized)
    {
        SaveAsDialog::ClassInitialized = true;
	//this->installDefaultResources(theApplication->getRootWidget());
    }
}

//
// Install the default resources for this class.
//
//void SaveAsDialog::installDefaultResources(Widget  baseWidget)
//{
//    this->setDefaultResources(baseWidget, SaveAsDialog::DefaultResources);
//    this->SaveFileDialog::installDefaultResources( baseWidget);
//}

char *SaveAsDialog::getDefaultFileName()
{
   const char *netname = this->network->getFileName();
   if (netname)
	return DuplicateString(netname);
   else
	return NULL;
}

