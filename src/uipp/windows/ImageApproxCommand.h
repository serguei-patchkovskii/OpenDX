/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"




#ifndef _ImageApproxCommand_h
#define _ImageApproxCommand_h


#include "NoUndoCommand.h"
#include "ImageWindow.h"


//
// Class name definition:
//
#define ClassImageApproxCommand	"ImageApproxCommand"

//
// Referenced classes.
//

//
// ImageApproxCommand class definition:
//				
class ImageApproxCommand : public NoUndoCommand
{
  private:
    //
    // Private member data:
    //
    ImageWindow *imageWindow;
    bool    up;
    ApproxMode mode;

  protected:
    //
    // Protected member data:
    //

    virtual bool doIt(CommandInterface *ci);


  public:
    //
    // Constructor:
    //
    ImageApproxCommand(const char   *name,
		   CommandScope *scope,
		   bool       active,
		   ImageWindow  *w,
		   bool      up,
		   ApproxMode   mode);

    //
    // Destructor:
    //
    ~ImageApproxCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassImageApproxCommand;
    }
};


#endif // _ImageApproxCommand_h
