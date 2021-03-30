/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"


#ifndef _ConfirmedExitCommand_h
#define _ConfirmedExitCommand_h


#include "OptionalPreActionCommand.h"


class   DXApplication;
class   Command;

//
// Class name definition:
//
#define ClassConfirmedExitCommand	"ConfirmedExitCommand"


//
// ConfirmedExitCommand class definition:
//				
class ConfirmedExitCommand : public OptionalPreActionCommand 
{
  private:

    Command     *command;
    DXApplication *application;

  protected:
    //
    // Implements the command:

    virtual bool needsConfirmation();
    virtual void    doPreAction();

  public:
    //
    // Constructor:
    //
    ConfirmedExitCommand(const char*   name,
                        CommandScope* scope,
                        bool       active,
			DXApplication *app);

    //
    // Destructor:
    //
    ~ConfirmedExitCommand(){}

    bool doIt(CommandInterface*);

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassConfirmedExitCommand;
    }
};


#endif // _ConfirmedExitCommand_h
