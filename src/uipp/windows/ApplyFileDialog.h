/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"


#ifndef _ApplyFileDialog_h
#define _ApplyFileDialog_h


#include "FileDialog.h"

//
// Class name definition:
//
#define ClassApplyFileDialog	"ApplyFileDialog"


//
// ApplyFileDialog class definition:
//				
class ApplyFileDialog : public dxui::FileDialog
{
    static bool ClassInitialized;

  protected:

    //static String  DefaultResources[];

    //
    // Call super class and then set the dialog title and the dirMask resource. 
    //
    virtual void createDialog();

    //
    // Used to call this->okFileWork().
    //
    virtual void helpCallback(Dialog *d);

    //
    // Constructor: for derived classes
    //
    ApplyFileDialog(const char* name);

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
    ApplyFileDialog();

    //
    // Destructor:
    //
    ~ApplyFileDialog(){}

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassApplyFileDialog;
    }
};

#endif // _ApplyFileDialog_h
