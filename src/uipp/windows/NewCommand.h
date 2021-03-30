/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"


#ifndef _NewCommand_h
#define _NewCommand_h


#include "OptionalPreActionCommand.h"
#include "Network.h"


//
// Class name definition:
//
#define ClassNewCommand	"NewCommand"


//
// NewCommand class definition:
//				
class NewCommand : public OptionalPreActionCommand
{
  private:
    //
    // Private member data:
    //
    Network *network;

  protected:
    //
    // Protected member data:
    //
    virtual bool needsConfirmation();
    virtual void    doPreAction();

    virtual bool doIt(CommandInterface *ci);

  public:
    //
    // Constructor:
    //
    NewCommand(const char      *name,
	       CommandScope    *scope,
	       bool		active,
	       Network	       *net);


    //
    // Destructor:
    //
    ~NewCommand(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassNewCommand;
    }
};


#endif // _NewCommand_h
