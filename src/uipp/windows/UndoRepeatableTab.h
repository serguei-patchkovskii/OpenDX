/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
#ifndef _UndoRepeatableTab_h
#define _UndoRepeatableTab_h
#include "UndoNode.h"

class Node;

//
//
#define UndoRepeatableTabClassName "UndoRepeatableTab"
class UndoRepeatableTab : public UndoNode
{
    private:
    protected:
	static char OperationName[];
	bool adding;
	bool input;
    public:
	virtual const char* getLabel() { return UndoRepeatableTab::OperationName; }
	virtual ~UndoRepeatableTab(){}
	virtual bool canUndo();
	UndoRepeatableTab (EditorWindow* editor, Node* n, bool adding, bool input);
	virtual void undo(bool first_in_list=true);
	virtual const char* getClassName() { return UndoRepeatableTabClassName; }
};

#endif // _UndoRepeatableTab_h
