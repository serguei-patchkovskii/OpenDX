/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"


#ifndef _OptionalPreActionCommand_h
#define _OptionalPreActionCommand_h

#include "PreActionCommand.h"


//
// Class name definition:
//
#define ClassOptionalPreActionCommand	"OptionalPreActionCommand"


//
// OptionalPreActionCommand class definition:
//				
class OptionalPreActionCommand : public PreActionCommand
{
  private:

  protected:
    //
    // Constructor:
    //
    OptionalPreActionCommand(const char*   name,
		     CommandScope* scope,
		     bool       active,
		     char*         dialogTitle,
		     char*         dialogQuestion);

    virtual bool needsConfirmation() = 0;

  public:
    //
    // Destructor:
    //
    ~OptionalPreActionCommand(){}

    //
    // Overrides the supperclass execute() function:
    //   First posts a dialog to ask for user confirmation before
    //   actually executing the command.
    //
    virtual bool execute(CommandInterface *ci = NULL);

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassOptionalPreActionCommand;
    }
};


#endif // _OptionalPreActionCommand_h
