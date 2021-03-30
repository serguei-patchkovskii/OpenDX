/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"




#ifndef _DXDropSite_h
#define _DXDropSite_h

#include "Base.h"
#include "List.h"
#include "Network.h"
#include "DropSite.h"


//
// Class name definition:
//
#define ClassDXDropSite	"DXDropSite"


//
// DropSite class definition:
//				
class DXDropSite : public DropSite 
{
  private:

    //
    // a strang thing for a dnd operation... conditionally refuse to engange 
    // in the ipc mechanism if the other end is in a separate process.  This is
    // needed by control panel dnd because you can't drop an interactor
    // into a different copy of dx.
    //
    bool intraExecutable;

  protected:

    //
    // DXDropSite class reads in temporary .net and .cfg files, creates the
    // temporary network and panels, and hands off to a required subclass'
    // method to merge the temp net and/or the temp panels.
    //
    virtual bool mergeNetElements (Network *tmpnet, List *tmppanels, int x, int y) = 0;

    //bool transfer(char *, XtPointer, unsigned long, int, int);

  public:

    //
    // Constructor:
    //
    DXDropSite(bool intraExecutable = false);
 
    //
    // Destructor:
    //
    ~DXDropSite(); 
  
    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassDXDropSite;
    }
};


#endif // _DXDropSite_h
