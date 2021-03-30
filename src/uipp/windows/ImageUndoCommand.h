/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"




#ifndef _ImageUndoCommand_h
#define _ImageUndoCommand_h


#include "NoUndoCommand.h"


//
// Class name definition:
//
#define ClassImageUndoCommand	"ImageUndoCommand"

//
// Referenced classes.
//
class ImageWindow;

//
// ImageUndoCommand class definition:
//				
class ImageUndoCommand : public NoUndoCommand
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
    ImageUndoCommand(const char   *name,
		   CommandScope *scope,
		   bool       active,
		   ImageWindow  *w);

    //
    // Destructor:
    //
    ~ImageUndoCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassImageUndoCommand;
    }
};


#endif // _ImageUndoCommand_h
