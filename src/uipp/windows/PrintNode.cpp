/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

#include <string.h>

#include "PrintNode.h"
#include "DXApplication.h"
#include "MsgWin.h"
static char *message_token = "PRINT";

PrintNode::PrintNode(NodeDefinition *nd, Network *net, int instnc) :
    ModuleMessagingNode(nd, net, instnc)
{
}

PrintNode::~PrintNode()
{
}

//
// Called when a message is received from the executive after
// this->ExecModuleMessageHandler() is registered in
// this->Node::netPrintNode() to receive messages for this node.
// The format of the message coming back is defined by the derived class.
//
void PrintNode::execModuleMessageHandler(int id, const char *line)
{
    const char *p = strstr(line,message_token);

    if (p) {
        MsgWin *mw = theDXApplication->getMessageWindow();
        if (theDXApplication->doesInfoOpenMessage(true))
	    mw->infoOpen();
    }
}

//
// Returns a string that is used to register
// this->ExecModuleMessageHandler() when this->hasModuleMessageProtocol()
// return true.  This version, returns an id that is unique to this
// instance of this node.
//
const char *PrintNode::getModuleMessageIdString()
{
     if (!this->moduleMessageId)
        this->moduleMessageId = DuplicateString(message_token);
     return (const char*) this->moduleMessageId;

}


//
// Determine if this node is of the given class.
//
bool PrintNode::isA(Symbol classname)
{
    Symbol s = theSymbolManager->registerSymbol(ClassPrintNode);
    if (s == classname)
	return true;
    else
	return this->ModuleMessagingNode::isA(classname);
}
