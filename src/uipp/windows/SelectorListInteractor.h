/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"


#ifndef _SelectorListInteractor_h
#define _SelectorListInteractor_h

 
#include "Interactor.h"
#include "List.h"

//
// Class name definition:
//
#define ClassSelectorListInteractor	"SelectorListInteractor"

//
// XtCallbackProc (*CB), XtEventHandler (*EH) and XtActionProc (*AP)
// DialogCallback (*DCB), XtInputCallbackProc (*ICP), XtWorkProc (*WP)
// functions for this and derived classes
//
//extern "C" void SelectorListInteractor_SelectCB(Widget, XtPointer, XtPointer);


//
// SelectorListInteractor class definition:
//				
class SelectorListInteractor : public Interactor
{
  private:
    //
    // Private member data:
    //
    //Widget list_widget;
    bool single_select;

    //void enableCallbacks (bool enab = true);
    //void disableCallbacks () { this->enableCallbacks(false); }

  protected:
    //
    // Protected member data:
    //

    //
    // One widget for each component (scalar or n-vector).
    //

    static bool ClassInitialized;

    //static String DefaultResources[];

    //friend void SelectorListInteractor_SelectCB(Widget , XtPointer , XtPointer );

    //
    // [Re]load the options into this->pulldown.
    //
    void reloadListOptions();

    virtual void completeInteractivePart(){}

  public:
    //
    // Constructor:
    //
    SelectorListInteractor(const char *name, InteractorInstance *ii);

    //
    // Allocate this class 
    //
    static Interactor *AllocateInteractor(const char *name, InteractorInstance *ii) {
	return new SelectorListInteractor(name, ii);
    }

    //
    // Accepts value changes and reflects them into other interactors, cdbs
    // and off course the interactor node output.
    //
    void applyCallback();

    //
    // Destructor:
    //
    ~SelectorListInteractor(){}

    //
    // Update the displayed values for this interactor.
    //
    void updateDisplayedInteractorValue(void);

    //
    // 
    //
    //Widget createInteractivePart(Widget p);

    //
    // Make sure the attributes match the resources for the widgets. 
    //
    void handleInteractivePartStateChange(InteractorInstance *, bool );

    //
    // Added to be able to override the developer style selectColor
    //
    void setAppearance(bool );

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassSelectorListInteractor;
    }
};


#endif // _SelectorListInteractor_h
