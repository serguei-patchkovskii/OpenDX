/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"




#ifndef _ImageConstraintCommand_h
#define _ImageConstraintCommand_h


#include "NoUndoCommand.h"
#include "ImageWindow.h"


//
// Class name definition:
//
#define ClassImageConstraintCommand	"ImageConstraintCommand"

//
// Referenced classes.
//

//
// ImageConstraintCommand class definition:
//				
class ImageConstraintCommand : public NoUndoCommand
{
  private:
    //
    // Private member data:
    //
    ImageWindow *imageWindow;
    ConstraintDirection direction;

  protected:
    //
    // Protected member data:
    //

    virtual bool doIt(CommandInterface *ci);


  public:
    //
    // Constructor:
    //
    ImageConstraintCommand(const char   *name,
		   CommandScope *scope,
		   bool       active,
		   ImageWindow  *w,
		   ConstraintDirection dir);

    //
    // Destructor:
    //
    ~ImageConstraintCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassImageConstraintCommand;
    }
};


#endif // _ImageConstraintCommand_h
