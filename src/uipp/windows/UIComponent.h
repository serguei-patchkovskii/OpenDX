/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include <string.h>
#include <vcclr.h>

using namespace System::Windows::Forms;

#include "defines.h"

#ifndef _UIComponent_h
#define _UIComponent_h

#include "Base.h"

//
// Class name definition:
//
#define ClassUIComponent	"UIComponent"

//
// XtCallbackProc (*CB), XtEventHandler (*EH) and XtActionProc (*AP)
// DialogCallback (*DCB) functions for this and derived classes
//
//extern "C" void UIComponent_ComponentHelpCB(Widget, XtPointer, XtPointer);
//extern "C" void UIComponent_WidgetDestroyCB(Widget, XtPointer, XtPointer);
//extern "C" void UIComponent_BubbleEH (Widget, XtPointer, XEvent*, Boolean*);
//extern "C" void UIComponent_InstallBubbleTP (XtPointer, XtIntervalId*);


//
// UIComponent class definition:
//				
class UIComponent : virtual public Base
{
  private:
    //
    // XmNdestroyCallback callback routine for this class:
    //
    //friend void UIComponent_WidgetDestroyCB(Widget    widget,
				//      XtPointer clientData,
				//      XtPointer callData);
    //friend void UIComponent_ComponentHelpCB(Widget    widget,
			 //    XtPointer clientData,
			 //    XtPointer callData);
    //friend void UIComponent_BubbleEH (Widget, XtPointer, XEvent*, Boolean*);
    //friend void UIComponent_InstallBubbleTP (XtPointer, XtIntervalId*);

    //Widget  root;	// root widget of the component

#define NO_STIPPLE 1
    // SUITS local stuff needed to turn on/off stipple
#ifdef NO_STIPPLE
#   define DXD_NO_STIPPLE 1
    //XtTranslations  xtt;
    //Pixel           fg;
    bool         deactivated;
#endif 

    char*	help_msg;
    char*	inactive_help_msg;
    //Widget	help_widget;
    //static      XtIntervalId BubbleTimer;

  protected:
    //
    // Protected member data:
    //

    char*   name;	// component name
    bool active;	// is component active?

	// Windows.Forms application context.
	gcroot<System::Windows::Forms::ApplicationContext*> applicationContext;

    //
    // Constructor:
    //   Protected to prevent direct instantiation.
    //
    UIComponent(const char* name);

    void clearRootWidget();
//    virtual void setRootWidget(Widget root, bool standardDestroy = true);

//    void setBubbleHelp (const char *msg, Widget w = NULL, bool active_help = true);
    void showBubbleHelp();
    void eraseBubbleHelp();


    //
    // Called by UIComponent_WidgetDestroyCB() if root widget is destroyed.
    // This routine can be overriden by subclasses, but, at this level,
    // the "root" variable is reset to make sure it isn't referenced
    // accidentally again.
    //
    virtual void widgetDestroyed();

    //
    // Loads component's default resources into database.
    // This allows overrideable defaults to be set for certain resources.
    // This function should normally be called by the derived class
    // before any widgets are created, in case any resources
    // apply to the component's root widget.
    //
    //void setDefaultResources(const Widget  widget,
			 //    const String* resourceSpec);

    //
    // This routine by default installs a standard help callback, and is
    // called in setRootWidget.
    // It can also be called to install help callbacks on widgets other than
    // the root widget by setting w.
    //
    //virtual void installComponentHelpCallback(Widget w = NULL);
    //virtual void removeComponentHelpCallback( Widget w = NULL);

    //
    // This routine allows the user to override the standard help topic for
    // a UIComponent, which is the component name.
    virtual const char *getComponentHelpTopic();


  public:
    //
    // Destructor:
    //
    ~UIComponent();

    //
    // The following are constant understood by setGeometry() and used by
    // setXYPosition() and setXYSize() and subclasses.
    //
    static const int UnspecifiedPosition;
    static const int UnspecifiedDimension;

    //
    // Print/parse a comment that represents the given geometry.  The
    // geometry is printed/parsed normalized to the display.  The tag
    // is optional and defaults to "window".  It is prepended to the
    // comment (i.e. "// <tag>:...").
    //
    static bool PrintGeometryComment(FILE *f, int xpos, int ypos,
				int xsize, int ysize, 
				const char *tag=NULL,
				const char *indent=NULL);
    static bool ParseGeometryComment(const char *line, const char *file,
				int lineno, int *xpos, int *ypos, 
				int *xsize, int *ysize, const char *tag=NULL) ;


    //
    // Determines if the the component widget is managed.
    // Return false if the widget is not built yet.
    //
    virtual bool isManaged();

    //
    // Manages the the component widget tree.
    //
    virtual void manage();

    //
    // Unmanages the component widget tree.
    //
    virtual void unmanage();

    //
    // Activates the component widget tree and/or marks the component
    // as active.
    //
    virtual void activate();

    //
    // Deactivates the component widget tree and/or marks the component
    // as inactive.
    //
    virtual void deactivate(const char *reason = NUL(char*));

	Form* getMainForm() 
	{
		return this->applicationContext->get_MainForm();
	}

    //
    // Returns the root widget of the component.
    //
	
	//   Widget getRootWidget()
 //   {
	//return this->root;
 //   }

    //
    // S/Get the size of this component
    //
    virtual void setXYSize(int x, int y);
    virtual void getXYSize(int *x, int *y);

    //
    // S/Get the position of this ui component 
    //
    virtual void setXYPosition(int  x, int  y);
    virtual void getXYPosition(int *x, int *y);

    //
    // S/Get the size and dimensions.
    //
    virtual void setGeometry(int  x, int  y, int  width, int  height);
    //
    // Get the size and dimensions.
    // Return true if all return values are valid.
    //
    virtual bool getGeometry(int *x, int *y, int *width, int *height);

    //
    // S/Get data saved locally with this UIComponent.
    // WARNING: these are only to be used by leaf instances and should 
    //		therfore not be used to implement a class's internals.	
    // NOTE: Originally placed here for the ButtonInterface's allocated
    //	in dxui/Network::fillCascadeMenu().
    // 
    void setLocalData(void *data);
    void *getLocalData();

    //
    // Ask the application to get help for this component
    //
    virtual void componentHelp();


    bool isActivated() { return this->active; }

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassUIComponent;
    }
};


#endif // _UIComponent_h
