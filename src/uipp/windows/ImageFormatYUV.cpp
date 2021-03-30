/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

#include <string.h>

#include "ImageFormatYUV.h"
#include "DXStrings.h"
#if defined(DXD_WIN) || defined(OS2)
#define unlink _unlink
#endif
#if defined(HAVE_UNISTD_H)
#include <unistd.h>
#endif


bool ImageFormatYUV::ClassInitialized = false;

//String ImageFormatYUV::DefaultResources[] = {
//    NUL(char*)
//};


ImageFormatYUV::ImageFormatYUV (ImageFormatDialog* dialog) : 
    PixelImageFormat("YUVformat", dialog)
{

}

ImageFormatYUV::~ImageFormatYUV()
{
}


void ImageFormatYUV::initialize()
{
    if (!ImageFormatYUV::ClassInitialized) {
	//this->setDefaultResources (theApplication->getRootWidget(),
	//    ImageFormat::DefaultResources);
	//this->setDefaultResources (theApplication->getRootWidget(),
	//    PixelImageFormat::DefaultResources);
	//this->setDefaultResources (theApplication->getRootWidget(),
	//    ImageFormatYUV::DefaultResources);
	ImageFormatYUV::ClassInitialized = true;
    }
}


void ImageFormatYUV::eraseOutputFile(const char *fname)
{
    char *cp;
    char *srcfile = DuplicateString(fname);
    char *file_to_delete = new char[strlen(fname) + 8];
    if ( (cp = strstr (srcfile, ".yuv")) ) cp[0] = '\0';
    sprintf (file_to_delete, "%s.yuv", srcfile);
    unlink (file_to_delete);
    sprintf (file_to_delete, "%s.size", srcfile);
    unlink (file_to_delete);

    delete file_to_delete;
    delete srcfile;
}

bool ImageFormatYUV::isA(Symbol classname)
{
    Symbol s = theSymbolManager->registerSymbol(ClassImageFormatYUV);
    if (s == classname)
	return true;
    else
	return this->ImageFormat::isA(classname);
}

