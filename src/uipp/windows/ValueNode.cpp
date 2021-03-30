/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"




 
#include "ValueNode.h"
#include "ValueInstance.h"

//
// The Constructor... 
//
ValueNode::ValueNode(NodeDefinition *nd, Network *net, int instnc) :
                        NondrivenInteractorNode(nd, net, instnc)
{ 

}

//
// Destructure: needs to delete all its instances. 
//
ValueNode::~ValueNode()
{
}

bool ValueNode::initialize()
{
    dx_Type t = this->setOutputValue(1,"NULL", DXType::UndefinedType, false);
    return t == DXType::UndefinedType ? false : true;
}

InteractorInstance* ValueNode::newInteractorInstance()
{
    ValueInstance *ii;

    ii = new ValueInstance(this);

    return ii;
}
//
// Determine if this node is of the given class.
//
bool ValueNode::isA(Symbol classname)
{
    Symbol s = theSymbolManager->registerSymbol(ClassValueNode);
    if (s == classname)
	return true;
    else
	return this->NondrivenInteractorNode::isA(classname);
}
