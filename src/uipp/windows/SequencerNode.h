/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"


#ifndef _SequencerNode_h
#define _SequencerNode_h


#include "ShadowedOutputNode.h"

typedef long SequencerDirection;

//
// Class name definition:
//
#define ClassSequencerNode	"SequencerNode"

//
// Referenced Classes
//
class   SequencerWindow;
//
// SequencerNode class definition:
//				
class SequencerNode : public ShadowedOutputNode
{
  friend class SequencerWindow; 
  friend class DXExecCtl; 

  private:
    //
    // Private member data:
    //
    int xpos, ypos, width, height;

    //
    // Handler for 'frame %d %d' messages.
    //
    static void ProcessFrameInterrupt(void *clientData, int id, void *p);

    SequencerWindow* seq_window;
    bool         step;           /* step mode?                   */
    bool         loop;           /* loop mode?                   */
    bool         palindrome;     /* palindrome mode?             */

    bool         current_defined;/* current frame defined?       */
    bool         stop_requested; /* execution stop requested?    */
    int		    startValue;	    	// Start frame
    int		    stopValue;		// Stop frame

    //short           minimum;        /* minimum frame                */
    //short           maximum;        /* maximum frame                */
    //short           start;          /* start frame                  */
    //short           stop;           /* stop frame                   */
    //short           increment;      /* frame increment              */

    short           current;        /* current frame                */
    short           next;           /* current frame                */
    short           previous;       /* previous frame               */

    bool	    ignoreFirstFrameMsg;
    bool         transmitted;    /* frame values transmitted?    */
    //
    // Indicates if this node has ever been executed
    // (even across different executions of the User Interface).  This is
    // used to tell the Sequencer module in the executive when to ignore
    // the frame input (it ignores it if it has never been executed before).
    //
    bool	    wasExecuted;    // Has this instance ever been run 

    //
    // Nov, 1996 - added startup flag to print/parse operation so that you
    // could start in image mode without having the vcr appear.  To preserve
    // old behavior, record whether or not you actuall parsed a startup value
    // and treat those sequencers for which there was not value parsed as if
    // the vcr is a startup window.
    //
    bool startup;
    void setStartup(bool on = true) { this->startup = on; }

    //
    // Disable the Frame control.
    //
    void disableFrameControl();
    //
    // Enable the Frame control if the node is not data driven.
    //
    void enableFrameControl();
    //
    // Set the buttons that indicate the direction of play.
    //
    void setPlayDirection(SequencerDirection dir);
    void setForwardPlay();
    void setBackwardPlay();
    void setStepMode(bool step = true);
    void setLoopMode(bool loop = true);
    void setPalindromeMode(bool pal = true);

    // 
    //  Print/parse comments that are common to both .nets and .cfgs.
    // 
    bool printCommonComments(FILE *f, const char *indent = NULL);
    bool parseCommonComments(const char* comment,
                                        const char *file,
                                        int lineno);


  protected:
    //
    // Protected member data:
    //
    virtual char *netNodeString(const char *prefix);
    virtual char *valuesString(const char *prefix);
    virtual bool cfgPrintNode(FILE *f, PrintType dest);

    virtual bool     netPrintAuxComment(FILE *f);
    virtual bool     netParseAuxComment(const char* comment,
                                                const char *file, int lineno);

    //
    // The messages we parse can contain one or more of the following...
    //
    // 'min=%g' 'max=%g' 'start=%d' 'end=%d' 'delta=%g' 
    //
    // If any input or output values are to be changed, don't send them
    // because the module backing up the sequencer will have just executed
    // and if the UI is in 'execute on change' mode then there will be an
    // extra execution.
    //
    // Returns the number of attributes parsed.
    //
    virtual int handleNodeMsgInfo(const char *line);

    //
    // Update the Sequencer state that is based on the state of this
    // node.   Among other times, this is called after receiving a message
    // from the executive.
    //
    virtual void reflectStateChange(bool unmanage);

    //
    // Initialize the attributes with the give string values.
    //
    bool initMinimumValue(int val);
    bool setMinimumValue(int val);

    bool initMaximumValue(int val);
    bool setMaximumValue(int val);

    bool initDeltaValue(int val);
    bool setDeltaValue(int val);

    bool initStartValue(int val);
    bool setStartValue(int val);

    bool initStopValue(int val);
    bool setStopValue(int val);

#if 0
    bool isAttributeVisuallyWriteable(int input_index);

    bool setStartValue(const char *val);
    bool setStopValue(const char *val);
    bool setDeltaValue(const char *val);
    bool setMaximumValue(const char *val);
    bool setMinimumValue(const char *val);
#endif

    //
    // The Sequencer always expects the 'frame %d %d'  message and when
    // data-driven expects 'Sequencer_%d: ...' messages.  We install the
    // handler for the 'frame' message here and then call the super class
    // to install the 'Sequencer_%d:' handler.
    //
    virtual bool hasModuleMessagingProtocol() { return true; }
    virtual void updateModuleMessageProtocol(DXPacketIF *pif);

    //
    // If the min or max input has changed, update the attribute parameter
    // (integer list of min and max) and then call the super class method
    // if the input is not the attribute parameter.
    //
    virtual void ioParameterStatusChanged(bool input, int index,
                                NodeParameterStatusChange status);


    //
    // Make sure the value of the parameter that holds a list of ui attributes
    // (i.e. min/max/incr) is up to date in the executive.
    // Always send it since the input attribute is cache:0.
    //
    void updateAttributes();

  public:
    //
    // Constructor:
    //
    SequencerNode(NodeDefinition *nd, Network *net, int instnc);

    //
    // Destructor:
    //
    ~SequencerNode();

    enum {
	ForwardDirection 	= 1,
	BackwardDirection	= 2,
	Directionless		= 3
    };

    virtual bool initialize();
    void openDefaultWindow();
    bool isStartup();

    //
    // Let the caller of openDefaultWindow() know what kind of window she's getting.
    // This is intended for use in EditorWindow so that we can sanity check the number
    // of cdbs were going to open before kicking off the operation and so that we
    // don't question the user before opening large numbers of interactors.
    // A name describing the type of window can be written into window_name in order
    // to enable nicer warning messages.
    //
    virtual bool defaultWindowIsCDB(char* window_name = NULL)
	{ if (window_name) strcpy (window_name, "Sequencer"); return false; }

    virtual bool     cfgParseComment(const char* comment,
                                        const char *file, 
                                        int lineno);

    bool isMinimumVisuallyWriteable();
    bool isMaximumVisuallyWriteable();
#ifdef HAS_START_STOP
    bool isStartVisuallyWriteable();
    bool isStopVisuallyWriteable();
#endif
    bool isDeltaVisuallyWriteable();

    int	    getMinimumValue();
    int	    getMaximumValue();
    int	    getDeltaValue();
    int	    getStartValue();
    int	    getStopValue();


    bool isStepMode() { return this->step; }
    bool isLoopMode() { return this->loop; }
    bool isPalindromeMode() { return this->palindrome; }

    //
    // Get a string representing the assignment to the global vcr variables, 
    // @startframe, @frame, @nextframe, @endframe and @deltaframe.
    // The returned string must be deleted by the caller.
    //
    char *getFrameControlString();

    //Widget  getVCRWidget();

    //
    // Determine if this node is a node of the given class
    //
    virtual bool isA(Symbol classname);

    virtual bool canSwitchNetwork(Network *from, Network *to);

    virtual DXWindow *getDXWindow()
	{return (DXWindow *)this->seq_window;};

    //
    // Return true if this node has state that will be saved in a .cfg file.
    //
    virtual bool hasCfgState();

    //
    // Most nodes' id parameter is number 1 but a few aren't.  This number is
    // important because whenever you merge 2 nets, you update instance numbers.
    // When you do that, you must also change the id parameter and for that you
    // need its number.
    //
    virtual int getMessageIdParamNumber();

    virtual const char* getJavaNodeName() { return "SequencerNode"; }
    virtual bool printInputAsJava(int input);
    virtual const char *getJavaInputValueString(int index);




    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassSequencerNode;
    }
};


#endif // _SequencerNode_h
