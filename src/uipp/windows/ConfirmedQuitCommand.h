/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"


#ifndef _ConfirmedQuitCommand_h
#define _ConfirmedQuitCommand_h


#include "OptionalPreActionCommand.h"

class   DXApplication;
class   Command;

//
// Class name definition:
//
#define ClassConfirmedQuitCommand	"ConfirmedQuitCommand"


//
// ConfirmedQuitCommand class definition:
//				
class ConfirmedQuitCommand : public OptionalPreActionCommand 
{
  private:

    Command     *command;
    DXApplication *application;

  protected:
    //
    // Implements the command:

    virtual bool needsConfirmation();
    virtual void    doPreAction();
    virtual bool doIt(CommandInterface *ci);

  public:
    //
    // Constructor:
    //
    ConfirmedQuitCommand(const char*   name,
                        CommandScope* scope,
                        bool       active,
			DXApplication *app);

    //
    // Destructor:
    //
    ~ConfirmedQuitCommand();


    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassConfirmedQuitCommand;
    }
};


#endif // _ConfirmedQuitCommand_h
