/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"


#ifndef _InteractorInstance_h
#define _InteractorInstance_h



#include "DXStrings.h"
#include "Base.h"
#include "InteractorNode.h"


class List;
class Interactor;
class Node;
class Network;
class ControlPanel;
class InteractorStyle;
class SetAttrDialog;

//
// Class name definition:
//
#define ClassInteractorInstance	"InteractorInstance"


//
// Describes an instance of an interactor in a control Panel.
//
class InteractorInstance : public Base {

    friend class Interactor;
    friend void InteractorNode::openDefaultWindow();

  private:


  protected:

    char		*localLabel;
    Interactor		*interactor;
    ControlPanel	*controlPanel;
    int			xpos, ypos;
    int			width, height;
    InteractorStyle	*style;
    InteractorNode	*node;
    bool		selected;
    bool		verticalLayout;

    //
    // The dialog for setting attributes of the interactor.
    // This set in this->openDefaultWindow()
    //
    SetAttrDialog *setAttrDialog;

    //
    // Create the set attributes dialog.
    // This should also perform the function of this->loadSetAttrDialog().
    //
    virtual SetAttrDialog *newSetAttrDialog();

    //
    // Make sure the given output's current value complies with any attributes.
    // This is called by InteractorInstance::setOutputValue() which is
    // intern intended to be called by the Interactors.
    // If verification fails (returns false), then a reason is expected to
    // placed in *reason.  This string must be freed by the caller.
    // At this level we always return true (assuming that there are no
    // attributes) and set *reason to NULL.
    //
    virtual bool verifyValueAgainstAttributes(int output, 
					 	const char *val,
						dx_Type t,
						char **reason);
    virtual bool defaultVertical() { return true; }

    static int CountLines(const char*);
    static const char* FetchLine(const char*, int);

    char* java_var_name;
    virtual const char* javaName() { return "tfld"; }

  public:
    InteractorInstance(InteractorNode *n);
	
    ~InteractorInstance(); 

    void 	setPanel(ControlPanel *panel) 
				{ this->controlPanel= panel; }
    void 	setLocalLabel(const char *label); 

    void 	setXYPosition(int x, int y);
    void	setXYSize(int width, int height);

    void 	setStyle(InteractorStyle *is) 
				{ this->style = is; }
 
    bool 	isSelected()  { return this->selected ; }

    void 	setSelected(bool select);

    void 	setSelected() { this->setSelected(true); } 
    void 	clrSelected() { this->setSelected(false); } 
    virtual void setVerticalLayout(bool val = true); 
    bool	isVerticalLayout()  { return this->verticalLayout; }

    //
    // Ask the InteractorStyle to build an Interactor for this instance.
    //
    void	createInteractor();

    const char 		*getInteractorLabel();
    const char 		*getLocalLabel() { return this->localLabel; }
    void 		getXYPosition(int *x, int *y);	

    //
    // If the interactor for this instance exists, then return true
    // and the width and height in *x and *y respectively.
    // If the interactor does not exists return false and set *x and *y to 0.
    //
    bool getXYSize(int *x, int *y);


    InteractorStyle 	*getStyle() { return this->style; }
    ControlPanel 	*getControlPanel() { return this->controlPanel; }
    //Widget		getParentWidget();
				
    Interactor		*getInteractor() { return this->interactor; }
    Node		*getNode() 	{ return this->node; }
    Network		*getNetwork();

    void                changeStyle(InteractorStyle* style);    

    //
    // Delete an interactor in such a way that we could create another one
    // with createInteractor().
    //
    void uncreateInteractor();

    //
    // Send notification to this->interactor that the attributes may have 
    // changed and to reflect these changes in the display Interactor. 
    // Some changes can be ignored if 'this != src_ii'.  This is typically
    // called by InteractorNode::notifyInstancesOfStateChange().
    //
    void		handleInteractorStateChange(
				InteractorInstance *src_ii, 
				bool unmanage = false);

    bool isDataDriven() { InteractorNode *n = 
					(InteractorNode*)this->getNode();
			     return n->isDataDriven();
			   } 


    //
    // Return true/false indicating if this class of interactor instance has
    // a set attributes dialog (i.e. this->newSetAttrDialog returns non-NULL).
    // At this level in the class hierarchy, we return false.
    //
    virtual bool hasSetAttrDialog();

    //
    // Open the set attributes dialog for this Interactor.
    //
    void openSetAttrDialog();

    //
    // Make sure the given value complies with any attributes and if so
    // set the value in the Node.  This should generally be called from
    // interactors that can't directly enforce  attributes.  For example,
    // the Text style versus the Stepper style Vector interactor.  The
    // Stepper style enforces its attributes itself, but the Text style
    // accepts any value and then must have the value checked for type
    // and attribute compliance.
    // If we fail because attribute verification fails, then *reason contains
    // the reason (as passed back by verifyValueAgainstAttributes()) for
    // failure.  This string is expected to be freed by the caller.
    //
    bool setAndVerifyOutput(int index, const char *val, 
					dx_Type type, bool send,
					char **reason);

    //
    // Called from ControlPanel in the process of performing cut/copy + paste
    // of interactors within the control panels of one executable.  If possible
    // change the pointers so that this instance no long belongs to a temp net
    // but to the real network (passwd in in newnet). Return True on success.
    //
    bool switchNets (Network *newnet);

    virtual bool printAsJava(FILE* );
    virtual const char* getJavaVariable();

    const char *getClassName() 
	{ return ClassInteractorInstance; }
};

#endif // _InteractorInstance_h

