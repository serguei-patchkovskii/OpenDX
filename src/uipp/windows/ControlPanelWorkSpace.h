/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"




#ifndef _ControlPanelWorkSpace_h
#define _ControlPanelWorkSpace_h


#include "WorkSpace.h"
#include "DXDropSite.h"


//
// Class name definition:
//
#define ClassControlPanelWorkSpace	"ControlPanelWorkSpace"

class ControlPanel;
class WorkSpaceInfo;

//
// ControlPanelWorkSpace class definition:
//				
class ControlPanelWorkSpace : public WorkSpace, public DXDropSite
{
  private:

    //
    // Private member data:
    //

    static bool ControlPanelWorkSpaceClassInitialized;

    //static String DefaultResources[];

    //
    // if set to false, then reject all drops -- for user mode control panels
    //
    bool dropPermission;

    //
    // For use during autoArrange mode, record the difference between the size
    // of the enclosing dialog box and the size of the workspace widget.  Do this
    // so that the workspace widget can be resized along with the dialog box.
    // Recall that the contents of a scrolledWindow won't be forced to grow or
    // shrink if the scrollWindow resizes.  With this extra info, the resize
    // method can maintain a close association.
    //
    int widthDelta, heightDelta;

    // 1 per class... Holds the data types this drop site can swallow.  It's set
    // up during class initialization.
    static Dictionary *DropTypeDictionary;

    // 1 enum for each type of data we can swallow in a dnd operation.  
    // The Nodes constant is for dragging StandIns from the vpe to a panel.
    enum {
	Interactors,
	Nodes,
	Text
    };
#if defined(WANT_DND_FOR_TEXT)
    static void SetOwner(void*);
    static void DeleteSelections(void*);
#endif


  protected:

    //
    // Protected member data:
    //
    ControlPanel	*controlPanel;

    //
    // Called when the workspace background gets a double click.
    //
    //void doDefaultAction(Widget w, XtPointer callData);

    //
    // Called when the workspace background gets a single click.
    //
    //void doBackgroundAction(Widget w, XtPointer callData);
    //void doSelectionAction(Widget w, XtPointer callData);

    //
    // Drag and Drop related stuff
    //
    bool mergeNetElements (Network *tmpnet, List *tmppanels, int x, int y);
    //bool compoundTextTransfer (char *, XtPointer, unsigned long, int, int);
    //bool decodeDropType (int, char *, XtPointer, unsigned long, int, int);

    virtual Dictionary *getDropDictionary() 
	{ return ControlPanelWorkSpace::DropTypeDictionary; }

  public:
    //
    // Constructor:
    //
    ControlPanelWorkSpace(const char *name, 
			  WorkSpaceInfo *info, ControlPanel *cp);
			
    //
    // Destructor:
    //
    ~ControlPanelWorkSpace(){}

    //
    // One time class initialization.
    //
    void initializeRootWidget(bool fromFirstIntanceOfADerivedClass = false);

    //
    // Turn on/off drops
    //
    void dropsPermitted (bool onoff);

    //
    // Supply a resize method which chains to that of the parent class
    // except if the workspace is in autoArrange mode - user mode.
    //
    virtual void resize();
    void setSizeDeltas (int w, int h) {this->widthDelta = w; this->heightDelta = h;}

    //
    // Get the bounding box of the children which are selected
    //
    virtual void getSelectedBoundingBox (int *minx, int *miny, int *maxx, int *maxy);

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassControlPanelWorkSpace;
    }
};


#endif // _ControlPanelWorkSpace_h
