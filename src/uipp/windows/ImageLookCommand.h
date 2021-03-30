/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"




#ifndef _ImageLookCommand_h
#define _ImageLookCommand_h


#include "NoUndoCommand.h"
#include "ImageWindow.h"


//
// Class name definition:
//
#define ClassImageLookCommand	"ImageLookCommand"

//
// Referenced classes.
//

//
// ImageLookCommand class definition:
//				
class ImageLookCommand : public NoUndoCommand
{
  private:
    //
    // Private member data:
    //
    ImageWindow *imageWindow;
    LookDirection direction;

  protected:
    //
    // Protected member data:
    //

    virtual bool doIt(CommandInterface *ci);


  public:
    //
    // Constructor:
    //
    ImageLookCommand(const char   *name,
		   CommandScope *scope,
		   bool       active,
		   ImageWindow  *w,
		   LookDirection dir);

    //
    // Destructor:
    //
    ~ImageLookCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassImageLookCommand;
    }
};


#endif // _ImageLookCommand_h
