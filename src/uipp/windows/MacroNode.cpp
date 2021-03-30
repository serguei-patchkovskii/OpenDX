/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"




#include "MacroNode.h"
#include "MacroDefinition.h"
#include "Parameter.h"
#include "Network.h"
#include "DXApplication.h"

MacroNode::MacroNode(NodeDefinition *nd, Network *net, int instnc) :
    Node(nd, net, instnc)
{
}

MacroNode::~MacroNode()
{
    MacroDefinition *d = (MacroDefinition*)this->getDefinition();
    d->dereference(this);
}

bool
MacroNode::initialize()
{
    MacroDefinition *d = (MacroDefinition*)this->getDefinition();
    d->reference(this);

    this->Node::initialize();
    return true;
}
//
// Handle changing numbers and types of parameters. . .
void MacroNode::updateDefinition()
{
    this->Node::updateDefinition();
}

bool MacroNode::sendValues(bool     ignoreDirty)
{
    MacroDefinition *md = (MacroDefinition *)this->getDefinition();
    md->updateServer();
    return this->Node::sendValues(ignoreDirty);
}

void MacroNode::openMacro()
{
    MacroDefinition *md = (MacroDefinition *)this->getDefinition();
    md->openMacro();
}
//
// Determine if this node is of the given class.
//
bool MacroNode::isA(Symbol classname)
{
    Symbol s = theSymbolManager->registerSymbol(ClassMacroNode);
    if (s == classname)
	return true;
    else
	return this->Node::isA(classname);
}

bool MacroNode::hasJavaRepresentation()
{
    return (EqualString(this->getNameString(), "WebOptions"));
}



bool MacroNode::printInputAsJava(int i)
{
    if (EqualString(this->getNameString(), "WebOptions") == false) return false;
    bool retval = false;
    switch (i) {
	case 1:
	case 9:
	case 10:
	    retval = true;
	    break;
    }
    return retval;
}
