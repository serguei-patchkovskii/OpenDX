/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"




#include "AttributeParameter.h"

AttributeParameter::AttributeParameter(ParameterDefinition *pd, 
		Node *n, int index) : BinaryParameter(pd)
{ 
    this->set2ndValue("NULL");
    this->node = n; 
    this->index = index;
    this->syncOnTypeMatch = true;
}
//
// Copy the parameter value into the Attribute value.
//
bool  AttributeParameter::syncAttributeValue() 
{
    if (this->hasValue()) {
	dx_Type t = this->getValueType();
	const char *v = this->getSetValueString();
	return  this->set2ndValue(v,t,false);
    } else 
	return true;

}


//
// Make sure that the primary parameter has the same value as the
// attribute when appropriate.  Appropriate is defined as the primary
// parameter having a value and a type which is the same as the attribute's.
//
bool  AttributeParameter::syncPrimaryValue(bool force) 
{
    if (force || this->syncOnTypeMatch) {
	dx_Type t = this->get2ndValueType();
	if (force || (this->hasValue() && this->getValueType() == t)) {
	    ASSERT(this->isInput());
	    const char *v = this->get2ndValueString();
	    return this->node->setInputSetValue( this->index,v,t,false) != 
			DXType::UndefinedType;
        }
    }
    return true;
}

//
// Determine if the attribute that shadows this parameter is writeable. 
// Attributes are writeable if the primary parameter is not connected
// and (the primary parameter is defaulting or the value has the same 
// type as the attribute value.
//
bool  AttributeParameter::isAttributeVisuallyWriteable()
{ 
    return this->isDefaulting();
}


//
// Determine if this parameter is of the given class.
//
bool AttributeParameter::isA(Symbol classname)
{
    return 
      (classname == theSymbolManager->registerSymbol(ClassAttributeParameter))
	||
      this->Parameter::isA(classname);
}
