/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"



#include "IBMVersion.h"
#include "ReceiverNode.h"
#include "TransmitterNode.h"
#include "ParameterDefinition.h"

#include "Ark.h"
#include "ConfigurationDialog.h"
#include "ListIterator.h"
#include "ErrorDialogManager.h"
#include "WarningDialogManager.h"
#include "Network.h"
#include "EditorWindow.h"
#include "lex.h"


// FIXME: should be static class data
static bool initializing = false;

ReceiverNode::ReceiverNode(NodeDefinition *nd, Network *net, int instnc) :
    UniqueNameNode(nd, net, instnc)
{
}
bool ReceiverNode::initialize()
{
    const char *label;

    label = this->getLabelString(); 
    Network *net = this->getNetwork();
    EditorWindow *editor = net->getEditor();
    if (!net->isReadingNetwork() && editor) {
	TransmitterNode *tmtr = editor->getMostRecentTransmitterNode();
	if (tmtr)
	    label = tmtr->getLabelString();
    }
    initializing = true;
    this->setLabelString(label);
    initializing = false;

    return true;
}

ReceiverNode::~ReceiverNode()
{
}


//
// Is this receiver connected to a Transmitter.
//
bool ReceiverNode::isTransmitterConnected()
{
    return this->isInputConnected(1);
}

char *ReceiverNode::netNodeString(const char *prefix)
{
    char      *string = new char[200];
    char      *outputParam;

    outputParam = this->outputParameterNamesString(prefix);
    sprintf(string,"%s = %s;\n", outputParam, this->getLabelString());

    delete outputParam;
    return string;
}

//
// When a Receiver gets a new label, it has to disconnect from its existing
// transmitter, and connect to the new one.  This will work even if it's
// the transmitter that's changing our label.
bool ReceiverNode::setLabelString(const char *label)
{
    if (EqualString(label, this->getLabelString()))
	return true;

    if (initializing && this->getNetwork()->isReadingNetwork()) 
        return this->UniqueNameNode::setLabelString(label);

    if (!this->verifyRestrictedLabel(label))
	return false;

    //
    // Skip the conflict check when reading in a newer style net since
    // there can't be any conflict in these nets.
    //
    const char* conflict = NUL(char*);
    if (this->getNetwork()->isReadingNetwork()) {
        int net_major = this->getNetwork()->getNetMajorVersion();
        int net_minor = this->getNetwork()->getNetMinorVersion();
        int net_micro = this->getNetwork()->getNetMicroVersion();
        int net_version =   VERSION_NUMBER( net_major, net_minor, net_micro);
        if (net_version < VERSION_NUMBER(3,1,1))
	    conflict = this->getNetwork()->nameConflictExists(this, label);
    }

    //
    // If there is a name conflict while reading a network, it's important to try
    // to continue in spite of the conflict and fix things up later.  Reason: older
    // versions of dx allowed the name conflict and we would like to try and fix
    // things and report what happened rather than read the net incorrectly.
    //
    if ((conflict) && (this->getNetwork()->isReadingNetwork() == false)) {
	ErrorMessage("A %s with name \"%s\" already exists.", conflict, label);
	return false;
    }

    bool found = false;
    List *ia = (List*)this->getInputArks(1);
    if ((ia) && (ia->getSize() > 0)) {
	Ark *a = (Ark*)ia->getElement(1);
	int dummy;
	if (EqualString(a->getSourceNode(dummy)->getLabelString(), label))
	    found = true;
	else
	    delete a;
    }
    ia = NUL(List*);


    if (!found) {
	List* l = this->getNetwork()->makeClassifiedNodeList(ClassTransmitterNode, false);
	ListIterator iterator;
	Node *n;

	if ((l) && (this->getNetwork()->isReadingNetwork() == false)) {
	    //
	    // Before creating any Arks, check for cycles.
	    //
	    iterator.setList(*l);
	    while ( (n = (Node*)iterator.getNext()) ) {
		if (EqualString(label, n->getLabelString())) {
		    Network* net = this->getNetwork();
		    if (net->checkForCycle(n, this)) {
			ErrorMessage (
			    "Unable to rename Receiver \"%s\" to \"%s\"\n"
			    "because that would cause a cyclic connection.",
			    this->getLabelString(), label
			);
			delete l;
			return false;
		    }
		}
	    }
	}

	if (l) {
	    iterator.setList(*l);
	    while ( (n = (Node*)iterator.getNext()) ) {
		if (EqualString(label, n->getLabelString()))
		{
		    found = true;
		    // link me to transmitter
		    new Ark(n, 1, this, 1);
		}
	    }
	    delete l;
	}
    }

    //
    // There was a name conflict because earlier versions of dx were less restrictive.
    // Record the transmitter for later fixup.  When the transmitter is fixed up,
    // then we'll automatically get fixed up also.  Caveat:  if there is no transmitter
    // connected, then it's cool to refuse the name because then we're not breaking
    // anything.
    //
    if (conflict) {
	ASSERT (this->getNetwork()->isReadingNetwork());
	if (this->isTransmitterConnected() == false) {
	    ErrorMessage("A %s with name \"%s\" already exists.", conflict, label);
	    return false;
	}
	List *l = (List*)this->getInputArks(1);
	ASSERT (l->getSize() > 0);
	Ark *a = (Ark*)l->getElement(1);
	int dummy;
	TransmitterNode* tn = (TransmitterNode*)a->getSourceNode(dummy);
	this->getNetwork()->fixupTransmitter(tn);
    }

    return this->UniqueNameNode::setLabelString(label);
	
}
//
// Determine if this node is of the given class.
//
bool ReceiverNode::isA(Symbol classname)
{
    Symbol s = theSymbolManager->registerSymbol(ClassReceiverNode);
    if (s == classname)
	return true;
    else
	return this->UniqueNameNode::isA(classname);
}

//
// Get the node that is connected to the Transmitter that this Receiver
// is receiving from.  IF there is no Transmitter for this Receiver, or  
// the Transmitter is not connected, return NULL, otherwise the Node.
//
Node *ReceiverNode::getUltimateSourceNode(int* param_no)
{
    int startPos = 1;

    //
    // Loop over nodes named the same as our getLabelString().  Normally,
    // this wouldn't be necessary, but you can name a ProbeList the same
    // as a transmitter.  Keep a loop counter just as a sanity check, although
    // according to the logic in Network::findNode, it shouldn't be needed.
    //
    Node* tmtr = NUL(Node*);
    int i = 0;
    while (1) {
	tmtr = this->getNetwork()->findNode(this->getLabelString(), &startPos, true);
	if (!tmtr) break;
	if (tmtr->isA(ClassTransmitterNode)) break;
	if (++i > 100) break;
    }

    if (!tmtr)
	return NULL;

    List *arcList = (List*)tmtr->getInputArks(1);
    int narcs = arcList->getSize();
    ASSERT(narcs <= 1);
    if (narcs == 0)
	return NULL;

    Ark *a = (Ark*)arcList->getElement(1);
    ASSERT(a);
    int paramInd;
    Node *n = a->getSourceNode(paramInd);
    if (param_no) *param_no = paramInd;
    if (EqualString(n->getClassName(),ClassReceiverNode)) 
	return ((ReceiverNode*)n)->getUltimateSourceNode();
    else
	return n;
}


//
// Switch the node from one net to another.  Look for a transmitter
// to connect to.
//
void ReceiverNode::switchNetwork(Network *from, Network *to, bool silently)
{
    const char *label = this->getLabelString();

    //
    // Check for a connected input.  If there is an arc, do nothing
    // because any required name change on the part of the transmitter
    // will keep us up-to-date.  If there is no arc, then it's tough to
    // know what name to use.
    //
    List *l = (List*)this->getInputArks(1);
    bool found = false;
    if (l->getSize() > 0) {
	Ark *a = (Ark*)l->getElement(1);
	int dummy;
	if (EqualString(a->getSourceNode(dummy)->getLabelString(), label))   {
	    found = true;
	} else  {
	    delete a;
	}
    }

    bool avoiding_cycle = false;
    if (!found) {
	l = to->makeClassifiedNodeList(ClassTransmitterNode, false);
	if (l) {
	    Node *n;
	    ListIterator iterator(*l);
	    while ( (n = (Node*)iterator.getNext()) ) {
		if (EqualString(label, n->getLabelString())) {
		    if (to->checkForCycle(n, this)) {
			avoiding_cycle = true;
			break;
		    }
		}
	    }

	    if (!avoiding_cycle) {
		iterator.setList(*l);
		while ( (n = (Node*)iterator.getNext()) ) {
		    if (EqualString(label, n->getLabelString())) {
			// link me to transmitter
			new Ark(n, 1, this, 1);
			found = true;
		    }
		}
	    }
	    delete l;
	}
    }

    //
    // If the receiver has no arc, then check for name uniqueness and rename the
    // receiver if necessary.  (If the receiver has an arc, then it's up to the
    // transmitter to handle name uniqueness.)
    //
    if (!found) {
	if (!avoiding_cycle) {
	    const char* conflict = to->nameConflictExists(this, label);
	    if (conflict){
		if (!silently)
		    WarningMessage ("A %s with name \"%s\" already exists.", 
			conflict, label);
		this->setLabelString ("Receiver");
	    }
	} else {
	    if (!silently)
		WarningMessage (
		    "Receiver \"%s\" has been renamed \"%s\"\n"
		    "due to a cyclic connection.",
		    this->getLabelString(), "Receiver"
		);
	    this->setLabelString ("Receiver");
	}
    }

    this->UniqueNameNode::switchNetwork(from, to, silently);
}


bool ReceiverNode::namesConflict (const char* his_label, const char* my_label,
    const char* his_classname)
{

    //
    // You can always match names with other TransmitterNodes or ReceiverNodes.
    //
    if (EqualString (his_classname, this->getClassName())) return false;
    if (EqualString (his_classname, ClassTransmitterNode)) return false;

    //
    // You can always use the name Receiver.
    //
    if (EqualString (my_label, "Reciever")) return false;

    return this->UniqueNameNode::namesConflict (his_label, my_label, his_classname);
}
