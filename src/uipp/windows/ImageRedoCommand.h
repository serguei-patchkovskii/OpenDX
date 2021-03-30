/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"




#ifndef _ImageRedoCommand_h
#define _ImageRedoCommand_h


#include "NoUndoCommand.h"


//
// Class name definition:
//
#define ClassImageRedoCommand	"ImageRedoCommand"

//
// Referenced classes.
//
class ImageWindow;

//
// ImageRedoCommand class definition:
//				
class ImageRedoCommand : public NoUndoCommand
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
    ImageRedoCommand(const char   *name,
		   CommandScope *scope,
		   bool       active,
		   ImageWindow  *w);

    //
    // Destructor:
    //
    ~ImageRedoCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassImageRedoCommand;
    }
};


#endif // _ImageRedoCommand_h
