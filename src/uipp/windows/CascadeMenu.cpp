/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

#include "CascadeMenu.h"
#include "DXStrings.h"
#include "ListIterator.h"


CascadeMenu::CascadeMenu(char* name) : UIComponent(name)
{
#define BUFLEN 100
#define NAME	"Submenu"
#define NAMELEN 7
    char *pulldownName, buffer[BUFLEN]; 
    int	len = STRLEN(name);


    if (len > BUFLEN-NAMELEN-1)
	pulldownName = new char[ len + NAMELEN];
    else
	pulldownName = buffer;

    sprintf(pulldownName,"%s%s",name,NAME);

    //this->subMenu = XmCreatePulldownMenu(parent, pulldownName, 
				//		NUL(ArgList), 0);

    //Widget cascade =  XtVaCreateManagedWidget
    //        (name,
    //         xmCascadeButtonWidgetClass,
    //         parent,
    //         XmNsubMenuId, subMenu, 
    //         NULL);

    //this->setRootWidget(cascade);

    if (pulldownName != buffer)
	delete pulldownName;
}


CascadeMenu::~CascadeMenu()
{
    this->clearComponents();
    // FIXME: when/if to destroy this.
    //        Does the parent own it or this class.
    // XtDestroyWidget(this->subMenu);
}

#if 0
//
// Build the cascaded menu. 
// This must be done before creating the components that will reside in the
// menu so that getMenuItemParent() can succeed.
//
void CascadeMenu::createMenu()
{
    this->clearComponents();

    //this->subMenu = XmCreatePulldownMenu(parent, "subMenu", NUL(ArgList), 0);

    //Widget cascade =  XtVaCreateManagedWidget
    //        (name,
    //         xmCascadeButtonWidgetClass,
    //         parent,
    //         XmNsubMenuId, subMenu, 
    //         NULL);

    //this->setRootWidget(cascade);
}
#endif

//
// Get the parent of the UIComponents that are to be added to the cascaded
// menu.
//
//Widget CascadeMenu::getMenuItemParent()
//{
//    ASSERT(this->subMenu);
//    return this->subMenu;
//}

//
// Append the given UIComponent to the sub menu and manage it.
//
bool CascadeMenu::appendComponent(UIComponent *uic)
{
    //ASSERT(this->subMenu == XtParent(uic->getRootWidget()));

    if (!this->componentList.appendElement(uic))
	return false;

    uic->manage(); 
    return true;
}
//
// Remove (but do not delete) the given UIComponent from the submenu and
// unmanage it.
//
bool CascadeMenu::removeComponent(UIComponent *uic)
{
    if (!this->componentList.removeElement(uic))
	return false;

    uic->unmanage();
    return true;
}
//
// Remove and delete the given UIComponent from the submenu. 
//
bool CascadeMenu::deleteComponent(UIComponent *uic)
{
    if (!this->componentList.removeElement(uic))
	return false;

    delete uic;
    return true;
}
//
// Remove and delete all UIComponents owned by the menu.
//
void CascadeMenu::clearComponents()
{
    UIComponent *uic;

    while ((uic = (UIComponent*)this->componentList.getElement(1))) {
	this->componentList.deleteElement(1);
	delete uic;
    }

}
//
// Set the label of the Cascade menu 
//
void CascadeMenu::setLabel(const char *label)
{
    //Arg      arg[1];
    //XmString name;

    //name = XmStringCreateSimple((char*)label);
    //XtSetArg(arg[0],XmNlabelString, name);
    //XtSetValues(this->getRootWidget(), arg, 1);

    //XmStringFree(name);

}


//
// Set the sensitivity of the cascade menu item based on the sensitivity
// of its immediate children.  If any are sensitive, then set the sensitivity
// to true (active) else not sensitive.  We return true if the cascade was
// set active, otherwise false.
//
bool CascadeMenu::setActivationFromChildren()
{
    UIComponent *uic;
    ListIterator iterator(this->componentList);
    bool active = false;

    while(!active && (uic = (UIComponent*)iterator.getNext())) {
	if (uic->isActivated())
	   active = true; 
    }

    if (active)
	this->activate();
    else
	this->deactivate();

    return active;
}
