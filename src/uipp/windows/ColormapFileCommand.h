/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"


#ifndef _ColormapFileCommand_h
#define _ColormapFileCommand_h


#include "NoUndoCommand.h"


//
// Class name definition:
//
#define ClassColormapFileCommand	"ColormapFileCommand"

class ColormapEditor;

//
// ColormapFileCommand class definition:
//				
class ColormapFileCommand : public NoUndoCommand
{

  private:
    ColormapEditor    *editor;
    bool		opening;

  protected:
    //
    // Implements the command:

    virtual bool doIt(CommandInterface *ci);

  public:
    //
    // Constructor:
    //
    ColormapFileCommand(const char*     name,
                        CommandScope*   scope,
                        bool         active,
                        ColormapEditor* editor,
			bool		opening);


    //
    // Destructor:
    //
    ~ColormapFileCommand();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassColormapFileCommand;
    }
};


#endif // _ColormapFileCommand_h
