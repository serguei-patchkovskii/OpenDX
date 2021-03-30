/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"




#include "NondrivenInteractorNode.h"

//
// Constructor 
//
NondrivenInteractorNode::NondrivenInteractorNode(NodeDefinition *nd,
			Network *net, int instance) :
                        InteractorNode(nd, net, instance)
{
    // This is only relevant if the interactor is being data driven, but
    // turns caching off for those interactors that are.
    // FIXME: this should be in the mdf
    // this->setNodeCacheability(NotCached);
}

//
//
//
bool NondrivenInteractorNode::isDataDriven()
{
    return false;
}
//
// Define the mapping of inputs that shadow outputs.
// non-data-driven interactors do not have inputs. 
//
int NondrivenInteractorNode::getShadowingInput(int output_index)
{
    return 0;
}
int NondrivenInteractorNode::handleNodeMsgInfo(const char *line)
{
    ASSERT(0);
    return 0;
}
int  NondrivenInteractorNode::handleInteractorMsgInfo(const char *line)
{
    ASSERT(0);
    return 0;
}




//
// Determine if this node is of the given class.
//
bool NondrivenInteractorNode::isA(Symbol classname)
{
    Symbol s = theSymbolManager->registerSymbol(ClassNondrivenInteractorNode);
    if (s == classname)
	return true;
    else
	return this->InteractorNode::isA(classname);
}
