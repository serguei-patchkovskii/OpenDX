/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>


#include "ImageFormatMIF.h"

bool ImageFormatMIF::ClassInitialized = false;

//String ImageFormatMIF::DefaultResources[] = {
//    NUL(char*)
//};


ImageFormatMIF::ImageFormatMIF (ImageFormatDialog* dialog) : 
    PixelImageFormat("MIFformat", dialog)
{

}

ImageFormatMIF::~ImageFormatMIF()
{
}


void ImageFormatMIF::initialize()
{
    if (!ImageFormatMIF::ClassInitialized) {
	//this->setDefaultResources (theApplication->getRootWidget(),
	//    ImageFormat::DefaultResources);
	//this->setDefaultResources (theApplication->getRootWidget(),
	//    PixelImageFormat::DefaultResources);
	//this->setDefaultResources (theApplication->getRootWidget(),
	//    ImageFormatMIF::DefaultResources);
	ImageFormatMIF::ClassInitialized = true;
    }
}

bool ImageFormatMIF::isA(Symbol classname)
{
    Symbol s = theSymbolManager->registerSymbol(ClassImageFormatMIF);
    if (s == classname)
	return true;
    else
	return this->ImageFormat::isA(classname);
}

