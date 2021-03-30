/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"



#ifndef _ImageResetCommand_h
#define _ImageResetCommand_h


#include "NoUndoCommand.h"


//
// Class name definition:
//
#define ClassImageResetCommand	"ImageResetCommand"

//
// Referenced classes.
//
class ImageWindow;

//
// ImageResetCommand class definition:
//				
class ImageResetCommand : public NoUndoCommand
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
    ImageResetCommand(const char   *name,
		   CommandScope *scope,
		   bool       active,
		   ImageWindow  *w);

    //
    // Destructor:
    //
    ~ImageResetCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassImageResetCommand;
    }
};


#endif // _ImageResetCommand_h
