/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"


#ifndef _PreActionCommand_h
#define _PreActionCommand_h


#include "NoUndoCommand.h"


//
// Class name definition:
//
#define ClassPreActionCommand	"PreActionCommand"

//
// PreActionCommand class definition:
//				
class PreActionCommand : public NoUndoCommand
{
  private:
    char* dialogQuestion;
    char* dialogTitle;

    static void YesDCB(void* clientData);
    static void NoDCB(void* clientData);
    static void CancelDCB(void* clientData);

  protected:
    //
    // Constructor:
    //
    //Widget dialogParent;

    PreActionCommand(const char*   name,
		     CommandScope* scope,
		     bool       active,
		     char*         dialogTitle,
		     char*         dialogQuestion);

    //
    // Must be implemented by subclasses.
    //
    virtual void doPreAction() {};

  public:
    //
    // Destructor:
    //
    ~PreActionCommand(){}

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
	return ClassPreActionCommand;
    }
};


#endif // _PreActionCommand_h
