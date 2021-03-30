/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"




#include <stdlib.h>

#include "DXStrings.h"
#include "lex.h"
#include "GroupManager.h"
#include "Dictionary.h"
#include "ListIterator.h"
#include "List.h"
#include "Network.h"
#include "ErrorDialogManager.h"
#include "EditorWindow.h"
#include "DXApplication.h"
#include "SymbolManager.h"

GroupManager::GroupManager(Network *net, Symbol groupID)
{
    this->app = theDXApplication;
    this->network = net;
    this->setDirty();
    this->groupID = groupID;
}
GroupManager::~GroupManager()
{
     this->clear(); 
}

void GroupManager::clear()
{
    GroupRecord *record;

    while ( (record = (GroupRecord*) this->groups.getDefinition(1)) ) 
    {
	this->groups.removeDefinition((const void*)record);
	delete record;
    }
}

Network* GroupManager::getGroupNetwork(const char *name)
{
    GroupRecord *record
    	= (GroupRecord*)this->groups.findDefinition(name);

    if(NOT record)
	return NULL;
    else
	return record->network;
}


bool GroupManager::registerGroup(const char *name, Network *net)
{
    GroupRecord *record;
    ASSERT (net == this->network);

    if (NOT this->groups.findDefinition(name))
    {
	record = this->recordAllocator(net, name);
    	this->groups.addDefinition(name,(const void*)record); 
    }

    return true;
}

bool GroupManager::addGroupMember(const char *name, Network *net)
{
    ASSERT (net == this->network);

    if (IsBlankString(name))
	return false;

    if (NOT this->hasGroup(name))
	return false;	

    GroupRecord *grec = this->getGroup(name);

    EditorWindow* editor = net->getEditor();
    if (editor) {
	editor->setGroup(grec, this->groupID);
	net->setFileDirty();
    }

    return true;
}

bool  GroupManager::removeGroupMember(const char *name, Network *net)
{
    ASSERT (net == this->network);

    if (NOT this->hasGroup(name))
	return false;	

    EditorWindow* editor = net->getEditor();
    if (editor) {
	editor->setGroup(NULL, this->groupID);
	net->setFileDirty();
    }

    return true;
}

bool     GroupManager::createGroup(const char *name, Network *net)
{
    ASSERT (net == this->network);

    bool result;

    if (IsBlankString(name))
	return false;

    if (this->groups.findDefinition(name))
	return false;	// Named group already exists.

    GroupRecord *record = this->recordAllocator(net, name);

    result = this->groups.addDefinition(name,(const void*)record); 

    if(result)
    {
	EditorWindow* editor = net->getEditor();
	if (editor) {
	    editor->setGroup(record, this->groupID);
	    net->setFileDirty();
	    net->changeExistanceWork(NUL(Node*), true);
	}
    }

    return result;
}

bool     GroupManager::removeGroup(const char *name, Network *net) 
{
    ASSERT (net == this->network);

    GroupRecord *record;

    record = (GroupRecord*)this->groups.removeDefinition(name);

    if (NOT record) 
	return false;

    EditorWindow* editor = net->getEditor();
    if (editor) {
	editor->resetGroup(name, this->groupID);
	net->setFileDirty();
	net->changeExistanceWork(NUL(Node*), false);
    }

    delete record;

    return true;
}


bool     GroupManager::selectGroupNodes(const char *name) 
{
    GroupRecord *record;

    record = (GroupRecord*) this->groups.findDefinition(name);

    if(NOT record)
	return false;	
    
    EditorWindow* editor = record->network->getEditor();
    if (editor)
	editor->selectGroup(name, this->groupID);

    return true;
}


const char *GroupManager::getManagerName() 
    { return theSymbolManager->getSymbolString(this->groupID); }


