/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"




#include "DisplayNode.h"
#include "Parameter.h"
#include "ImageWindow.h"
#include "Network.h"
#include "DXApplication.h"
#include "PanelAccessManager.h"
#include "List.h"
#include "ListIterator.h"
#include "ErrorDialogManager.h"
#if WORKSPACE_PAGES
#include "GroupManager.h"
#endif

DisplayNode::DisplayNode(NodeDefinition *nd, 
				     Network *net, int instnc) :
    DrivenNode(nd, net, instnc)
{
    this->xpos = this->ypos = UIComponent::UnspecifiedPosition;
    this->width = this->height = UIComponent::UnspecifiedDimension;
    this->image = NULL;
    //
    // It's makes no sense to even think about creating an image window
    // for a Display node in a macro.
    //
    this->userSpecifiedWhere = net->isMacro();
    this->title = NULL;
    this->panelAccessManager = NULL;
}

DisplayNode::~DisplayNode()
{
    if (this->windowId != 0)
    {
	char message[1000];
	sprintf(message, "IMAGE:  ##%d", this->windowId);
	DXPacketIF *pif = theDXApplication->getPacketIF();
	pif->setHandler(DXPacketIF::INFORMATION,
			NULL,
			(void*)this,
			message);
    }
    if (this->image != NULL)
    {
	if (this->image != theDXApplication->getAnchor())
	{
	    delete this->image;
	}
	else
	{
	    this->setTitle("Image");
	    this->image->associateNode(NULL);
	}
    }
    if (this->title != NULL)
	delete title;
    if (this->panelAccessManager) 
        delete this->panelAccessManager;
}

bool DisplayNode::initialize()
{
    this->Node::initialize();

    this->depth = 24;

    this->windowId = 0;
    this->lastImage = true;

    this->panelAccessManager = new PanelAccessManager(this->getNetwork());

    // Try to find an extant image window that isn't being used.
    ImageWindow *w = this->getUnassociatedImageWindow(false);
    if (w) 
	this->associateImage(w);

    Parameter *p = this->getInputParameter(3);
    p->setDirty();
    return true;
}

void
DisplayNode::setDepth(int depth)
{
    if(depth != this->depth)
    {
	this->depth = depth;
	if(this->image)
	    this->setInputValue(WHERE, this->image->getDisplayString(), 
		DXType::WhereType, true);
    }
}

//
// FIXME:  Why is there an extra unused bool here?  I added it when I made
// this virtual because ImageNode::setTitle needs the bool (I think).
// Please look there and fix that piece of code.  
//
void
DisplayNode::setTitle(const char *title, bool)
{
    if (this->title)
	delete this->title;
    if ((title) && (title[0]))
	this->title = DuplicateString(title);
    else
	this->title = NUL(char*);

    if (this->image != NULL)
	if (this->title) this->image->setWindowTitle(title, true);
	else this->image->resetWindowTitle();
}

bool DisplayNode::netPrintAuxComment(FILE *f)
{
    return this->Node::netPrintAuxComment(f) &&
    	   this->printCommonComments(f,"    ");
}
bool DisplayNode::netParseAuxComment(const char *comment,
				const char *file,
				int lineno)
{
    return this->Node::netParseAuxComment(comment, file, lineno)  ||
	   this->parseCommonComments(comment,file,lineno); 
}


bool DisplayNode::cfgPrintNode(FILE *f, PrintType dest)
{
    long fpos1, fpos2; 

    fpos1 = ftell(f);
    if (!this->cfgPrintNodeLeader(f))
	return false;

    fpos2 = ftell(f);

    if (!this->panelAccessManager->cfgPrintInaccessibleComment(f))
	return false;

    if (!this->printCommonComments(f))
	return false;

    //
    // If there were no other comments for this node, then back out the 'node'
    // comment that we wrote above.
    //
    if (fpos2 == ftell(f))
	fseek(f,fpos1,0);	// 0 == absolute seek

    return true;
}

bool DisplayNode::cfgParseComment(const char *comment,
				const char *file,
				int lineno)
{
    if (this->Node::cfgParseNodeLeader(comment, file, lineno)) 
	return true;

    if (this->panelAccessManager->cfgParseInaccessibleComment(comment, 
				file,lineno))
	return true;

    if (this->parseCommonComments(comment,file,lineno))
	return true;

    return false;
}



dx_Type
DisplayNode::setInputValue(int index,
				 const char *value,
				 dx_Type t,
				 bool send)
{
    if (index == 3)
    {
	if (this->image == NULL) {
	    this->userSpecifiedWhere = true;
	    dx_Type tmp = this->Node::setInputValue(index, value, t, send);
	    this->userSpecifiedWhere = (bool)tmp;
	    return tmp;
	} else {
	    const char* cp = this->getInputValueString(index);
	    bool retVal = this->Node::setInputValue (index, cp, t, send);
	    return retVal;
	}
    }
    else
	return this->Node::setInputValue(index, value, t, send);
}

bool
DisplayNode::associateImage(ImageWindow *w)
{
    if (w == NULL) { 
	if (this->image == NULL)
	    return true; // Stop recursion with ImageWindow::associateNode()
	w = this->image;
	if (!w->associateNode(NULL))
            return false;
	this->image = NULL;
    } else {
	if (this->image != NULL)
	    return false;
    
	if (!w->associateNode(this))
	    return false;

	this->image = w;
    }

	if (this->title != NULL && this->image != NULL)
		this->image->setWindowTitle(this->title);

	if (this->image != NULL)
		this->image->changeDepth(this->depth);

    return true;
}

void DisplayNode::prepareToSendValue(int index, Parameter *p)
{
    if (!this->userSpecifiedWhere)
    {
	// Create a new Image Window if necessary.
	if (this->image == NULL)
	{
	    this->openImageWindow(false);
	}
	if (p->isInput() && index == 3)
	{
	    char *s = this->image->getDisplayString();
	    this->Node::setInputValue(index,
					    s,
					    DXType::WhereType,
					    false);
	    int newWindowId;
	    sscanf(s, "%*[^#]##%d", &newWindowId);
	    if (this->windowId != newWindowId)
	    {
		char message[1000];
		sprintf(message, "IMAGE:  ##%d", this->windowId);
		DXPacketIF *pif = theDXApplication->getPacketIF();
		pif->setHandler(DXPacketIF::INFORMATION,
				NULL,
				(void*)this,
				message);
		this->windowId = newWindowId;
		sprintf(message, "IMAGE:  ##%d", this->windowId);
		pif->setHandler(DXPacketIF::INFORMATION,
				DisplayNode::HandleImageMessage,
				(void*)this,
				message);
	    }
	}
    }
}

void DisplayNode::prepareToSendNode()
{
    if (!this->userSpecifiedWhere)
    {
	// Create a new Image Window if necessary.
	if (this->image == NULL)
	    this->openImageWindow(false);

 	if (!this->isInputSet(3))
	    this->notifyWhereChange(false);
    }
}

void DisplayNode::HandleImageMessage(void *clientData, int id, void *line)
{
    DisplayNode *n = (DisplayNode *)clientData;
    n->handleImageMessage(id, (const char *)line);
}

void DisplayNode::handleImageMessage(int id, const char *line)
{
    int x, y;
    if (sscanf(line, "%*d:  IMAGE:  ##%*d %dx%d", &x, &y) == 2)
	this->image->newCamera(x, y);

    if (!this->image->isManaged())
    {
	this->image->sensitizeChangeImageName(true);
	this->image->manage();
    }
}

void    DisplayNode::notifyWhereChange(bool send)
{
    this->setInputValue(3, "", DXType::WhereType, send);
    this->windowId = 0;
}


bool DisplayNode::printCommonComments(FILE *f, const char *indent)
{
    if (!indent)
	indent = "";

    if (this->title &&
	(fprintf(f, "%s// title: value = %s\n", indent, this->title) <= 0))
	return false;
    if (fprintf(f, "%s// depth: value = %d\n", indent, this->depth) <= 0)
	return false;

    int x,y,w,h;
    if (this->image) {
        this->image->getGeometry(&x,&y,&w,&h);
    } else {
        x = this->xpos;
        y = this->ypos;
        w = this->width;
        h = this->height;
    }

    if (x != UIComponent::UnspecifiedPosition) {
        if (!UIComponent::PrintGeometryComment(f, x,y,w,h,NULL,indent))
            return false;
    }
    return true;
}

bool DisplayNode::parseCommonComments(const char *comment,
				const char *file,
				int lineno)
{
    // Display title comment is of the form
    // title: value = somestring
    if (strncmp(" title:", comment, 7) == 0)
    {
	this->setTitle(comment + STRLEN(" title: value = "));
	return true;
    }
    else if (strncmp(" depth:", comment, 7) == 0)
    {
	//
	// If we have an image window, then changing its depth will put the 
	// proper value into our WHERE param.  If we don't then  we'll set it
	// directly.
	//
	int depth;
	sscanf(comment, " depth: value = %d", &depth);
	if (this->image != NULL)
	    this->image->changeDepth(depth);
	else
	    this->setDepth(depth);
	return true;
    } else if (UIComponent::ParseGeometryComment(comment,file,lineno,
                        &this->xpos, &this->ypos,
                        &this->width, &this->height))  {
	ImageWindow *w = this->image;
        if (w && (this->xpos != UIComponent::UnspecifiedPosition)  &&
            theDXApplication->applyWindowPlacements()) {
	    //
	    // The comments, if they exist may cause a resize, but we don't
	    // want to cause an execution that normally results from  a resize. 
	    //
	    //bool was_execute_on_resize = w->isExecuteOnResize();	
	    //if (was_execute_on_resize) w->setExecuteOnResize(false);
	    w->setGeometry(this->xpos,this->ypos, this->width,this->height);
	    //
	    // This will tell ImageWindow to install a workproc for resetting
	    // the resize-on-execute flag.   This way resize event handling
	    // will get finished before the flag gets turned back on.
	    //
	    //if (was_execute_on_resize) w->resetExecuteOnResizeWhenAble();
	}
        return true;
    }

    return false; 
}
void    DisplayNode::openImageWindow(bool manage)
{
    ImageWindow *w = this->image;
    if (w == NULL)
    {
	if (this->userSpecifiedWhere) {
	    char pname[128];
	    ErrorMessage(
		"The user interface can not open the Image window for the %s\n"
		"tool because it has the input parameter '%s' set and\n"
		"therefore does not own the window.", 
		this->getNameString(),
		this->getInputNameString(3,pname));
	    return;
	} else {
	    w = this->getUnassociatedImageWindow();
	    ASSERT(w);
	    this->associateImage(w);
	    this->userSpecifiedWhere = false;
	    this->notifyWhereChange(manage);

	}
        if ((this->xpos != UIComponent::UnspecifiedPosition)  &&
            theDXApplication->applyWindowPlacements())
            w->setGeometry(this->xpos,this->ypos, this->width,this->height);
    }
    this->image->sensitizeChangeImageName(true);
    if (manage)
	w->manage();
}

char *DisplayNode::inputValueString(int i, const char *prefix)
{
    if (i != 3 || this->userSpecifiedWhere)
	return this->Node::inputValueString(i, prefix);
    else
    {
	char *retbuf, buf1[256], buf2[256];
	Parameter *p = this->getInputParameter(i);

	buf1[0] = '\0';
	this->strcatParameterNameLvalue(buf1, p, prefix, i);
	strcat(buf1, " = ");
	const char *cp = this->getTitle();
	if (cp)
	    sprintf(buf2, "\"X%d,,%s\";", this->getDepth(), cp);
	else
	    sprintf(buf2, "\"X%d,,\";", this->getDepth());
	retbuf = new char[strlen(buf1) + strlen(buf2) + 2];
	strcpy(retbuf, buf1);
	strcat(retbuf, buf2);

	return retbuf;
    }
}

bool DisplayNode::printIOComment(FILE *f, bool input, int index, 
			const char *indent, bool valueOnly)
{
    if (index == 3 && input && !this->userSpecifiedWhere)
	return true;
    else
	return this->Node::printIOComment(f, input, index, indent, valueOnly);
}

void DisplayNode::setLastImage(bool last)
{
    if(this->lastImage != last)
    {
	lastImage = last;
	if(this->image)
	    this->notifyWhereChange(true);
    }
}
bool DisplayNode::isLastImage()
{
    return this->lastImage;
}
//
// Determine if this node is of the given class.
//
bool DisplayNode::isA(Symbol classname)
{
    Symbol s = theSymbolManager->registerSymbol(ClassDisplayNode);
    if (s == classname)
	return true;
    else
	return this->DrivenNode::isA(classname);
}

#if WORKSPACE_PAGES
void DisplayNode::setGroupName(GroupRecord *grec, Symbol groupID)
{
    bool update_where = (grec?grec->changesWhere(): true);
    //
    // If we're just clearing old group information, then only update the
    // WHERE param, if the old group says it needs to.
    //
    if (!grec) {
	const char* current_group_name = this->getGroupName(groupID);
	if (current_group_name) {
	    Network* net = this->getNetwork();
	    Dictionary *gmgrs = net->getGroupManagers();
	    GroupManager* gmgr = (GroupManager*)gmgrs->findDefinition(groupID);
	    GroupRecord* old_grec = gmgr->getGroup(current_group_name);
	    if (!old_grec)
		update_where = false;
	    else if (old_grec->changesWhere() == false)
		update_where = false;
	}
    }
    this->Node::setGroupName(grec, groupID);
    if ((update_where) && (this->image))
	this->notifyWhereChange(true);
}
#else
void DisplayNode::setGroupName(const char *name)
{
    this->Node::setGroupName(name);
    if (this->image)
	this->notifyWhereChange(true);
}
#endif
void DisplayNode::setDefaultCfgState()
{
    if (this->panelAccessManager)
	this->panelAccessManager->clear();
}
//
// Return true if this node has state that will be saved in a .cfg file.
//
bool DisplayNode::hasCfgState()
{
    return true;
}

//
// Search through the networks list of image windows trying to find one
// that is not associated with a (display) node.  If canBeAnchor is true
// then any ImageWindow will do, otherwise the returned ImageWindow must
// not by an anchor window.
// If one is not found in the current list, then create one if requested.
//
ImageWindow *DisplayNode::getUnassociatedImageWindow(
			bool alloc_one, 
			bool canBeAnchor)
{
    List *imageList = this->getNetwork()->getImageList();
    ListIterator li;
    ImageWindow *w = NULL;
    DXWindow *anchor = theDXApplication->getAnchor();
    
    //
    // If this can be the anchor window, then try and get it first.
    //
    if (canBeAnchor && imageList->isMember((void*)anchor)) {
	ImageWindow *image_anchor = (ImageWindow*)anchor;
	ASSERT(image_anchor->isAnchor());
	if (!image_anchor->isAssociatedWithNode())
	    w = image_anchor;
    } 

    //
    // If the anchor window wasn't available, try for any other window.
    //
    if (!w) {
	li.setList(*imageList);
	while ( (w = (ImageWindow *)li.getNext()) ) {
	    if (!w->isAssociatedWithNode() && (canBeAnchor || !w->isAnchor()))
		break;
	}
    }

    if (alloc_one && (w == NULL)) {
        w = theDXApplication->newImageWindow(this->getNetwork());
        w->initialize();
    }
    return w;

}

void DisplayNode::switchNetwork(Network *from, Network *to, bool silently)
{
    if (this->panelAccessManager)  {
        delete this->panelAccessManager;
	this->panelAccessManager = NULL;
    }

    if (this->image && this->image != theDXApplication->getAnchor()) {
	delete this->image;
	this->image = NULL;
    }

    this->panelAccessManager = new PanelAccessManager(to);

    if (to->isMacro()) {
	if (!this->isInputConnected(WHERE)) {
	    this->notifyWhereChange(false);
	    this->useDefaultInputValue (WHERE, false);
	}
	this->associateImage(NUL(ImageWindow*));
    } else {
	ImageWindow *w = this->getUnassociatedImageWindow(true, false);
	if (w)
	    this->associateImage(w);
    }

    this->Node::switchNetwork(from, to, silently);
}

void DisplayNode::reflectStateChange(bool)
{
}

int DisplayNode::handleNodeMsgInfo(const char *line)
{
     return 0;
}
//
//  This is a DrivenNode, but has not message id parameter.
//
int DisplayNode::getMessageIdParamNumber() { return 0; }

const char *DisplayNode::getTitle()
{
    return this->title;
}


void DisplayNode::ioParameterStatusChanged(bool input, int index,
		     NodeParameterStatusChange status)
{
#if !defined(DONT_DEFINE_WINDOW_TYPE)
    //
    // If Where is wired up, then treat it the way we treat a user supplied window.
    // This handles wiring, unwiring, and unsetting.  The case of setting (thru
    // the cdb) is handled in this->setInputValue().  DisplayNodes still cling
    // tenaciously to their ImageWindows.  If you run the net and dxui provides
    // an ImageWindow for the DisplayNode, you won't be able to flip the Where
    // param tab up and so dxui will always provide the ImageWindow and the only
    // way to get around that is to delete the DisplayNode and place a new one.
    //
    if ((input) && (index == WHERE)) {
	if (status == ParameterArkAdded) {
	    this->userSpecifiedWhere = true;
	    if (this->image) {
		ImageWindow *iw = this->image;
		this->image = NUL(ImageWindow*);
		if (iw->isAnchor() == false)
		    delete iw;
	    }


	//
	// Flipping the param tab up, might be considered a way to indicate
	// that userSpecifiedWhere should be reset to false.  This was not
	// the behavior in 3.1.2.
	// Set network dirty because changing userSpecifiedWhere requires 
	// a call to DisplayNode::prepareToSend. 
	//
	} else if (status == ParameterArkRemoved) {
	    this->userSpecifiedWhere = false;
	} else if (status == ParameterSetValueToDefaulting) {
	    this->userSpecifiedWhere = false;
	    this->getNetwork()->setDirty();
	}
    }
#endif

    this->DrivenNode::ioParameterStatusChanged(input, index, status);
}

