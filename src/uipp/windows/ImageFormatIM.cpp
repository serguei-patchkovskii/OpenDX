/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>


#include "ImageFormatIM.h"

bool ImageFormatIM::ClassInitialized = false;

//String ImageFormatIM::DefaultResources[] = {
//    NUL(char*)
//};


ImageFormatIM::ImageFormatIM (ImageFormatDialog* dialog) : 
    PixelImageFormat("IMformat", dialog)
{

}

ImageFormatIM::~ImageFormatIM()
{
}


void ImageFormatIM::initialize()
{
    if (!ImageFormatIM::ClassInitialized) {
	//this->setDefaultResources (theApplication->getRootWidget(),
	//    ImageFormat::DefaultResources);
	//this->setDefaultResources (theApplication->getRootWidget(),
	//    PixelImageFormat::DefaultResources);
	//this->setDefaultResources (theApplication->getRootWidget(),
	//    ImageFormatIM::DefaultResources);
	ImageFormatIM::ClassInitialized = true;
    }
}

bool ImageFormatIM::isA (Symbol classname)
{
    Symbol s = theSymbolManager->registerSymbol(ClassImageFormatIM);
    if (s == classname)
	return true;
    else
	return this->ImageFormat::isA(classname);
}
