/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>


#include "ImageFormatPSGrey.h"

bool ImageFormatPSGrey::ClassInitialized = false;

//String ImageFormatPSGrey::DefaultResources[] = {
//    NUL(char*)
//};


ImageFormatPSGrey::ImageFormatPSGrey (ImageFormatDialog* dialog) : 
    PostScriptImageFormat("PSGreyformat", dialog)
{

}

ImageFormatPSGrey::~ImageFormatPSGrey()
{
}


void ImageFormatPSGrey::initialize()
{
    if (!ImageFormatPSGrey::ClassInitialized) {
	//this->setDefaultResources (theApplication->getRootWidget(),
	//    ImageFormat::DefaultResources);
	//this->setDefaultResources (theApplication->getRootWidget(),
	//    PostScriptImageFormat::DefaultResources);
	//this->setDefaultResources (theApplication->getRootWidget(),
	//    ImageFormatPSGrey::DefaultResources);
	ImageFormatPSGrey::ClassInitialized = true;
    }
}

bool ImageFormatPSGrey::isA (Symbol classname)
{
    Symbol s = theSymbolManager->registerSymbol(ClassImageFormatPSGrey);
    if (s == classname)
        return true;
    else
        return PostScriptImageFormat::isA(classname);
}

