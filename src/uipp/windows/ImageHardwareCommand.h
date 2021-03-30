/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"



#ifndef _ImageHardwareCommand_h
#define _ImageHardwareCommand_h


#include "NoUndoCommand.h"


//
// Class name definition:
//
#define ClassImageHardwareCommand	"ImageHardwareCommand"

//
// Referenced classes.
//
class ImageWindow;

//
// ImageHardwareCommand class definition:
//				
class ImageHardwareCommand : public NoUndoCommand
{
  private:
    //
    // Private member data:
    //
    ImageWindow *imageWindow;

  protected:
    //
    // Protected member data:
    //

    virtual bool doIt(CommandInterface *ci);


  public:
    //
    // Constructor:
    //
    ImageHardwareCommand(const char   *name,
		   CommandScope *scope,
		   bool       active,
		   ImageWindow  *w);

    //
    // Destructor:
    //
    ~ImageHardwareCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassImageHardwareCommand;
    }
};


#endif // _ImageHardwareCommand_h
