/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"


#ifndef _OpenCommand_h
#define _OpenCommand_h


#include "OptionalPreActionCommand.h"

class	Network;
class   DXApplication;

//
// Class name definition:
//
#define ClassOpenCommand	"OpenCommand"


//
// OpenCommand class definition:
//				
class OpenCommand : public OptionalPreActionCommand 
{
  private:

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
    OpenCommand(const char*   name,
                        CommandScope* scope,
                        bool       active,
			DXApplication *app);

    //
    // Destructor:
    //
    ~OpenCommand(){}


    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassOpenCommand;
    }
};


#endif // _OpenCommand_h
