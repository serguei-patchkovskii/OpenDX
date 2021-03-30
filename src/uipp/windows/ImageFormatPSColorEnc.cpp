/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>


#include "ImageFormatPSColorEnc.h"

bool ImageFormatPSColorEnc::ClassInitialized = false;

//String ImageFormatPSColorEnc::DefaultResources[] = {
//    NUL(char*)
//};


ImageFormatPSColorEnc::ImageFormatPSColorEnc (ImageFormatDialog* dialog) : 
    PostScriptImageFormat("PSColorEncformat", dialog)
{

}

ImageFormatPSColorEnc::~ImageFormatPSColorEnc()
{
}


void ImageFormatPSColorEnc::initialize()
{
    if (!ImageFormatPSColorEnc::ClassInitialized) {
	//this->setDefaultResources (theApplication->getRootWidget(),
	//    ImageFormat::DefaultResources);
	//this->setDefaultResources (theApplication->getRootWidget(),
	//    PostScriptImageFormat::DefaultResources);
	//this->setDefaultResources (theApplication->getRootWidget(),
	//    ImageFormatPSColorEnc::DefaultResources);
	ImageFormatPSColorEnc::ClassInitialized = true;
    }
}

bool ImageFormatPSColorEnc::isA (Symbol classname)
{
    Symbol s = theSymbolManager->registerSymbol(ClassImageFormatPSColorEnc);
    if (s == classname)
        return true;
    else
        return PostScriptImageFormat::isA(classname);
}

