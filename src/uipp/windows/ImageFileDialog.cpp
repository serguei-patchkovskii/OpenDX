/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

#include "ImageFileDialog.h"
#include "DXStrings.h"
#include "ErrorDialogManager.h"
#include "SaveImageDialog.h"

//String ImageFileDialog::DefaultResources[] = {
//    ".dialogStyle:	XmDIALOG_MODELESS",
//    "*dialogTitle:	Save Image to File...",
//    NUL(char*)
//};

bool ImageFileDialog::ClassInitialized = false;

ImageFileDialog::ImageFileDialog(SaveImageDialog* dialog) :
                       FileDialog("imageFileSelector")
{
    this->sid = dialog;
}

//void ImageFileDialog::installDefaultResources(Widget  baseWidget)
//{
//    if (ImageFileDialog::ClassInitialized) return ;
//    ImageFileDialog::ClassInitialized = true;
//    this->setDefaultResources(baseWidget, ImageFileDialog::DefaultResources);
//    this->FileDialog::installDefaultResources( baseWidget);
//}

void ImageFileDialog::okFileWork(const char *string)
{
    this->sid->setFilename(string, false);
    this->sid->setCommandActivation();
}

void ImageFileDialog::cancelCallback (Dialog *)
{
    this->unmanage();
    this->sid->setCommandActivation();
}

void ImageFileDialog::createDialog ()
{
    //this->installDefaultResources (theApplication->getRootWidget());
    //return this->FileDialog::createDialog(parent);
}
