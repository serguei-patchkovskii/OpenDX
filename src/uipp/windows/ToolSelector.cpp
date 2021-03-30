/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

#include <ctype.h>
#include <time.h>

#include "Application.h"
#include "NodeDefinition.h"
#include "Dictionary.h"
#include "DictionaryIterator.h"
#include "ResourceManager.h"

#include "TreeNode.h"
#include "TreeView.h"
#define TOOL_SELECTOR_PRIVATE
#include "ToolSelector.h" 
#define ALPHABETIZED "( ALL )"
//#define DONT_USE_ALL_IN_THE_LIST 1

bool ToolSelector::ToolSelectorClassInitialized = false;
List ToolSelector::AllToolSelectors;

//String ToolSelector::DefaultResources[] =
//{
//    ".width:    180",
//    "*traversalOn: False",
//     NUL(char*)
//};    


//
// Constructor:
//
ToolSelector::ToolSelector(const char *name) : UIComponent(name) 
{
    this->activeData = NUL(void*); 
    this->lockedData = false;
    this->initialize();

    AllToolSelectors.appendElement((void*)this);
}


//
// Destructor:
//
ToolSelector::~ToolSelector()
{
    ActiveItemDictionary *d;
    DictionaryIterator iterator(this->categoryDictionary);
    while ( (d = (ActiveItemDictionary*)iterator.getNextDefinition()) )
        delete d;

    AllToolSelectors.removeElement((void*)this);
}

//
// Unhighlight any selected tools in the tool list.
// We only allow one selection at a time so this is just deselecting THE 
// selected item (if there is one).
//
void ToolSelector::deselectAllTools()
{
    this->activeData = NULL;
    this->lockedData = false;
    this->treeView->clear();
}

void ToolSelector::initialize()
{
    //
    // Initialize default resources (once only).
    //
    if (NOT ToolSelector::ToolSelectorClassInitialized)
    {
        //ASSERT(theApplication);

        //this->setDefaultResources(theApplication->getRootWidget(),
        //                          ToolSelector::DefaultResources);
        ToolSelector::ToolSelectorClassInitialized = true;

    }
}
//
//
bool ToolSelector::initialize(Dictionary *d)
{
    //
    // Create the widgets before do 'addTool'.
    //
    //this->setRootWidget(this->layoutWidgets(parent));

    theSymbolManager->registerSymbol(ALPHABETIZED);

    if (d->getSize() == 0)
	return true;
    //
    // Build the category lists. 
    //
    if (!this->augmentLists(d))
	return false;

    this->buildTreeModel();

    return true;
}

//
// Build the category lists and add the list items to the widgets. 
// from a dictionary of NodeDefinitions.
//
bool ToolSelector::augmentLists(Dictionary *d)
{
    Symbol c, t;
    DictionaryIterator iterator(*d);
    NodeDefinition *nd;

    Symbol alpha = theSymbolManager->getSymbol(ALPHABETIZED);
 
    //
    // Look at all the node definitions and insert their category:name
    // pairs in the categories member.
    //
    while ( (nd = (NodeDefinition*)iterator.getNextDefinition()) ) {
        c = nd->getCategorySymbol();
        t = nd->getNameSymbol();
        if (!this->addTool(c, t, (void*)nd))
		return false;
    }

    return true;
}

//
//  Build the widget tree. 
//
//Widget ToolSelector::layoutWidgets(Widget parent)
//{
//
//    this->treeView = new ToolView(parent, this);
//    return this->treeView->getRootWidget();
//}

//
// Add the Node named 'tool' that is in category 'cat' and defined by 'nd'
// to the table of category/tool pairings.
// We keep an ActiveItemDictionary of ActiveItemDictoinaries.  The
// first level of dictionary is the categories, the second is the tools
// under the given category.
//
bool ToolSelector::addTool(Symbol cat, Symbol tool, void *ptr)
{
    ActiveItemDictionary *toollist;

    //
    // Tools without categories are ignored.
    //
    if (!cat) return true;

    toollist = (ActiveItemDictionary*) this->categoryDictionary.findDefinition(cat);

    //
    // If adding new category create a new toollist data structure
    //
    if (!toollist) {
        toollist = new ActiveItemDictionary;
        this->categoryDictionary.addDefinition(cat, toollist);
    }

    if (!toollist->addDefinition(tool,ptr)) {
        if (!toollist->replaceDefinition(tool,ptr)) {
	    return false;
	}
    }

    Symbol alpha = theSymbolManager->getSymbol(ALPHABETIZED);
    if (cat != alpha)
	return this->addTool(alpha,tool,ptr);
    else
	return true;
}

void ToolSelector::buildTreeModel()
{
    bool repaint = (this->treeView->getDataModel()!=NUL(dxui::TreeNode*));
    RootNode* root = new RootNode();
    DictionaryIterator citer(this->categoryDictionary);
    Symbol cat;
    List expanded_categories;
    theResourceManager->getValue(EXPANDED_CATEGORIES, expanded_categories);
#if defined(DONT_USE_ALL_IN_THE_LIST)
    Symbol alpha = theSymbolManager->getSymbol(ALPHABETIZED);
#endif
    while (cat = citer.getNextSymbol()) {
#if defined(DONT_USE_ALL_IN_THE_LIST)
	if (cat == alpha) continue;
#endif
	CategoryNode* cnode = new ToolCategoryNode(cat, root, this);
	root->addChild(cnode);

	ActiveItemDictionary* tools = (ActiveItemDictionary*)
	    this->categoryDictionary.findDefinition(cat);
	DictionaryIterator titer(*tools);
	Symbol tool;
	while (tool = titer.getNextSymbol()) {
	    cnode->addChild(new ToolNode(tool, cnode, this));
	}

	//
	// did the user leave the category open?
	//
	if (expanded_categories.isMember((void*)cat))
	    cnode->setExpanded(true);
    }

    //
    // check for unusable categories in the resource setting and remove them.
    // This happens if a tool was loaded into a category but during a later
    // use of dxui, that tool isn't loaded and its category doesn't exist.
    //
    ListIterator iter(expanded_categories);
    while (cat=(Symbol)(long)iter.getNext()) {
	if (this->categoryDictionary.findDefinition(cat)) continue;
	const char* cp = theSymbolManager->getSymbolString(cat);
	//printf ("%s[%d] Warning: bad value(%s) in resource %s\n",
	//    __FILE__,__LINE__,cp,EXPANDED_CATEGORIES);
	theResourceManager->removeValue(EXPANDED_CATEGORIES, cp);
    }

    this->treeView->initialize(root, repaint);
}

//
// Remove the Node named 'tool' that is in category 'cat'
// from the table of category/tool pairings.
// We keep a of ActiveItemDictionary of ActiveItemDictoinaries.  The
// first level of dictionary is the categories, the second is the tools
// under the given category.
//
bool ToolSelector::removeTool(Symbol cat, Symbol tool)
{
    ActiveItemDictionary *toollist;


    toollist = (ActiveItemDictionary*)this->categoryDictionary.findDefinition(cat);
    //
    // If adding new category create a new toollist data structure
    //
    if (!toollist || toollist->removeDefinition(tool) == NULL)
	return false;

    Symbol alpha = theSymbolManager->getSymbol(ALPHABETIZED);
    if (cat != alpha)
	return this->removeTool(alpha,tool);
    else
	return true;
}


/////////////////////////////////////////////////////////////////////////////


//
// Member function callback called through 
// (XtCallbackProc)ToolSelector_CategorySelectCB() to handle tool list selection 
// callbacks.
//
void ToolSelector::categorySelect(Symbol cs)
{
    this->categoryDictionary.setActiveItem(cs);
}


//
// Member function callback called through (XtCallbackProc)ToolSelector_ToolSelectCB().
// to handle tool list selection call backs.
//
void ToolSelector::toolSelect(Symbol ts)
{
    if (ts) {
	ActiveItemDictionary *toollist;
	ToolView* tv = (ToolView*)this->treeView;

	/*
	 * Search for the selected module.
	 */
	toollist = (ActiveItemDictionary*) this->categoryDictionary.getActiveDefinition();
	this->activeData = toollist->findDefinition(ts); 

	//
	// When we include ALPHABETIZED in the list, we always have a problem
	// figuring out exactly which node to select because there are 2 copies
	// of each node, 1 in the normal category and 1 in ( All ).
	//
	dxui::TreeNode* tn = this->getToolNode(this->treeView->getDataModel(), ts);
	dxui::TreeNode* seln = tv->getSelection();
	if ((seln) && (tn->getDefinition() != seln->getDefinition()))
	    tv->select (tn, true);
    } else {
	this->activeData = NULL;
    }
    this->lockedData = false;
}

void ToolSelector::lockSelect(Symbol ts)
{
    if (this->activeData != NULL) this->lockedData = true;
}

ToolCategoryNode::ToolCategoryNode(Symbol s, dxui::TreeNode* parent, ToolSelector* ts) :
    CategoryNode(s,parent)
{
    this->toolSelector = ts;
    this->sorted = (s == theSymbolManager->getSymbol(ALPHABETIZED));
}

//
// return the NodeDefinition of char strings or 0 if the item is not
// in the list.  Added 5/15/95 for dnd support.  The vpe needs this in
// order to know if the DXTOOLNAME dropped on him is a legal tool for
// the current copy of dx.  Just because something was dragged froma ToolSelector
// doesn't mean it will be dropped on the same dx. 
//
NodeDefinition *
ToolSelector::definitionOf (const char *category, const char *item)
{
ActiveItemDictionary *toolList;
NodeDefinition* activeData;

    toolList = (ActiveItemDictionary*)this->categoryDictionary.findDefinition(category);
    if (!toolList) return 0;

    activeData = (NodeDefinition*)toolList->findDefinition (item);
    if (!activeData) return 0;

    return activeData;
    
}


// These perform addTool and removeTool to all tool selectors.
bool ToolSelector::AddTool(Symbol cat, Symbol tool, void *ptr)
{
    ListIterator li(ToolSelector::AllToolSelectors);
    ToolSelector *ts;

    //
    // If there is no category, don't put it in the list.
    //
    if (!cat)
	return true;

    while( (ts = (ToolSelector*)li.getNext()) ) {
	ts->addTool(cat, tool, ptr);
    }
    return true;
}

bool ToolSelector::RemoveTool(Symbol cat, Symbol tool)
{
    ListIterator li(ToolSelector::AllToolSelectors);
    ToolSelector *ts;
    bool result = true;
    while( (ts = (ToolSelector*)li.getNext()) )
    {
	if (!ts->removeTool(cat, tool))
	    result = false;
    }
    return result;
}

//
// Caution:  This API isn't very good IMO.  Problem is you can't really
// call UpdateCategoryListWidget or UpdateToolListWidget idependently.
// They really operate as a pair.  They're called from MacroDefinition
// when creating/modifying a macro.  When updating either, you must
// update both and you have to update the data model.
//
bool ToolSelector::UpdateCategoryListWidget()
{
    ListIterator li(ToolSelector::AllToolSelectors);
    ToolSelector *ts;
    bool result = true;
    while( (ts = (ToolSelector*)li.getNext()) )
    {
	if (!ts->updateCategoryListWidget())
	    result = false;
	else
	    ts->buildTreeModel();
    }
    return result;
}

//
// Merge new tools definitions into all tool selectors from a dictionary 
// of NodeDefinitions.
//
bool ToolSelector::MergeNewTools(Dictionary *d)
{
    ListIterator li(ToolSelector::AllToolSelectors);
    ToolSelector *ts;

    while( (ts = (ToolSelector*)li.getNext()) )
    {
	if (!ts->augmentLists(d) ||
	    !ts->updateCategoryListWidget())
	    return false;
	ts->buildTreeModel();
    }
    return true;
}


//
// Build a new Category list and install it in the categoryList. 
// This assumes that there is at least ONE categorie.
//
bool ToolSelector::updateCategoryListWidget()
{
    DictionaryIterator iterator(this->categoryDictionary);
    Symbol first_cat = iterator.getNextSymbol();
    if (!this->categoryDictionary.isActive())
        this->categoryDictionary.setActiveItem(first_cat);

    return true;
}

void ToolView::select(dxui::TreeNode* node, bool repaint) 
{
 //   if (this->getSelection() == node) return ;
 //   this->TreeView::select(node, repaint);
 //   if (node) {
	//if (node->isLeaf()) {
	//    CategoryNode* cn = (CategoryNode*)node->getParent();
	//    this->toolSelector->categorySelect(cn->getDefinition());
	//    toolSelector->toolSelect(node->getDefinition());
	//} else {
	//    CategoryNode* cn = (CategoryNode*)node;
	//    this->toolSelector->categorySelect(cn->getDefinition());
	//    toolSelector->toolSelect(0);
	//}
 //   } else {
	//toolSelector->toolSelect(0);
 //   }
}
void ToolView::adjustVisibility(int x1, int y1, int x2, int y2)
{
    this->TreeView::adjustVisibility(x1,y1,x2,y2);
    this->toolSelector->adjustVisibility(x1,y1,x2,y2);
}

//
// append the tools in ( ALL ) so that type-ahead will always give
// precedence to the exposed tools and then allow matching on all others.
//
void ToolView::getSearchableNodes(List& nodes_to_search)
{
    this->TreeView::getSearchableNodes(nodes_to_search);
#if defined(ALPHABETIZED)
    Symbol alpha = theSymbolManager->getSymbol(ALPHABETIZED);
    if (!alpha) return ;
	dxui::TreeNode* root = this->getDataModel();
    List* kids = root->getChildren();
    ListIterator iter(*kids);;
	dxui::TreeNode* kid;
    bool found = false;
	while (kid = (dxui::TreeNode*)iter.getNext()) {
	if (kid->getDefinition() == alpha) {
	    if (kid->isExpanded() == false) {
		List* nodes = kid->getChildren();
		ListIterator liter(*nodes);
		bool in_expanded_category;
		while (kid=(dxui::TreeNode*)liter.getNext()) {
		    Symbol ns = kid->getDefinition();
		    NodeDefinition* nd = (NodeDefinition*)
			theNodeDefinitionDictionary->findDefinition(ns);
		    Symbol cs = nd->getCategorySymbol();
		    CategoryNode* cat = this->toolSelector->getCategoryNode (root, cs);
		    in_expanded_category = cat->isExpanded();
		    if (!in_expanded_category)
			nodes_to_search.appendElement(kid);
		}
	    }
	    found = true;
	    break;
	}
    }
    ASSERT(found);
#endif
}

void ToolView::multiClick(dxui::TreeNode* node) 
{
 //   this->TreeView::multiClick(node);
 //   if (node->isLeaf()) {
	//ToolNode* tn = (ToolNode*)node;
	//toolSelector->lockSelect(tn->getDefinition());
 //   }
}

//
// If ALPHABETIZED is in use, then there are always 2 definitions
// in the tree model for every node.  Don't return the definition
// that's inside the collapsed ALPHABETIZED category. If 
// ALPHABETIZED is expanded then we'll allow its use.
//
dxui::TreeNode* ToolSelector::getToolNode (dxui::TreeNode* node, Symbol tool)
{
    // this test does nothing if ALPHABETIZED isn't in use.
    Symbol alpha = theSymbolManager->getSymbol(ALPHABETIZED);
    if (alpha) {
	if (node->getDefinition() == alpha) {
	    if (node->isExpanded()==false) {
		return 0;
	    }
	}
    }

    if (node->getDefinition() == tool) return node;
    if (node->hasChildren()) {
	List* kids = node->getChildren();
	if (kids) {
	    ListIterator iter(*kids);
	    dxui::TreeNode* tn;
		while (tn=(dxui::TreeNode*)iter.getNext()) {
			dxui::TreeNode* n = this->getToolNode(tn, tool);
		if (n) return n;
	    }
	}
    }
    return 0;
}

CategoryNode* ToolSelector::getCategoryNode (dxui::TreeNode* node, Symbol cat)
{
    if (node->getDefinition() == cat) return (CategoryNode*)node;
    if (node->hasChildren()) {
	List* kids = node->getChildren();
	if (kids) {
	    ListIterator iter(*kids);
	    dxui::TreeNode* tn;
	    while (tn=(dxui::TreeNode*)iter.getNext()) {
		CategoryNode* catNode = this->getCategoryNode(tn, cat);
		if (catNode) return catNode;
	    }
	}
    }
    return NUL(CategoryNode*);
}

void ToolCategoryNode::setExpanded(bool e) 
{
    this->CategoryNode::setExpanded(e);
    if (this->toolSelector->inAnchor()) {
	if (e)
	    theResourceManager->addValue (EXPANDED_CATEGORIES,
		theSymbolManager->getSymbolString(this->getDefinition()));
	else
	    theResourceManager->removeValue (EXPANDED_CATEGORIES,
		theSymbolManager->getSymbolString(this->getDefinition()));
    }
}

void ToolSelector::help()
{
    const char* tools = 0;
    Symbol s = this->categoryDictionary.getActiveItem();

    // There is no help on ( ALL )
    if (s == theSymbolManager->getSymbol(ALPHABETIZED)) s = 0;
    if (s) {
	tools = theSymbolManager->getSymbolString(s);
    } else {
	//
	// If there is no active item in the category dictionary
	// then check for the first expanded category and use
	// that.  The ALPHABETIZED category doesn't have help.
	//
	dxui::TreeNode* root = this->treeView->getDataModel();
	List* categories = root->getChildren();
	ListIterator iter(*categories);
	iter.getNext();
	dxui::TreeNode* cat;
	while (cat=(dxui::TreeNode*)iter.getNext()) {
	    if (cat->isExpanded()) {
		tools = cat->getString();
		break;
	    }
	}
    }
    if (!tools)
	tools = this->name;//ALPHABETIZED;
    char* cp = DuplicateString(tools);
    char *p;
    for (p = cp; *p; ++p)
	if (*p == ' ' || *p == '\t')
	    *p = '-';
    theApplication->helpOn(cp);
    delete cp;
}

