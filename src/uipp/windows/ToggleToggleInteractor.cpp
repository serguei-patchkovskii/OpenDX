/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

#include "ToggleNode.h"
#include "ToggleInstance.h"
#include "ToggleToggleInteractor.h"
#include "InteractorStyle.h"

bool 
  ToggleToggleInteractor::ToggleToggleInteractorClassInitialized = false;

//
// Define the mapping of toggle states (Up/down) to option indices (1/2).
//
#define OPTION_TO_SETTING(opt) 	   ( (opt) == 1 ? True : False)
#define SETTING_TO_OPTION(setting) ( (setting) == True ? 1 : 2 )

//String ToggleToggleInteractor::DefaultResources[] =  {
//	NUL(char*) 
//};

ToggleToggleInteractor::ToggleToggleInteractor(const char *name,
		 InteractorInstance *ii) : 
			ToggleInteractor(name,ii)
{
}

//
// One time class initializations.
//
void ToggleToggleInteractor::initialize()
{
    //
    // Initialize default resources (once only).
    //
    if (NOT ToggleToggleInteractor::ToggleToggleInteractorClassInitialized)
    {
        //ASSERT(theApplication);
        //this->setDefaultResources(theApplication->getRootWidget(),
        //                         ToggleToggleInteractor::DefaultResources);
        //this->setDefaultResources(theApplication->getRootWidget(),
        //                         ToggleLblToggleInteractor::DefaultResources);
        //this->setDefaultResources(theApplication->getRootWidget(),
        //                         ToggleInteractor::DefaultResources);
        //this->setDefaultResources(theApplication->getRootWidget(),
        //                         Interactor::DefaultResources);
        ToggleToggleInteractor::ToggleToggleInteractorClassInitialized = true;
    }
}


//
// Allocate a toggle style interactor for a selector instance. 
//
Interactor *ToggleToggleInteractor::AllocateInteractor(
			const char *name,
			InteractorInstance *ii)
{

    ToggleToggleInteractor *ti = new ToggleToggleInteractor(name,ii);
    return (Interactor*)ti;
}
//
// Accepts value changes and reflects them into other interactors, cdbs
// and of course the interactor node output.
//
//void ToggleToggleInteractor::toggleCallback(Widget w,
//                                                Boolean set, XtPointer cb)
//{
//    ToggleInstance *ti = (ToggleInstance*)this->interactorInstance;
//    ToggleNode        *tnode;
//  
//    tnode       = (ToggleNode*)ti->getNode();
//
//    if (set)
//	tnode->set();
//    else
//	tnode->reset();
//}

//
// Update the displayed values for this interactor.
//
void ToggleToggleInteractor::updateDisplayedInteractorValue()
{
    bool set;
    ToggleInstance *ti = (ToggleInstance*)this->interactorInstance;
    ASSERT(ti);
    ToggleNode        *tnode = (ToggleNode*)ti->getNode();

    //
    // There are no options, so there is nothing to update.
    //
    if (tnode->isSet())
	set = true;
    else
	set = false;

    //XtVaSetValues(this->toggleButton, XmNset, set, NULL);

}

