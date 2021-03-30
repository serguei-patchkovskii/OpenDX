/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

#ifndef _BaseApp_h
#define _BaseApp_h

#include "UIComponent.h"
#include "Server.h"

//
// Class name definition:
//
#define ClassApplication	"BaseApp"

//
// XtCallbackProc (*CB), XtEventHandler (*EH) and XtActionProc (*AP)
// DialogCallback (*DCB) functions for this and derived classes
//
//extern "C" void Application_XtWarningHandler(char*);
//extern "C" int  Application_XErrorHandler(Display *display, XErrorEvent *event);

//
// Application class definition:
//				
class BaseApp : public UIComponent, public Server
{
  private:
    //
    // Private class data:
    //
    static bool ApplicationClassInitialized;	

    int 	busyCursors; 	// Keeps track of setBusyCursor calls.

    //
    // The main program needs to access protected member functions.
    //
    friend int main(unsigned int argc,
		     char**       argv);


    //
    // Bubble help information
    //
    bool  show_bubbles;
    //Widget   help_viewer;

  protected:
    //
    // Protected member data:
    //
    char*        applicationClass;	// application class name

    //
    // Initialize the window system.
    //
    virtual bool initializeWindowSystem(unsigned int *argcp, char **argv);

    virtual void parseCommand(unsigned int* argcp, char** argv);

    //
    // Handles application events.
    //   This routine should be called by main() only.
    //
//    virtual void handleEvent(XEvent *xev);

    //
    // Load application specific action routines
    //
    virtual void addActions() {}

    //
    // Post the copyright notice that is returned by this->getCopyrightNotice().
    // If it returns NULL, then don't post any notice.
    //
    virtual void postCopyrightNotice();

    //
    // Handle Xt Warnings (called by Application_XtWarningHandler, static, above)
    // Handle X Errors (called by XErrorHandler, static, above)
    //
    //virtual void handleXtWarning(char *message);
    //virtual int  handleXError(Display *display, XErrorEvent *event);

    //
    // Constructor for the subclasses:
    //
    BaseApp(char* className);

    //
    // Install the default resources for this class and then call the
    // same super class method to get the default resources from the
    // super classes.
    //
    //virtual void installDefaultResources(Widget baseWidget);

    //
    // test the file to ensure that's is a regular file, and writable.
    //
    bool isUsableDefaultsFile(const char* res_file, bool create=false);

  public:
    //
    // Busy indicator cursor to be used globally:
    //
    //static Cursor BusyCursor;

    // Currently used only for debugging. 
    //static void DumpApplicationResources(const char *filename);

    //
    // Notification messages:
    //
    static Symbol MsgCreate;
    static Symbol MsgManage;
    static Symbol MsgUnmanage;
    static Symbol MsgSetBusyCursor;
    static Symbol MsgResetCursor;
    static Symbol MsgManageByLeafClassName;
    static Symbol MsgUnmanageByLeafClassName;
    static Symbol MsgManageByTitle;
    static Symbol MsgUnmanageByTitle;

    //
    // Initializes the Xt Intrinsics (creating the first widget),
    // by calling initializeWindowSytstem() if not already called.
    // Initializes any Application specfic state.  This routine should 
    // be called by main() or subclasses only.
    //
    virtual bool initialize(unsigned int* argcp, char** argv);

    //
    // Allow others to access our event processing mechanism
    //
    //void passEventToHandler(XEvent *xev) { this->handleEvent(xev); }

    //
    // Virtual methods that are called by Command::ExecuteCommandCallback()
    // before and after Command::execute().
    // Send a message to all clients that we are beginngin/ending execution
    // of a command.
    //
    virtual void startCommandInterfaceExecution(); 
    virtual void endCommandInterfaceExecution();

    //
    // Destructor:
    //
    ~BaseApp();

    //
    // Manages all the application windows.
    //
    void manage();

    //
    // Unmanages all the application windows.
    //
    void unmanage();

    //
    // Iconfies all the application windows.
    //
    void iconify();

    //
    // Sets/resets busy cursor for the application.
    // Calls to this routine can be 'stacked' so that the first call
    // sets the cursor and the last call resets the cursor.
    // setBusyCursor(true);         // Sets busy cursor
    // setBusyCursor(true);         // does not effect cursor
    // setBusyCursor(true);         // does not effect cursor
    // setBusyCursor(false);        // does not effect cursor
    // setBusyCursor(true);         // does not effect cursor
    // setBusyCursor(false);        // does not effect cursor
    // setBusyCursor(false);        // does not effect cursor
    // setBusyCursor(false);        // resets cursor
    //
    void setBusyCursor(bool setting);

    //
    // Shutdown application (without deleting it out from under itself.
    //
    virtual void shutdownApplication() = 0;
    
    //
    // Returns the Display pointer.
    //
 //   Display* getDisplay()
 //   {
	//return this->display;
 //   }

    //
    // Returns the application context pointer.
    //
 //   XtAppContext getApplicationContext()
 //   {
	//return this->applicationContext;
 //   }

    //
    // Returns the application class name.
    //
    const char* getApplicationClass()
    {
	return this->applicationClass;
    }

    //
    // Return the name of the application (i.e. 'Data Explorer', 
    // 'Data Prompter', 'Medical Visualizer'...).
    //
    virtual const char *getInformalName();

    //
    // Return the formal name of the application (i.e. 
    // 'Open Visualization Data Explorer', 'Open Visualization Data Prompter'...)
    //
    virtual const char *getFormalName();

    //
    // Get the applications copyright notice, for example...
    // "Copyright International Business Machines Corporation 1991-1993 
    // All rights reserved"
    //
    virtual const char *getCopyrightNotice();

    //
    // Displays any help required.
    //
    virtual void helpOn(const char *topic);
    virtual const char *getHelpDirectory();
    virtual const char *getHelpDirFileName();
    virtual const char *getHTMLDirectory();
    virtual const char *getHTMLDirFileName();

    //
    // Start a tutorial on behalf of the application.
    // Return true if successful.  At this level in the class hierachy
    // we don't know how to start a tutorial so we always return false.
    //
    virtual bool startTutorial();

    //
    // Return a pixmap with the logo in it.
    //
    //virtual Pixmap getLogoPixmap(bool ){return XtUnspecifiedPixmap;};
    virtual void cleanupLogo(){};

    //
    // Return a pixmap with the icon in it.
    //
    //virtual Pixmap getIconPixmap(){return XtUnspecifiedPixmap;};

    //
    // A virtual method that allows other applications to handle ASSERT
    // failures among other things.
    //
    virtual void abortApplication();

    //
    // Control the display of bubble help
    //
    virtual bool bubbleHelpEnabled() { return this->show_bubbles; }
    virtual void    enableBubbleHelp (bool state = true) 
	{ this->show_bubbles = state; }
    //virtual void    setHelpViewer (Widget viewer) { this->help_viewer = viewer; }
    //virtual Widget  getHelpViewer () { return this->help_viewer; }

    virtual void handleEvents();

    virtual bool getApplicationDefaultsFileName(char* res_file, bool create=false);

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassApplication;
    }
};

//
// Pointer to the single (hopefully) global instance:
//
extern BaseApp* theApplication;


#endif // _BaseApp_h
