/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"


#include "NodeList.h"
#include "Node.h"
#include "ListIterator.h"
#include "DictionaryIterator.h"


NodeList::NodeList()
{
}


NodeList::~NodeList()
{	
    DictionaryIterator di(this->nodeDict);
    List* nl;
    while ( (nl = (List*)di.getNextDefinition()) ) 
	delete nl;
    this->nodeDict.clear();
}


void NodeList::clear()
{
    ASSERT(this);
    this->List::clear();
    DictionaryIterator di(this->nodeDict);
    List* nl;
    while ( (nl = (List*)di.getNextDefinition()) ) 
	delete nl;
    this->nodeDict.clear();
}


bool NodeList::insertElement(const void* element, const int position)
{
    bool status = this->List::insertElement(element, position);
    if (status == false) return false;

    //
    // If the Node wants special treatment, then add him
    //
    Node* n = (Node*)element;
    if (n->needsFastSort() == true) {
	List* nl = this->getSubList(n);
	ASSERT (nl->isMember((void*)n) == false);
	nl->appendElement((void*)n);
    }

    return true;
}

List* NodeList::getSubList(Node* n)
{
    const char* node_class = n->getClassName();
    const void* def = this->nodeDict.findDefinition(node_class);
    if (def == NUL(char*)) {
	List* nl = new List;
	this->nodeDict.addDefinition(node_class, nl);
	def = (const void*)nl;
    }
    return (List*)def;
}

bool NodeList::replaceElement(const void* element, const int position)
{
    void* old_element = (void*)this->getElement(position);
    bool status = this->List::replaceElement(element, position);
    if (status == false) return false;

    Node* n = (Node*)old_element;
    if (n->needsFastSort() == true) {
	List* nl = getSubList(n);
	ASSERT (nl->isMember((void*)n) == true);
	nl->removeElement((void*)n);
    }

    n = (Node*)element;
    if (n->needsFastSort() == true) {
	List* nl = getSubList(n);
	ASSERT (nl->isMember((void*)n) == false);
	nl->appendElement((void*)n);
    }

    return status;
}


bool NodeList::deleteElement(const int position)
{
    void* old_element = (void*)this->getElement(position);
    bool status = this->List::deleteElement(position);
    if (status == false) return false;

    Node* n = (Node*)old_element;
    if (n->needsFastSort() == true) {
	List* nl = getSubList(n);
	ASSERT(nl->isMember((void*)n) == true);
	nl->removeElement((void*)n);
    }

    return status;
}

//
// Create a duplicate list with the same list items.
//
List* NodeList::dup()
{
    NodeList *nl = new NodeList;
    ListIterator iter(*this);
    const void *v;

    while ( (v = (const void*)iter.getNext()) )
        nl->appendElement(v);

    return nl;
}

List* NodeList::makeClassifiedNodeList(const char* classname)
{
    ASSERT(classname);
    int size = this->nodeDict.getSize();
    int i;
    for (i=1; i<=size; i++) {
	const char* cn = this->nodeDict.getStringKey(i);
	if (EqualString(cn, classname) == false) continue;

	List* nl = (List*)this->nodeDict.getDefinition(i);
	return nl->dup();
    }
    ListIterator it(*this);
    Node* n;
    List* l = NUL(List*);
    while ( (n = (Node*)it.getNext()) ) {
	if (EqualString(classname, n->getClassName()) == true) {
	    if (!l) l = new List;
	    l->appendElement((void*)n);
	}
    }
    return l;
}
