/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"



#ifndef _SetScalarAttrDialog_h
#define _SetScalarAttrDialog_h



#include "SetAttrDialog.h"


//
// Class name definition:
//
#define ClassSetScalarAttrDialog	"SetScalarAttrDialog"

//
// XtCallbackProc (*CB), XtEventHandler (*EH) and XtActionProc (*AP)
// DialogCallback (*DCB), XtInputCallbackProc (*ICP), XtWorkProc (*WP)
// functions for this and derived classes
//
//extern "C" void SetScalarAttrDialog_NumberWarningCB(Widget, XtPointer, XtPointer);
//extern "C" void SetScalarAttrDialog_ToggleCB(Widget, XtPointer, XtPointer);
//extern "C" void SetScalarAttrDialog_UpdateOptionsCB(Widget, XtPointer, XtPointer);
//extern "C" void SetScalarAttrDialog_IncrementOptionsCB(Widget, XtPointer, XtPointer);
//extern "C" void SetScalarAttrDialog_StepperCB(Widget, XtPointer, XtPointer);
//extern "C" void SetScalarAttrDialog_NumberCB(Widget, XtPointer, XtPointer);

//
// Referenced Classes
//
class InteractorInstance;
class LocalAttributes;
class ScalarInstance;

struct _ScalarAttr {
	double minimum, maximum;
	bool usingGlobalIncrement;
	double globalIncrementValue;  
	double localIncrementValue;  
	int	decimals;
	bool minSensitive, maxSensitive;
	bool globalIncrementSensitive, decimalsSensitive;
}; 


//
// SetScalarAttrDialog class definition:
//				
class SetScalarAttrDialog : public SetAttrDialog
{
  private:
    //
    // Private member data:
    //
    static bool ClassInitialized;

    //friend void SetScalarAttrDialog_NumberCB(Widget	 widget,
		  //       XtPointer clientData,
		  //       XtPointer callData);
    //friend void SetScalarAttrDialog_StepperCB(Widget	 widget,
		  //       XtPointer clientData,
		  //       XtPointer callData);
    //friend void SetScalarAttrDialog_IncrementOptionsCB(Widget	 widget,
		  //       XtPointer clientData,
		  //       XtPointer callData);
    //friend void SetScalarAttrDialog_UpdateOptionsCB(Widget	 widget,
		  //       XtPointer clientData,
		  //       XtPointer callData);
    //friend void SetScalarAttrDialog_ToggleCB(Widget	 widget,
		  //       XtPointer clientData,
		  //       XtPointer callData);

    //friend void SetScalarAttrDialog_NumberWarningCB(Widget w, 
    //                     XtPointer clientData, 
			 //XtPointer callData);
  
    void initInstanceData(ScalarInstance *si);

  protected:
    //
    // Protected member data:
    //
    //static String DefaultResources[];

    struct _ScalarAttr *attributes; 
 
    int    numComponents;		// This is saved for convenience.

    bool usingGlobalContinuous;
    bool globalContinuousValue;
    bool localContinuousValue;

    //Widget maxLabel, maxNumber;
    //Widget minLabel, minNumber;
    //Widget incrementOptions, incrementNumber;
    //Widget globalIncrement, localIncrement;
    //Widget decimalsLabel, decimalsStepper;
    //Widget updateOptions, updateToggle;
    //Widget globalUpdate, localUpdate;

    //Widget createUpdatePulldown(Widget parent, const char *name);
    //Widget createIncrementPulldown(Widget parent, const char *name);

    //
    // Build the interactive set attributes widgets that sit in the dialog.
    //
    virtual void createAttributesPart();

    virtual bool okCallback(Dialog *clientData); 

    //
    // Indicate whether to update all attributes when a dialog attribute
    // is changed.  At this level we return false, but provide this 
    // to allow others (i.e. SetVectorAttrDialog) to indicate that
    // all values are to be updated.
    //
    bool updateAllAttributes();

    //
    // Copy all the values from the given components dialog saved attributes
    // into the other dialog saved attributes.
    // 
    void updateAllAttributes(int component_index);

    //
    // Indicate whether to update all attributes when a dialog attribute
    // is changed.  At this level we return false, but provide this
    // to allow others (i.e. SetVectorAttrDialog) to indicate that
    // all values are to be updated.
    //
    virtual bool isAllAttributesMode();

    //
    // Desensitize the data-driven attributes in the dialog.
    //
    virtual void setAttributeSensitivity();

    //
    // Make sure the range of values accepted in the increment number
    // widget is goes from 0 to (current_max - current_min);
    //
    void adjustIncrementBounds();

    //
    // Constructor (for derived classes only):
    //
    SetScalarAttrDialog(const char *name,
			const char *title, ScalarInstance *si);

    //
    // Install the default resources for this class and then call the
    // same super class method to get the default resources from the
    // super classes.
    //
    //virtual void installDefaultResources(Widget baseWidget);

  public:
    //
    // Constructor (instances of THIS class only):
    //
    SetScalarAttrDialog(const char *title, ScalarInstance *si);

    //
    // Destructor:
    //
    ~SetScalarAttrDialog();

    //
    // Used by displayAttributes() to determine which component of
    // of vector to work on.  At this level we always return 1 and assume
    // either a Scalar or Integer interactor.
    //
    virtual int getCurrentComponentNumber();

    // 
    // Does the work on behalf of this->updateDisplayedAttributes().  For Scalar
    // interactors component is always 1; component can be varied for
    // SetVectorAttrDialogs.
    //
    void updateDisplayedComponentAttributes(int component);

    virtual void loadAttributes();
    virtual bool storeAttributes();
    virtual void updateDisplayedAttributes();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassSetScalarAttrDialog;
    }
};


#endif // _SetScalarAttrDialog_h
