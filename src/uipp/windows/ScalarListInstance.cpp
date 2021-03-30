/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"




#include "ScalarListInstance.h"
#include "ScalarListNode.h"
#include "LocalAttributes.h"

ScalarListInstance::ScalarListInstance(ScalarListNode *n) :
                ScalarInstance((ScalarNode*)n)
{
}
	
ScalarListInstance::~ScalarListInstance() 
{
}

//
// S/Get value associated with this interactor instance.
// ScalarListInstances have a component value that is always local to
// the instance (i.e. saved in the LocalAttributes list).
//
double ScalarListInstance::getComponentValue(int component)
{ 
  LocalAttributes *la = this->getLocalAttributes(component);
  ASSERT(la);
  return la->getValue();
}

void ScalarListInstance::setComponentValue(int component, double val)
{ 
  LocalAttributes *la = this->getLocalAttributes(component);
  ASSERT(la);
  la->setValue(val);
}

//
// Make sure the given output's current value complies with any attributes.
// This is called by InteractorInstance::setOutputValue() which is
// intern intended to be called by the Interactors.
// If verification fails (returns false), then a reason is expected to
// placed in *reason.  This string must be freed by the caller.
// At this level we always return true (assuming that there are no
// attributes) and set *reason to NULL.
//
bool ScalarListInstance::verifyValueAgainstAttributes(int output,
					    	const char *val,
                                                dx_Type t,
                                                char **reason)
{
    dx_Type itemtype = t & DXType::ListTypeMask;
    int index = -1;
    char buf[1024];
    bool r = true;

    if (reason)
	*reason = NULL;

    while (r && DXValue::NextListItem(val,&index,t,buf)) 
	r = this->verifyVSIAgainstAttributes(buf, itemtype, reason);
   
    return r; 
}
