/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
#include "UndoAddArk.h"
#include "EditorWindow.h"
#include "Node.h"
#include "StandIn.h"
#include "Ark.h"
#include "UndoNode.h"
#include "List.h"
#include "ListIterator.h"

char UndoAddArk::OperationName[] = "connection";

UndoAddArk::UndoAddArk (EditorWindow* editor, Ark* arc, bool adding) : 
    UndoableAction(editor)
{
    this->adding = !adding;

    Node* source = arc->getSourceNode (this->output);
    Node* dest = arc->getDestinationNode(this->input);
    this->source_name = source->getNameString();
    this->destination_name = dest->getNameString();
    this->source_instance = source->getInstanceNumber();
    this->destination_instance = dest->getInstanceNumber();
}

//
// Write out the contents in the buffer and let a new network read
// it back in.
//
void UndoAddArk::undo(bool first_in_list) 
{
    Node* src = UndoNode::LookupNode 
	(this->editor, this->source_name, this->source_instance);
    Node* dst = UndoNode::LookupNode 
	(this->editor, this->destination_name, this->destination_instance);
    StandIn* si = src->getStandIn();
    ASSERT(si);
    if (adding) {
	si->addArk(this->editor, new Ark (src, this->output, dst, this->input));
    } else {
	Ark* a = this->lookupArk(src, dst);
	si->deleteArk(a);
    }
}

//
// How can I tell if the contents of the buffer are usable?
//
bool UndoAddArk::canUndo()
{
    Node* src = UndoNode::LookupNode 
	(this->editor, this->source_name, this->source_instance);
    if (!src) return false;
    Node* dst = UndoNode::LookupNode 
	(this->editor, this->destination_name, this->destination_instance);
    if (!dst) return false;


    if (adding) {
	if (src->getOutputCount() < this->output) return false;
	if (dst->getInputCount() < this->input) return false;
	if (!src->isOutputVisible(this->output)) return false;
	if (!dst->isInputVisible(this->input)) return false;
	if (dst->isInputConnected(this->input)) return false;
    } else {
	if (!dst->isInputConnected(this->input)) return false;
	if (!this->lookupArk(src,dst)) return false;
    }

    return true;
}

Ark* UndoAddArk::lookupArk(Node* src, Node* dst)
{
    if (src->getOutputCount() < this->output) return NUL(Ark*);
    if (dst->getInputCount() < this->input) return NUL(Ark*);
    if (!src->isOutputVisible(this->output)) return NUL(Ark*);
    if (!dst->isInputVisible(this->input)) return NUL(Ark*);

    List* arcs = (List*)dst->getInputArks(this->input);
    ListIterator iter(*arcs);
    Ark* arc;
    int output;
    while (arc=(Ark*)iter.getNext()) {
	Node* source = arc->getSourceNode(output);
	if ((source == src) && (output == this->output))
	    return arc;
    }
    return NUL(Ark*);
}
