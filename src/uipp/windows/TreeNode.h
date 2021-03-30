/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
#ifndef _TreeNode_h
#define _TreeNode_h

#include "Base.h"
#include "SymbolManager.h"
#include "List.h"
#include "ListIterator.h"

#define ClassTreeNode "TreeNode"

class List;

namespace dxui {
	class TreeNode : public Base {

	private:

	protected:
		Symbol definition;
		TreeNode* parent;
		TreeNode(Symbol s, TreeNode* parent) {
			this->definition = s;
			this->expanded = false;
			this->parent = parent;
		}

		bool expanded;

	public:
		virtual ~TreeNode() { }

		virtual bool hasChildren()=0;
		virtual List* getChildren()=0;
		virtual bool isExpanded() { return this->expanded; }
		virtual const char* getString() {
			return theSymbolManager->getSymbolString(this->definition);
		}
		virtual bool isRoot()=0;
		virtual bool isLeaf()=0;
		virtual Symbol getDefinition() { return this->definition; }
		virtual void setExpanded(bool e=true) {
			this->expanded = e;
		}
		virtual bool isSorted() { return false; }

		TreeNode* getParent() { return this->parent; }

		//
		// Returns a pointer to the class name.
		//
		const char* getClassName()
		{
			return ClassTreeNode;
		}
	};
}

class LeafNode : public dxui::TreeNode {
    private:
    protected:
    public:
	LeafNode(Symbol s, TreeNode* parent) : TreeNode(s, parent) {
	}
	bool isRoot() { return false; }
	bool isLeaf() { return true; }
	List* getChildren() { return NUL(List*); }
	bool hasChildren() { return false ; }
};

class CategoryNode: public dxui::TreeNode {
    private:
    protected:
	List kids;
    public:
	CategoryNode(Symbol s, TreeNode* parent) : TreeNode(s, parent) { }
	virtual ~CategoryNode() {
	    ListIterator iter(this->kids);
	    TreeNode* node;
	    while (node=(TreeNode*)iter.getNext()) {
		delete node;
	    }
	}
	bool isRoot() { return false; }
	bool isLeaf() { return false; }
	bool hasChildren() { return true; }
	void addChild(TreeNode* t) { this->kids.appendElement(t); }
	List* getChildren() { return &this->kids; }
};

class RootNode: public CategoryNode {
    private:
    protected:
    public:
	RootNode() : CategoryNode((Symbol)0, (TreeNode*)0) { }
	bool isRoot() { return true; }
	const char* getString() { return ""; }
	bool isExpanded() { return true; }
};

#endif // _TreeNode_h


