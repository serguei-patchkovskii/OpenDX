/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
#ifndef _ToolSelector_h
#define _ToolSelector_h

#include "Base.h"
#include "ActiveItemDictionary.h"
#include "UIComponent.h"
#include "TreeNode.h"
#include "TreeView.h"

#define EXPANDED_CATEGORIES "expandedCategories"

//
// Class name definition:
//
class ToolView;
class CategoryNode;
class ToolNode;

//
// Class name definition:
//
#define ClassToolSelector	"ToolSelector"

//
// XtCallbackProc (*CB), XtEventHandler (*EH) and XtActionProc (*AP)
// DialogCallback (*DCB), XtInputCallbackProc (*ICP), XtWorkProc (*WP)
// functions for this and derived classes
//
//extern "C" void ToolSelector_ToolSelectCB(Widget, XtPointer, XtPointer);
//extern "C" void ToolSelector_CategorySelectCB(Widget, XtPointer, XtPointer);

class NodeDefinition;

//
// ToolSelector class definition:
//				
class ToolSelector : public UIComponent 
{

  private:
    //
    // Private member data:
    //
    ActiveItemDictionary 	categoryDictionary;
    Dictionary			categoryNodeDictionary;

	dxui::TreeNode* treeModel;
    dxui::TreeView* treeView;

    const void			*activeData;
    bool			lockedData;
    bool			toolListDirty;
    int				lastToolIndex;

    static bool ToolSelectorClassInitialized;

    //static String DefaultResources[]; 

    friend class ToolView;

    // List of all tool selectors.
    static List AllToolSelectors;
  
    void buildTreeModel();

  protected:

    //
    // One time initialize for the class. 
    // 
    void initialize();

    //
    // Build the category lists and add the list items to the widgets.
    // from a dictionary of NodeDefinitions.
    //
    //virtual Widget layoutWidgets(Widget parent);

    //
    //  Add tools in the given dictionary to the category/tool lists.
    //
    bool augmentLists(Dictionary *d);

    //
    // Add the Node named 'tool' that is in category 'cat' and defined by 'nd'
    // to the table of category/tool pairings.
    // The widgets are not updated.
    //
    bool addTool(Symbol cat, Symbol tool, void *ptr);
    bool removeTool(Symbol cat, Symbol tool);

    //
    // Build a new Category list and install it in the categoryList.
    //
    bool updateCategoryListWidget();

    virtual void toolSelect(Symbol s);
    virtual void lockSelect(Symbol s);
    virtual void categorySelect(Symbol s);

    CategoryNode* getCategoryNode (dxui::TreeNode* node, Symbol cat);
    dxui::TreeNode* getToolNode (dxui::TreeNode* node, Symbol tool);

    virtual void adjustVisibility(int, int, int, int){}

    virtual void help();

  public:
    //
    // Constructor:
    //
    ToolSelector(const char *name);

    //
    // Destructor:
    //
    ~ToolSelector();

    //
    // Drag-n-Drop support.  Dnd requires some ability to change/access the selected
    // item in the toolList Widget.
    //
    NodeDefinition* definitionOf (const char *category, const char *tool);

    //
    // These perform addTool and removeTool to all tool selectors.
    //
    static bool AddTool(Symbol cat, Symbol tool, void *ptr);
    static bool RemoveTool(Symbol cat, Symbol tool);

    static bool UpdateCategoryListWidget();

    //
    // Merge new tools definitions into all tool selectors from a dictionary 
    // of NodeDefinitions.
    //
    static bool MergeNewTools(Dictionary *d);

    //
    // Get the current Selection. 
    // 
    virtual NodeDefinition *getCurrentSelection() {return (NodeDefinition*)activeData;}

    bool  isSelectionLocked()	{ return this->lockedData; }

    //
    // Build two list widgets and initialize the lists from the items in
    // the dictionary.
    //
    virtual bool initialize(Dictionary *d);

    //
    // Unhighlight any selected tools in the tool list. 
    //
    virtual void deselectAllTools();

    //
    // is the object in the anchor window. At this level we know nothing
    // of windows.  EditorToolSelector has this knowledge.
    //
    virtual bool inAnchor(){ return true; }

    virtual void componentHelp() { this->help(); }

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassToolSelector;
    }
};

//
// I had tried making these class definitions inside the ToolSelector
// protected section.  They shouldn't be usable by classes other than
// ToolSelector and its descendants.  Instead I've put them inside an
// ifdef that only ToolSelector.C picks up.  Reason: it seems that
// some compilers don't work on the definitions I made in the protected
// section.  I don't know what the problem is.  I hope this solves it.
//
#if defined(TOOL_SELECTOR_PRIVATE)
    class ToolCategoryNode : public CategoryNode {
	private:
	    bool sorted;
	protected:
	    ToolSelector* toolSelector;
	    ToolCategoryNode(Symbol s, dxui::TreeNode* parent, ToolSelector* ts); 
	    friend class ToolSelector;
	public:
	    void setExpanded(bool e=true);
	    bool isSorted() {
		if (this->sorted) return true;
		return this->CategoryNode::isSorted();
	    }
    };
    class ToolNode : public LeafNode {
	private:
	protected:
	    ToolSelector* toolSelector;
	    ToolNode(Symbol s, dxui::TreeNode* cat, ToolSelector* ts) : LeafNode(s, cat) { 
		this->toolSelector = ts;
	    }
	    friend class ToolSelector;
	public:
	    CategoryNode* getCategory() { return (CategoryNode*)this->getParent(); }
    };

    class ToolView : public dxui::TreeView {
	private:
	    ToolSelector* toolSelector;
	protected:
	    void select(dxui::TreeNode* node, bool repaint=true);
	    void multiClick(dxui::TreeNode* node);
	    friend class ToolSelector;
	    void adjustVisibility(int, int, int, int);
	    void getSearchableNodes (List& nodes_to_search);
	    ToolView (ToolSelector* t) : dxui::TreeView() {
		this->toolSelector = t;
	    }
	public:
	    void componentHelp() { this->toolSelector->componentHelp(); }
    };
#endif
#endif // _ToolSelector_h
