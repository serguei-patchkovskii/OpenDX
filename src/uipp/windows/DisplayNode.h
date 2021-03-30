/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"


#ifndef _DisplayNode_h
#define _DisplayNode_h



#include "DrivenNode.h"


#define WHERE                   3

//
// Class name definition:
//
#define ClassDisplayNode	"DisplayNode"

//
// Referenced Classes
class ImageWindow;
class Network;
class PanelAccessManager;

//
// DisplayNode class definition:
//				
class DisplayNode : public DrivenNode
{
  private:
    //
    // Private member data:
    //
    static void HandleImageMessage(void *clientData, int id, void *line);
    PanelAccessManager *panelAccessManager;

    bool      printCommonComments(FILE *f, const char *indent = NULL);

    bool      parseCommonComments(const char *comment, const char *file,
			 int lineno);
    //
    // read/written to the .cfg file and passed to the editor window
    // when it is created.
    //
    int xpos,ypos, width, height; 

  protected:
    //
    // Protected member data:
    //
    bool	userSpecifiedWhere;
    ImageWindow *image;
    char	*title;
    int		depth;
    int		windowId;
    bool     lastImage;

    virtual void handleImageMessage(int id, const char *line);

    void         prepareToSendValue(int index, Parameter *p);
    void         prepareToSendNode();

    virtual bool netPrintAuxComment(FILE *f);
    virtual bool netParseAuxComment(const char *comment,
			 const char *file,
			 int lineno);

    virtual char        *inputValueString(int i, const char *prefix);
    virtual bool      printIOComment(FILE *f, bool input, int index,
				const char *indent = NULL, 
				bool valueOnly = false);

    //
    // Search through the networks list of image windows trying to find one
    // that is not associated with a (display) node.  If canBeAnchor is true
    // then any ImageWindow will do and if available we return an anchor
    // window, otherwise the returned ImageWindow must not by an anchor window.
    // If one is not found in the current list, then create one if requested.
    //
    ImageWindow *getUnassociatedImageWindow(
			bool alloc_one = true, bool canBeAnchor = true);

    virtual void switchNetwork(Network *from, Network *to, bool silently=false);

    //
    // Update any UI visuals that may be based on the state of this
    // node.   Among other times, this is called after receiving a message
    // from the executive.
    //
    virtual void reflectStateChange(bool unmanage);

    //
    // Parse the node specific info from an executive message.
    // Returns the number of attributes parsed.
    //
    virtual int  handleNodeMsgInfo(const char *line);


    //
    // This node does not have a message id param, so it 
    // returns 0.
    //
    virtual int getMessageIdParamNumber(); 

    //
    // Monitor the status of the WHERE param.  If the tab is connected, then
    // treat it as if the user had supplied a value.
    //
    virtual void ioParameterStatusChanged(bool input, int index,
			NodeParameterStatusChange status);

  public:
    //
    // Constructor:
    //
    DisplayNode(NodeDefinition *nd, Network *net, int instnc);

    //
    // Destructor:
    //
    ~DisplayNode();

    virtual bool cfgParseComment(const char* comment,
                                const char* filename, int lineno);
    virtual bool cfgPrintNode(FILE *f, PrintType);

    virtual bool initialize();

    virtual void setTitle(const char *title, bool fromServer = false);
    virtual const char *getTitle();

    void setDepth(int depth);
    int getDepth() { return this->depth;}

    virtual dx_Type setInputValue(int index,
		       const char *value,
		       dx_Type t = DXType::UndefinedType,
		       bool send = true);
    virtual bool associateImage(ImageWindow *w);
    void    notifyWhereChange(bool send);
    virtual void    openImageWindow(bool manage = true);

#if WORKSPACE_PAGES
    virtual void setGroupName(GroupRecord *grec, Symbol);
#else
    virtual void setGroupName(const char *name);
#endif
    virtual void setDefaultCfgState();


    void    setLastImage(bool last);
    bool isLastImage();


    PanelAccessManager* getPanelManager()
    {
	return this->panelAccessManager;
    }

    virtual bool useSoftwareRendering(){return true;};

    virtual DXWindow *getDXWindow() {return (DXWindow *)(this->image);}

    //
    // Determine if this node is a node of the given class
    //
    virtual bool isA(Symbol classname);

    //
    // Return true if this node has state that will be saved in a .cfg file.
    //
    virtual bool hasCfgState();

    virtual bool needsFastSort() { return true; }

    //
    // Returns a pointer to the class name.
    //
    virtual const char* getClassName()
    {
	return ClassDisplayNode;
    }
};


#endif // _DisplayNode_h
