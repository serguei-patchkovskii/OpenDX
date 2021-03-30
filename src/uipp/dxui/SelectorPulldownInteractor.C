/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "../base/defines.h"



#include <Xm/Xm.h>
#include <Xm/RowColumn.h>
#include <Xm/Form.h>
#include <Xm/ToggleB.h>
#include "XmUtility.h"

#include "defines.h"
#include "SelectorPulldownInteractor.h"
#include "InteractorStyle.h"

#include "SelectorNode.h"

#include "SelectorInstance.h"
#include "DXApplication.h"
#include "ListIterator.h"
#include "ErrorDialogManager.h"
#include "TextSelector.h"

boolean SelectorPulldownInteractor::ClassInitialized = FALSE;

String SelectorPulldownInteractor::DefaultResources[] =  {
	"*XmToggleButton.shadowThickness:	0",
        "*XmToggleButton.selectColor:         White",
	"*allowHorizontalResizing:			True",

	NUL(char*) 
};

SelectorPulldownInteractor::SelectorPulldownInteractor(const char *name,
		 InteractorInstance *ii) : Interactor(name,ii)
{
}

//
// One time class initializations.
//
void SelectorPulldownInteractor::initialize()
{
    //
    // Initialize default resources (once only).
    //
    if (NOT SelectorPulldownInteractor::ClassInitialized)
    {
        ASSERT(theApplication);
        this->setDefaultResources(theApplication->getRootWidget(),
                                  SelectorPulldownInteractor::DefaultResources);
        this->setDefaultResources(theApplication->getRootWidget(),
                                  Interactor::DefaultResources);
        SelectorPulldownInteractor::ClassInitialized = TRUE;
    }
}


static Widget CreateStepperComponent(Widget,  boolean, double, double,
				     double, double, int,   XtCallbackProc,   
				     int, caddr_t) ;

//
// Allocate an interactor 
//
Interactor *SelectorPulldownInteractor::AllocateInteractor(
				const char *name, InteractorInstance *ii)
{

    SelectorPulldownInteractor *si = new SelectorPulldownInteractor(name,ii);
    return (Interactor*)si;
}

//
//
extern "C" void SelectorPulldownInteractor_SelectionCB
    (Widget widget, XtPointer clientData, XtPointer)
{
    SelectorPulldownInteractor *spi = (SelectorPulldownInteractor*)clientData;
    ASSERT(spi);
    SelectorInstance *sin = (SelectorInstance*)spi->interactorInstance;
    ASSERT(sin);
    int selno = spi->text_selector->getSelectedItem();
    if (selno)
	sin->setSelectedOptionIndex(selno, TRUE);
}

//
// Perform anything that needs to be done after the parent of 
// this->interactivePart has been managed.
//
void SelectorPulldownInteractor::completeInteractivePart()
{
    SelectorInstance	*si = (SelectorInstance*)this->interactorInstance;
}
//
// Build the selector interactor option menu. 
// Note that we also use this to rebuild the list of options seen in the menu
// In this case the  
//
Widget SelectorPulldownInteractor::createInteractivePart(Widget form)
{
    SelectorNode	*node;
    SelectorInstance	*si = (SelectorInstance*)this->interactorInstance;
    Pixel bg,fg;
    int n;
    Arg wargs[5];

    ASSERT(si);

    node = (SelectorNode*)si->getNode();

    ASSERT(form);
    ASSERT(node);
    ASSERT(EqualString(node->getClassName(), ClassSelectorNode));

    XtVaGetValues (form, XmNbackground, &bg, XmNforeground, &fg, NULL);
    this->text_selector = new TextSelector();
    this->text_selector->createTextSelector(form, (XtCallbackProc)
	SelectorPulldownInteractor_SelectionCB, (XtPointer)this);
    this->text_selector->manage();

    // 
    // Build the option menu 
    //
    this->reloadMenuOptions();

    return this->text_selector->getRootWidget();
}
//
// [Re]load the options into this->pulldown.
//
void SelectorPulldownInteractor::reloadMenuOptions()
{
    SelectorInstance *si = (SelectorInstance*) this->interactorInstance;
    int ocnt = si->getOptionCount();
    int i;

    String* items = new String[ocnt];
    for (i=0; i<ocnt; i++) {
	const char* cp = si->getOptionNameString(i+1);
	ASSERT(cp);
	items[i] = DuplicateString (cp);
    }
    this->text_selector->setItems (items, ocnt); 
    for (i=0; i<ocnt; i++) {
	delete items[i];
    }
    delete items;

    this->text_selector->setSelectedItem (si->getSelectedOptionIndex());
}


//
// Update the displayed values for this interactor.
//
void SelectorPulldownInteractor::updateDisplayedInteractorValue()
{
    SelectorInstance *si = (SelectorInstance*)this->interactorInstance;
    ASSERT(si);

    //
    // There are no options, so there is nothing to update.
    //
    if (si->getOptionCount() <= 0)
	return;

    this->text_selector->setSelectedItem (si->getSelectedOptionIndex());
}

//
// Make sure the attributes match the resources for the widgets.
//
void SelectorPulldownInteractor::handleInteractivePartStateChange(
					InteractorInstance *src_ii,
					boolean major_change)
{
    if (major_change)
	this->unmanage();

    this->reloadMenuOptions();

    if (major_change)
	this->manage();
}

void SelectorPulldownInteractor::layoutInteractorVertically()
{
    XtVaSetValues(this->text_selector->getRootWidget(),
		  XmNleftAttachment,	XmATTACH_FORM,
		  XmNrightAttachment,	XmATTACH_FORM,
		  NULL);
    Interactor::layoutInteractorVertically();
}
void SelectorPulldownInteractor::layoutInteractorHorizontally()
{
    XtVaSetValues(this->text_selector->getRootWidget(),
		  XmNleftAttachment,	XmATTACH_NONE,
		  XmNrightAttachment,	XmATTACH_FORM,
		  NULL);
    Interactor::layoutInteractorHorizontally();
}

void SelectorPulldownInteractor::setAppearance (boolean developerStyle)
{
    this->Interactor::setAppearance(developerStyle);

    //
    // Force the color change inside the menu pane of the ... button
    //
    Pixel fg,bg,ts,bs,arm;
    Screen* screen;
    Colormap cmap;
    XtVaGetValues (this->text_selector->getRootWidget(),
	XmNbackground, &bg,
	XmNforeground, &fg,
	XmNtopShadowColor, &ts,
	XmNbottomShadowColor, &bs,
	XmNscreen, &screen,
	XmNcolormap, &cmap,
    NULL);
    XmGetColors (screen, cmap, bg, NULL, NULL, NULL, &arm);
    Arg args[9];
    int n = 0;
    XtSetArg (args[n], XmNforeground, fg); n++;
    XtSetArg (args[n], XmNbackground, bg); n++;
    XtSetArg (args[n], XmNtopShadowColor, ts); n++;
    XtSetArg (args[n], XmNbottomShadowColor, bs); n++;
    XtSetArg (args[n], XmNarmColor, arm); n++;
    XtSetArg (args[n], XmNtroughColor, arm); n++;
    XtSetArg (args[n], XmNselectColor, arm); n++;

    this->text_selector->setMenuColors (args, n);
}
