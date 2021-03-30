/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"


#ifndef _InsertNetworkDialog_h
#define _InsertNetworkDialog_h

#include "OpenNetworkDialog.h"

//
// Class name definition:
//
#define ClassInsertNetworkDialog	"InsertNetworkDialog"


//
// InsertNetworkDialog class definition:
//				
class InsertNetworkDialog: public OpenNetworkDialog 
{
    static bool ClassInitialized;

  protected:

    //static String  DefaultResources[];

    virtual void okFileWork(const char *string);

    //
    // For sub-classes of this dialog
    //
    InsertNetworkDialog(const char* name);

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
    InsertNetworkDialog();


    //
    // Destructor:
    //
    ~InsertNetworkDialog();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassInsertNetworkDialog;
    }
};


#endif // _InsertNetworkDialog_h
