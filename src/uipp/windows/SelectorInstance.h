/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"




#ifndef _SelectorInstance_h
#define _SelectorInstance_h



#include "DXStrings.h"
#include "SelectorNode.h"
#include "SelectionInstance.h"

class SelectorInteractor;


//
// Class name definition:
//
#define ClassSelectorInstance	"SelectorInstance"


//
// Describes an instance of an interactor in a control Panel.
//
class SelectorInstance : public SelectionInstance {

  private:


  protected:

    virtual const char* javaName() { return "pdown"; }

  public:
    SelectorInstance(InteractorNode *node) : SelectionInstance(node) {}
	
    ~SelectorInstance()  {}

    int 	getSelectedOptionIndex();

    void setSelectedOptionIndex(int index, bool update_outputs = true);

    virtual bool printAsJava(FILE* );

    const char *getClassName() 
		{ return ClassSelectorInstance; }
};

#endif // _SelectorInstance_h

