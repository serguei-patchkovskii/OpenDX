/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"




#ifndef _SetMacroNameDialog_h
#define _SetMacroNameDialog_h


#include "Dialog.h"

//
// Class name definition:
//
#define ClassSetMacroNameDialog	"SetMacroNameDialog"

class Network;

//
// SetMacroNameDialog class definition:
//				
class SetMacroNameDialog : public Dialog
{
  private:
    //
    // Private member data:
    //

    static bool ClassInitialized;
    Network *network;

  protected:
    //
    // Protected member data:
    //
    //Widget macroName;
    //Widget category;
    //Widget description;


    //
    // Get the text from a text widget and clip off the leading and
    // trailing white space.
    // The return string must be deleted by the caller.
    //
    //static char *GetTextWidgetToken(Widget textWidget);

    //static String DefaultResources[];

    virtual bool okCallback(Dialog *d);
    virtual void createDialog();

    //
    // Constructor for the subclasses:
    //
    SetMacroNameDialog(const char *name, Network *n);

    //
    // Install the default resources for this class and then call the
    // same super class method to get the default resources from the
    // super classes.
    //
    //virtual void installDefaultResources(Widget baseWidget);

    //
    // Check the given name to see if it is a valid macro name.
    // If realMacro is true, then don't allow the name to be 'main'.
    // If it is return true, othewise return false and issue an error
    // message.
    //
    bool verifyMacroName(const char *name, bool realMacro);

  public:
    //
    // Constructor:
    //
    SetMacroNameDialog(Network *n);

    //
    // Destructor:
    //
    ~SetMacroNameDialog();


    virtual void manage();

    //
    // Returns a pointer to the class name.
    //
    virtual const char* getClassName()
    {
	return ClassSetMacroNameDialog;
    }
};


#endif // _SetMacroNameDialog_h
