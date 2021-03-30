/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

#ifndef _MainWindow_h
#define _MainWindow_h

#include "UIComponent.h"
#include "Client.h"


//
// Class name definition:
//
#define ClassMainWindow	"MainWindow"

//
// XtCallbackProc (*CB), XtEventHandler (*EH) and XtActionProc (*AP)
// DialogCallback (*DCB) functions for this and derived classes
//
//extern "C" void MainWindow_PopdownCB(Widget, XtPointer, XtPointer);
//extern "C" void MainWindow_HelpCB(Widget, XtPointer, XtPointer);
//extern "C" void MainWindow_CloseCB(Widget, XtPointer, XtPointer);

class CommandScope;

//
// Customized help callback record definition:
//
typedef struct
{
    int		reason;
    //XEvent*     event;
    //Widget	widget;

} MainWindowHelpCallbackStruct;


//
// Customized help callback reason:
//
#define DxCR_HELP	9001


//
// MainWindow class definition:
//				
class MainWindow : public UIComponent, public Client
{
  private:

    //
    // use the size of mwm borders during setGeometry.
    //
    static int WmOffsetX;
    static int WmOffsetY;
    static bool IsMwmRunning;
    // set to true if (XmIsMotifWMRunning() == false && exists(_MOTIF_WM_INFO))
    // This happens when displaying on dec and screws up window placement.
    // Note that on such a screen -geom cmd line option puts a window at the wrong
    // spot even if its not a Xt application.
    static bool IsMwmBroken;
    static bool OffsetsInitialized;

    static void InitializeOffsets ();

    //
    // XmNhelpCallback callback routine for this class:
    //
    //friend void MainWindow_CloseCB(Widget    widget,
			 //    XtPointer clientData,
			 //    XtPointer callData);

    //friend void MainWindow_HelpCB(Widget    widget,
			 //    XtPointer clientData,
			 //    XtPointer callData);

    //friend void MainWindow_PopdownCB(Widget    widget,
			 //    XtPointer clientData,
			 //    XtPointer callData);


  protected:
    //
    // These resources are expected to be loaded by the derived classes.
    //
    //static String DefaultResources[];

    //
    // Protected member data:
    //
    //Widget  main;	// XmMainWindow widget
    //Widget  menuBar;	// menu bar
    void *  workArea;	// work area widget created by derived class
    //Widget  commandArea; // command area widget created by derived class
    bool resizable;
    bool managed;	// True if the window has been managed.
    char    *title;	// The title being used for this window.
    bool hasMenuBar;		// Do we create the menuBar. 

    short	createX;	// X position of shell used at creation.
    short	createY;	// Y position of shell used at creation.
    short	createWidth;	// Width of shell used at creation.
    short	createHeight;	// Width of shell used at creation.

    void    allowResize(bool resizable);

    CommandScope                *commandScope;


    //
    // Derived classes must define this function to
    // create the window-specific work area.
    //
    virtual void* createWorkArea() = 0;

    //
    // Most derived classes will not want this.  It provides a look like
    // a dialog box.  The purpose is to accomodate ControlPanels which need
    // to alter their appearance in a major way without changing class hierarchy.
    //
    //virtual Widget createCommandArea (Widget ) { return 0; }

    //
    // This routine is called by initialize() function to create
    // the menus for the menubar in the window.
    // This function is defined here for windows that do not have
    // menu bars (i.e. hasMenuBar == false), so should never be called.
    //
    //virtual void createMenus(Widget parent);

    //
    // Overridden by DXWindow to put anchor up first
    //
    //virtual void createMenuBar(Widget parent);

    //
    // Provides context help.
    //
    virtual void provideContextHelp();

    //
    // Window closing callback called by MainWindow_PopdownCB().
    //
    virtual void popdownCallback();

    //
    // Set the name used in the window icon.
    // This will not take effect until the window has been realized, but is
    // intended to be called by the derived class during initialization
    // (i.e. createWorkArea()).
    //
    void setIconName(const char *name);

 //   Widget getWorkArea()
 //   {
	//return this->workArea;
 //   }

 //   Widget getCommandArea()
 //   {
	//return this->commandArea;
 //   }

 //   Widget getMenuBar()
 //   {
	//return this->menuBar;
 //   }

    //
    // Constructor for the subclasses:
    //
    MainWindow(const char* name, bool hasMenuBar = true);

    //
    // Install the default resources for this class and then call the
    // same super class method to get the default resources from the
    // super classes.
    //
    //virtual void installDefaultResources(Widget baseWidget);


    //
    // Allow subclasses to supply a string for the XmNgeometry resource 
    // (i.e. -geam 90x60-0-0) which we'll use instead of createX,createY,
    // createWidth, createHeight when making the new window.  If the string
    // is available then initialize() won't call setGeometry.
    //
    virtual const char* getGeometryString();
    virtual void getGeometryNameHierarchy(char** names, int* count, int max);
    virtual void getGeometryAlternateNames(char** names, int* count, int max);
    char* geometry_string;

  public:

    //
    // Destructor:
    //
    ~MainWindow();

    //
    // Creates and initializes the window.
    //
    virtual void initialize();

    //
    // returns true if this window is currently "popped up" or managed.
    //
    virtual bool isManaged();

    //
    // Manages the window.
    //
    virtual void manage();

    //
    // Implementation of notify() function for this class:
    //
    virtual void notify
	(const Symbol message, const void *data=NULL, const char *msg=NULL);


    //
    // Unmanages the window.
    //
    virtual void unmanage();

    //
    // Iconifies (minimizes) the window.
    //
    virtual void iconify();

    //
    // Returns true if the object has been initialized,
    //   i.e., the window root widget has been created.
    //
    bool isInitialized()
    {
//	return this->getRootWidget() != NUL(Widget);
		return false;
    }

    //
    // Access routines:
    //
//    Widget getMainWindow()
//    {
////	return main;
//    }

    //
    // G/Set the name/title of this window.
    //
    const char *getWindowTitle();
    virtual void setWindowTitle(const char *name, bool check_geometry=false);

    //
    // S/Get the size and dimensions.
    //
    virtual void setGeometry(int  x, int  y, int  width, int  height);
    virtual bool getGeometry(int *x, int *y, int *width, int *height);

    //
    // Window closing callback called by MainWindow_CloseCB().
    //
    virtual void closeWindow();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassMainWindow;
    }
};


#endif // _MainWindow_h
