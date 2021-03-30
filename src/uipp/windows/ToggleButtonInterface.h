/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

#ifndef _ToggleButtonInterface_h
#define _ToggleButtonInterface_h


#include "CommandInterface.h"


//
// Class name definition:
//
#define ClassToggleButtonInterface	"ToggleButtonInterface"


//extern "C" void ToggleButtonInterface_ExecuteCommandCB(Widget, 
//		XtPointer, XtPointer);

//
// ToggleButtonInterface class definition:
//				
class ToggleButtonInterface : public CommandInterface
{
  private:
    //
    // Private class data:
    //
    static bool ToggleButtonInterfaceClassInitialized;

    //
    // Private member data:
    //
    bool state;	// state of toggle button

    //
    // Calls the CommandInterface executeCommand method.
    //
    void tbExecuteCommand();

  public:
    //
    // Notification messages:
    //
    static Symbol MsgToggleOn;
    static Symbol MsgToggleOff;
    static Symbol MsgToggleState;

    //
    // Constructor:
    //
    ToggleButtonInterface(
			  char*    name,
			  Command* command,
			  bool  state,
			  const char *bubbleHelp = NULL);

    //
    // Destructor:
    //
    ~ToggleButtonInterface(){}

    //
    // Override of superclass notify() function:
    //   Handles additional messages:
    //     DXToolPanelCommand::MsgToggleOn
    //     DXToolPanelCommand::MsgToggleOff
    //
    virtual void notify
	(const Symbol message, const void *data=NULL, const char *msg=NULL);

    //
    // Toggles current state.
    //
    void toggleState();

    //
    // Changes current state to new setting.
    //
    void setState(const bool state, const bool notify=true);

    //
    // Returns the current stateof the toggle button.
    //
    bool getState();

    //friend void ToggleButtonInterface_ExecuteCommandCB(Widget    widget,
				//       XtPointer clientData,
				//       XtPointer callData);
    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassToggleButtonInterface;
    }
};


#endif // _ToggleButtonInterface_h
