/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>


#ifndef _ImageFormatREX_h
#define _ImageFormatREX_h


#include "PixelImageFormat.h"

//
// Class name definition:
//
#define ClassImageFormatREX	"ImageFormatREX"

//
// SaveImageDialog class definition:
//				
class ImageFormatREX : public PixelImageFormat
{
  private:

    //static String  DefaultResources[];
    static bool ClassInitialized;

  protected:

    virtual void	initialize();

  public:

    //
    // Constructor:
    //
    ImageFormatREX(ImageFormatDialog *dialog);

    static ImageFormat* Allocator (ImageFormatDialog* dialog) 
	{ return  new ImageFormatREX(dialog); }

    //
    // Destructor:
    //
    ~ImageFormatREX();

    virtual const char*		paramString() { return "r+g+b"; }
    virtual const char*		menuString() { return "R+G+B"; }
    virtual const char*		fileExtension() { return ".r"; }
    virtual bool 		supportsAppend() { return true; }
    virtual void		eraseOutputFile(const char *fname);
    virtual bool		supportsDelayedColors() { return false; }

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName() { return ClassImageFormatREX; }
    virtual bool isA(Symbol classname);
};


#endif // _ImageFormatREX_h
