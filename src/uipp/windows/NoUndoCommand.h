/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

#ifndef _NoUndoCommand_h
#define _NoUndoCommand_h


#include "Command.h"


//
// NoUndoCommand class definition:
//				
class NoUndoCommand : public Command
{
  protected:
    //
    // No op for this class...
    //
    virtual bool undoIt()
    {
	return false;
    }

    //
    // Constructor:
    //   Protected to prevent direct instantiation.
    //
    NoUndoCommand(const char*   name,
		  CommandScope* scope,
		  bool       active);

  public:
    //
    // Destructor:
    //
    ~NoUndoCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return "NoUndoCommand";
    }
};


#endif /*  _NoUndoCommand_h */
