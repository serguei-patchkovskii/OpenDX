/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"



#ifndef _ImageSetModeCommand_h
#define _ImageSetModeCommand_h


#include "NoUndoCommand.h"
#include "ImageWindow.h"


//
// Class name definition:
//
#define ClassImageSetModeCommand	"ImageSetModeCommand"

//
// Referenced classes.
//

//
// ImageSetModeCommand class definition:
//				
class ImageSetModeCommand : public NoUndoCommand
{
  private:
    //
    // Private member data:
    //
    ImageWindow *imageWindow;
    DirectInteractionMode mode;

  protected:
    //
    // Protected member data:
    //

    virtual bool doIt(CommandInterface *ci);


  public:
    //
    // Constructor:
    //
    ImageSetModeCommand(const char   *name,
		   CommandScope *scope,
		   bool       active,
		   ImageWindow  *w,
		   DirectInteractionMode mode);

    //
    // Destructor:
    //
    ~ImageSetModeCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassImageSetModeCommand;
    }
};


#endif // _ImageSetModeCommand_h
