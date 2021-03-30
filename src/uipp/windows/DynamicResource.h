/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"





#ifndef _DynamicResource
#define _DynamicResource

#include "Base.h"

//
// Class name definition:
//
#define ClassDynamicResource	"DynamicResource"

//
// Identify widgets for which you want to set a resource.  Supply the data.
// This class maintains a list of all widgets to which to apply the setting
// and it maintains a single setting.  Supply print and parse functions so
// setting can be written out and read back in.
//



//
// DynamicResource class definition:
//				
class DynamicResource : public Base
{
  private:
    //
    // Private member data:
    //

    //
    // When you use qualified widget names to specify widgets, you need a root
    // from which to start a search in order to convert the name to a Widget.
    //
//    Widget root;

    //
    // true if this->setting.default_addr contains a value legal for XtSetValues.
    // storedData is set to false when a new value is supplied and set to true
    // after the Intrinsics' type converter has been invoked.
    //
    bool storedData;

    //
    // ... holds the name, type, value we're working with.
    //
//    XtResource setting;

    //
    // Perform the type conversion then stick the data into the widget.
    //
    bool applySetting (const char *name);

    //
    // widgetNames[i] is a the widget name part of an Xt resource spec of the
    // ith widget in a object for which we should set this resource.  If the value
    // of the DynamicResource changes, then set it for every widget in widgetNames.
    //
    char** widgetNames;
    int nameCnt;

    //
    // true if this->setting.resource_name exists every widget in widgetNames.
    // The object should be destroyed if it's created with valid_resource==false.
    //
    bool valid_resource;

    //
    // Hang onto the resource name because the resource might not be found until
    // after addWidgetToNameList.  Keep the stringRepresentation of the setting
    // for printComment.
    //
    char *resourceName;
    char *stringRepresentation;

    //static bool VerifyPresence (const char *, Widget, XtResource*);
    //static char *QualifiedWidgetName (Widget, Widget);
    //static char* *GrowNameList (char**, int *, const char *);
    //static void CopyResource (XtResource *, XtResource *);

  protected:
    //
    // Protected member data:
    //

    //virtual void initialize ();

  public:

    //
    // Supply a new string representation of the resource's value.  Will use
    // installed converters to get the real value.
    //
    bool setData (const char *);
    // Update the settings using XtSetValues using the existing data.
    bool setData ();

    //
    // Query functions
    //
    // Fetch the results of the data conversion.  Using ::setData and the ::getData
    // is similar to using the routine XtConvertAndStore by yourself.
    //
    void *getData ();
    const char *getResourceName() { return this->resourceName; }
    const char *getStringRepresentation() 
	{ return (const char *)this->stringRepresentation; }
    //bool inWidgetList (Widget w);

    //
    // Supply the real value.  Don't do any conversion.
    //
    bool setDataDirectly (void *);

    //
    // The root widget is changeable.  Whenever it is set, run thru the list of
    // names, verifying that a widget has a resource and then setting the resource.
    //
    //bool setRootWidget(Widget);


    bool isValidResource() { return this->valid_resource; }

    //
    // When adding a widget to the list, verify that this->setting.resource_name is
    // in the set of resources held by the widget of interest.  The name used will
    // be ...XtName(XtParent(dest)).XtName(dest)
    //
    // If allIntermediates is set to true, then automatically include all widgets
    // which are both children of root and ancestors of dest.  This facilitates
    // setting colors resources in objects made of several widgets.
    //
    //bool addWidgetToNameList (Widget dest, bool allIntermediates=false);
    // Add dest and all decendants thereof.
    //bool addWidgetsToNameList (Widget dest, bool allIntermediates=false);

    //
    // print and parse functions called by someone in WorkSpaceComponent
    // probably for reading and writing a .cfg file.  Ordinarily you would have
    // to have a Widget in order to accept a resource name, but we'll assume that
    // the resource is valid because it could only have been written by me.
    //
    bool printComment (FILE *);
    bool parseComment (const char *comment, const char *file, int line);

    //
    // Constructor:
    // Destructor:
    //
    DynamicResource(const char *resourceName);
    ~DynamicResource();

    //
    // Returns a pointer to the class name.
    //
    virtual const char* getClassName() { return ClassDynamicResource; }
};

#endif // _DynamicResource
