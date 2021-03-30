/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"





#ifndef _LoadMacroDialog_h
#define _LoadMacroDialog_h



#include "OpenNetworkDialog.h"


//
// Class name definition:
//
#define ClassLoadMacroDialog	"LoadMacroDialog"

//
// XtCallbackProc (*CB), XtEventHandler (*EH) and XtActionProc (*AP)
// DialogCallback (*DCB), XtInputCallbackProc (*ICP), XtWorkProc (*WP)
// functions for this and derived classes
//
//extern "C" void LoadMacroDialog_LoadDirectoryCB(Widget, XtPointer, XtPointer);
//

class Dialog;

//
// LoadMacroDialog class definition:
//				
class LoadMacroDialog : public OpenNetworkDialog
{
    static bool ClassInitialized;

    //friend void LoadMacroDialog_LoadDirectoryCB(Widget widget, 
				//	XtPointer clientData,
    //                                 	XtPointer callData);
    bool doingOk;

  protected:

    //static String  DefaultResources[];
    virtual bool okCallback(Dialog *d);
    virtual void okFileWork(const char *string);
    virtual void createDialog();

    //
    // For sub-classes of this dialog
    //
    LoadMacroDialog(const char* name);

    //
    // Install the default resources for this class and then call the
    // same super class method to get the default resources from the
    // super classes.
    //
    //virtual void installDefaultResources(Widget baseWidget);

  public:
    //
    // Constructor:
    //
    LoadMacroDialog();

    //
    // Destructor:
    //
    ~LoadMacroDialog(){}

    virtual void unmanage();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassLoadMacroDialog;
    }
};


#endif // _LoadMacroDialog_h
