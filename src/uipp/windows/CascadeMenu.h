/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"




#ifndef _CascadeMenu_h
#define _CascadeMenu_h


#include "UIComponent.h"
#include "List.h"

//
// Class name definition:
//
#define ClassCascadeMenu	"CascadeMenu"


//
// Referenced classes:
//
class Command;
class CommandInterface;

//
// CascadeMenu class definition:
//				
class CascadeMenu : public UIComponent
{
  protected:
    List	componentList;	
    //Widget	subMenu;

  public:
    //
    // Constructor:
    //
    CascadeMenu(char* name);

    //
    // Destructor:
    //
    ~CascadeMenu();

    //
    // Get the parent of the UIComponents that are to be added to the cascaded
    // menu.  The name associated with this widget is the same as that passed
    // into the constructor with 'Submenu' appended.
    //
    //Widget getMenuItemParent();

    //
    // Append the given UIComponent to the sub menu and manage it.
    //
    bool appendComponent(UIComponent *uic);
    //
    // Remove (but do not delete) the given UIComponent from the submenu and
    // unmanage it.
    //
    bool removeComponent(UIComponent *uic);
    //
    // Remove and delete the given UIComponent from the submenu.
    //
    bool deleteComponent(UIComponent *uic);
    //
    // Remove and delete all UIComponents owned by the menu.
    //
    void clearComponents();

    //
    // Set the label of the Cascade menu
    //
    void setLabel(const char *label);

    //
    // Set the sensitivity of the cascade menu item based on the sensitivity
    // of its immediate children.  If any are sensitive, then set the 
    // sensitivity to true (active) else not sensitive.  We return true if 
    // the cascade was set active, otherwise false.
    //
    bool setActivationFromChildren();


    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassCascadeMenu;
    }

};


#endif // _CascadeMenu_h
