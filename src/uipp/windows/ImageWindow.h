/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"


#ifndef _ImageWindow_h
#define _ImageWindow_h

#include <windows.h>

#include "DXWindow.h"
#include "NoUndoImageCommand.h"
#include "ToggleButtonInterface.h"
#include "enums.h"
#include "Network.h"
#include "AutoAxesDialog.h"
#include "SetBGColorDialog.h"

#include <vcclr.h>
#include "ImageWinForm.h"

//
// Class name definition:
//
#define ClassImageWindow	"ImageWindow"

//
// XtCallbackProc (*CB), XtEventHandler (*EH) and XtActionProc (*AP)
// DialogCallback (*DCB), XtInputCallbackProc (*ICP), XtWorkProc (*WP)
// functions for this and derived classes
//
//extern "C" void ImageWindow_ChangeImageNameCB(Widget, XtPointer, XtPointer);
//extern "C" void ImageWindow_TrackFrameBufferEH(Widget, XtPointer, XEvent*, Boolean*);
//extern "C" void ImageWindow_PropertyNotifyCB(Widget, XtPointer, XtPointer);
//extern "C" void ImageWindow_ClientMessageCB(Widget, XtPointer, XtPointer);
//extern "C" void ImageWindow_ResizeCB(Widget, XtPointer, XtPointer);
//extern "C" void ImageWindow_UndoCB(Widget, XtPointer, XtPointer);
//extern "C" void ImageWindow_KeyCB(Widget, XtPointer, XtPointer);
//extern "C" void ImageWindow_ModeCB(Widget, XtPointer, XtPointer);
//extern "C" void ImageWindow_PickCB(Widget, XtPointer, XtPointer);
//extern "C" void ImageWindow_CursorCB(Widget, XtPointer, XtPointer);
//extern "C" void ImageWindow_RotationCB(Widget, XtPointer, XtPointer);
//extern "C" void ImageWindow_NavigateCB(Widget, XtPointer, XtPointer);
//extern "C" void ImageWindow_RoamCB(Widget, XtPointer, XtPointer);
//extern "C" void ImageWindow_ZoomCB(Widget, XtPointer, XtPointer);
//extern "C" void ImageWindow_RedrawCB(Widget, XtPointer, XtPointer);
//extern "C" void ImageWindow_WindowsMenuMapCB(Widget, XtPointer, XtPointer);
//extern "C" void ImageWindow_FileMenuMapCB(Widget, XtPointer, XtPointer);
//extern "C" Boolean ImageWindow_ResetEORWP(XtPointer);
//extern "C" void ImageWindow_ResizeTO (XtPointer , XtIntervalId* );

//
// Referenced classes:
//
/*
class Network;
*/
class CommandScope;
class CommandInterface;
class Command;
class Node;
class ProbeNode;
class PickNode;
class ViewControlDialog;
class RenderingOptionsDialog;
class Dialog;
class AutoAxesDialog;
class XHandler;
class ThrottleDialog;
class PanelAccessManager;
class SaveImageDialog;
class SetImageNameDialog;
class PrintImageDialog;
class CascadeMenu;
class SetBGColorDialog;
class dxc_Stack;

enum ApproxMode 
{
    APPROX_NONE,
    APPROX_WIREFRAME,
    APPROX_DOTS,
    APPROX_BOX
};

enum ViewDirection
{
    VIEW_NONE,
    VIEW_TOP,
    VIEW_BOTTOM,
    VIEW_FRONT,
    VIEW_BACK,
    VIEW_LEFT,
    VIEW_RIGHT,
    VIEW_DIAGONAL,
    VIEW_OFF_TOP,
    VIEW_OFF_BOTTOM,
    VIEW_OFF_FRONT,
    VIEW_OFF_BACK,
    VIEW_OFF_LEFT,
    VIEW_OFF_RIGHT,
    VIEW_OFF_DIAGONAL
};
enum LookDirection
{
    LOOK_FORWARD,
    LOOK_LEFT45,
    LOOK_RIGHT45,
    LOOK_UP45,
    LOOK_DOWN45,
    LOOK_LEFT90,
    LOOK_RIGHT90,
    LOOK_UP90,
    LOOK_DOWN90,
    LOOK_BACKWARD,
    LOOK_ALIGN
};

enum ConstraintDirection
{
    CONSTRAINT_NONE,
    CONSTRAINT_X,
    CONSTRAINT_Y,
    CONSTRAINT_Z
};

struct ImageAtoms
{
    unsigned long                pick_point;        // unsigned longs for GL client  */
    unsigned long                start_pick;        // unsigned longs for GL client  */
    unsigned long                set_view;          // unsigned longs for GL client  */
    unsigned long                start_rotate;      // unsigned longs for GL client  */
    unsigned long                stop;              // unsigned longs for GL client  */
    unsigned long                start_zoom;        // unsigned longs for GL client  */
    unsigned long                start_panzoom;     // unsigned longs for GL client  */
    unsigned long                start_cursor;      // unsigned longs for GL client  */
    unsigned long                start_roam;        // unsigned longs for GL client  */
    unsigned long                start_navigate;    // unsigned longs for GL client  */
    unsigned long                from_vector;       // unsigned longs for GL client  */
    unsigned long                up_vector;         // unsigned longs for GL client  */
    unsigned long                zoom1;             // unsigned longs for GL client  */
    unsigned long                zoom2;             // unsigned longs for GL client  */
    unsigned long                roam;              // unsigned longs for GL client  */
    unsigned long                cursor_change;     // unsigned longs for GL client  */
    unsigned long                cursor_constraint; // unsigned longs for GL client  */
    unsigned long                cursor_speed;      // unsigned longs for GL client  */
    unsigned long                gl_window0;        // unsigned longs for GL server  */
    unsigned long                gl_window1;        // unsigned longs for GL server  */
    unsigned long                gl_window2;        // unsigned longs for GL server  */
    unsigned long                gl_window2_execute;// unsigned longs for GL server  */
    unsigned long                execute_on_change; // unsigned longs for GL server  */
    unsigned long                gl_destroy_window; // unsigned longs for GL server  */
    unsigned long                gl_shutdown;       // unsigned longs for GL server  */
    unsigned long                image_reset;       // unsigned longs for DX server  */
    unsigned long                dx_pixmap_id;      // unsigned longs for DX server  */
    unsigned long                dx_flag;           // unsigned longs for DX server  */
    unsigned long                display_globe;     // unsigned longs for DX server  */
    unsigned long                motion;            // unsigned longs for DX server  */
    unsigned long                pivot;             // unsigned longs for DX server  */
    unsigned long                undoable;          // unsigned longs for DX server  */
    unsigned long                redoable;          // unsigned longs for DX server  */
    unsigned long                undo_camera;       // unsigned longs for DX server  */
    unsigned long                redo_camera;       // unsigned longs for DX server  */
    unsigned long                push_camera;       // unsigned longs for DX server  */
    unsigned long                button_mapping1;   // unsigned longs for DX server  */
    unsigned long                button_mapping2;   // unsigned longs for DX server  */
    unsigned long                button_mapping3;   // unsigned longs for DX server  */
    unsigned long                navigate_look_at;  // unsigned longs for DX server  */
};

struct ImageCamera {
    double  to[3];
    double  up[3];
    double  from[3];
    double  width;
    int     windowWidth;
    int     windowHeight;
    double  viewAngle;
    double  zoomFactor;
    double  aspect;
    int     projection;
    bool undoable;
    bool redoable;
};
struct ImageState {
    int			width;
    int			height;
//    Pixmap		pixmap;
    //GC			gc;
    bool		hardwareRender;
    bool		hardwareRenderExists;
    bool		resizeFromServer;
    bool		frameBuffer;
    long		hardwareWindow;
    ImageCamera		hardwareCamera;
    bool		globeDisplayed;
    bool		degenerateBox;
    int			imageCount;
    bool		resizeCausesExecution;
    //
    // when turning resizeCausesExecution back on (it's turned off during
    // parsing), set a flag which will cause it to be turned on after a resize
    // event is delivered.  Otherwise the async arrival of a resize event will
    // cause an execution.
    //
    struct {
//	Window			window;
	int			x;
	int			y;
	int			width;
	int			height;
    }			parent;
    double 		navigateTranslateSpeed;
    double 		navigateRotateSpeed;
};


//
// ImageWindow class definition:
//				
class ImageWindow : public DXWindow
{
    friend class NoUndoImageCommand;

  private:
    //
    // Private class data:
    //
    static bool ClassInitialized;

    //friend void ImageWindow_FileMenuMapCB(Widget, XtPointer, XtPointer);
    //friend void ImageWindow_WindowsMenuMapCB(Widget, XtPointer, XtPointer);

    //
    // Static callback routines.
    //
    //friend void ImageWindow_RedrawCB(Widget	 drawingArea,
		  //       XtPointer clientData,
		  //       XtPointer callData);
    //friend void ImageWindow_ZoomCB(Widget	 drawingArea,
		  //     XtPointer clientData,
		  //     XtPointer callData);
    //friend void ImageWindow_RoamCB(Widget	 drawingArea,
		  //     XtPointer clientData,
		  //     XtPointer callData);
    //friend void ImageWindow_NavigateCB(Widget	 drawingArea,
		  //         XtPointer clientData,
		  //         XtPointer callData);
    //friend void ImageWindow_RotationCB(Widget	 drawingArea,
		  //         XtPointer clientData,
		  //         XtPointer callData);
    //friend void ImageWindow_CursorCB(Widget	 drawingArea,
		  //       XtPointer clientData,
		  //       XtPointer callData);
    //friend void ImageWindow_PickCB(Widget	 drawingArea,
		  //     XtPointer clientData,
		  //     XtPointer callData);
    //friend void ImageWindow_ModeCB(Widget	 drawingArea,
		  //     XtPointer clientData,
		  //     XtPointer callData);
    //friend void ImageWindow_KeyCB(Widget	 drawingArea,
		  //    XtPointer clientData,
		  //    XtPointer callData);
    //friend void ImageWindow_UndoCB(Widget	 drawingArea,
		  //     XtPointer clientData,
		  //     XtPointer callData);
    //friend void ImageWindow_ResizeCB(Widget	 drawingArea,
		  //      XtPointer clientData,
		  //      XtPointer callData);
    //friend void ImageWindow_ClientMessageCB(Widget 	  drawingArea,
			 //       XtPointer clientData,
			 //       XtPointer callData);
    //friend void ImageWindow_PropertyNotifyCB(Widget   drawingArea,
				//XtPointer clientData,
				//XtPointer callData);
    //friend void ImageWindow_TrackFrameBufferEH(Widget    drawingArea,
				//   XtPointer clientData,
				//   XEvent    *callData,
				//   Boolean   *continue_to_dispatch);
    //static bool HandleExposures(XEvent *event, void *clientData);
    //friend void ImageWindow_ChangeImageNameCB(Widget    selectBox,
		  //    		  XtPointer clientData,
		  //    		  XtPointer callData);
    //friend Boolean ImageWindow_ResetEORWP(XtPointer);
    //friend void ImageWindow_ResizeTO (XtPointer , XtIntervalId* );

    bool adjustDepth(int &depth);

    void completePictureCreation();
    List         panelNameList;
    List         panelGroupList;

    //
    // Ah yes, interaction modes.  I recently added the 
    // 'pendingInteractionMode' member, because it seems that under 
    // certain cirmumstances, setInteractionMode() was not actually
    // installing the mode in the window.  In these cases, we save
    // the new mode in pendingInteractionMode and set currentInteractionMode
    // to NONE.  Then at a later time (when we get a canvas) we can
    // apply the pending interaction mode with applyPendingInteractionMode().
    //
    // Install the given mode as the new interaction mode. 
    // If ignoreMatchingModes is false, then we return immediately if the
    // mode is already set otherwise, we go ahead and set the window for
    // the given mode.  See, set/activateInteractionMode().
    //
    DirectInteractionMode pendingInteractionMode;
    DirectInteractionMode currentInteractionMode;
    bool setInteractionMode(DirectInteractionMode mode,
                        bool ignoreMatchingModes);
#if 00
    bool activateInteractionMode();
#endif
    bool applyPendingInteractionMode();

    Network*		network;

    //
    // Image state 
    //
    bool		directInteraction;
    ImageAtoms		atoms;
    ImageState		state;
    dxc_Stack*		managed_state;

    // are we just switching between hardware and software?
    bool		switchingSoftware;

    // Have we pushed since the last execution?
    bool		pushedSinceExec;

    int		currentProbeInstance;	
    int		currentPickInstance;		

    Node		*node;		// Display or Image node associated.


    ViewControlDialog       *viewControlDialog;
    RenderingOptionsDialog  *renderingOptionsDialog;
    SetBGColorDialog        *backgroundColorDialog;
    ThrottleDialog          *throttleDialog;
    AutoAxesDialog          *autoAxesDialog;
    SetImageNameDialog	    *changeImageNameDialog;
    SaveImageDialog         *saveImageDialog;
    PrintImageDialog        *printImageDialog;

    //XHandler		    *fbEventHandler;



    virtual void resizeImage(bool ok_to_send=true);
    //virtual void zoomImage(XmPictureCallbackStruct*);
    //virtual void roamImage(XmPictureCallbackStruct*);
    //virtual void rotateImage(XmPictureCallbackStruct*);
    //virtual void navigateImage(XmPictureCallbackStruct*);
    //virtual void handleMode(XmPictureCallbackStruct*);
    //virtual void handleKey(XmPictureCallbackStruct*);
    virtual void pickImage(double x, double y);
    virtual void handleCursor(int reason, int cursor_num,
			      double x, double y, double z);

    //
    // Image window commands:
    //
    Command		*renderingOptionsCmd;
    Command			*softwareCmd;
    Command			*hardwareCmd;
    Command			*upNoneCmd;
    Command			*upWireframeCmd;
    Command			*upDotsCmd;
    Command			*upBoxCmd;
    Command			*downNoneCmd;
    Command			*downWireframeCmd;
    Command			*downDotsCmd;
    Command			*downBoxCmd;
    Command		*autoAxesCmd;
    Command		*throttleCmd;
    Command		*viewControlCmd;
    Command			*modeNoneCmd;
    Command			*modeCameraCmd;
    Command			*modeCursorsCmd;
    Command			*modePickCmd;
    Command			*modeNavigateCmd;
    Command			*modePanZoomCmd;
    Command			*modeRoamCmd;
    Command			*modeRotateCmd;
    Command			*modeZoomCmd;
    Command			*setViewNoneCmd;
    Command			*setViewTopCmd;
    Command			*setViewBottomCmd;
    Command			*setViewFrontCmd;
    Command			*setViewBackCmd;
    Command			*setViewLeftCmd;
    Command			*setViewRightCmd;
    Command			*setViewDiagonalCmd;
    Command			*setViewOffTopCmd;
    Command			*setViewOffBottomCmd;
    Command			*setViewOffFrontCmd;
    Command			*setViewOffBackCmd;
    Command			*setViewOffLeftCmd;
    Command			*setViewOffRightCmd;
    Command			*setViewOffDiagonalCmd;
    Command			*perspectiveCmd;
    Command			*parallelCmd;
    Command			*constrainNoneCmd;
    Command			*constrainXCmd;
    Command			*constrainYCmd;
    Command			*constrainZCmd;
    Command			*lookForwardCmd;
    Command			*lookLeft45Cmd;
    Command			*lookRight45Cmd;
    Command			*lookUp45Cmd;
    Command			*lookDown45Cmd;
    Command			*lookLeft90Cmd;
    Command			*lookRight90Cmd;
    Command			*lookUp90Cmd;
    Command			*lookDown90Cmd;
    Command			*lookBackwardCmd;
    Command			*lookAlignCmd;
    Command		*undoCmd;
    Command		*redoCmd;
    Command		*resetCmd;
    Command		*changeImageNameCmd;
    Command		*backgroundColorCmd;
    Command		*displayRotationGlobeCmd;
    Command             *openVPECmd;
    CascadeMenu		*modeOptionCascade;
    CascadeMenu		*imageDepthCascade;
    Command             *imageDepth8Cmd;
    Command             *imageDepth12Cmd;
    Command             *imageDepth15Cmd;
    Command             *imageDepth16Cmd;
    Command             *imageDepth24Cmd;
    Command		*imageDepth32Cmd;
    Command		*closeCmd;
    Command		*setPanelAccessCmd;
    Command		*saveImageCmd;
    Command		*printImageCmd;

    //
    // Image window components:
    //
    //Widget		form;
    //Widget		canvas;

    //
    // Menus & pulldowns:
    //
    //Widget		fileMenu;
    //Widget		windowsMenu;
    //Widget		optionsMenu;

    //Widget		fileMenuPulldown;
    //Widget		editMenuPulldown;
    //Widget		windowsMenuPulldown;
    //Widget		optionsMenuPulldown;

    //
    // File menu options:
    //
    CommandInterface*	openOption;
    CommandInterface*	saveOption;
    CommandInterface*	saveAsOption;
    CommandInterface*	openCfgOption;
    CommandInterface*	saveCfgOption;
    CommandInterface*	loadMacroOption;
    CommandInterface*	loadMDFOption;
    CommandInterface*   quitOption;
    CommandInterface*   closeOption;
    CommandInterface*	saveImageOption;
    CommandInterface*	printImageOption;
    CascadeMenu*	cfgSettingsCascadeMenu;

    //
    // Windows menu options:
    //
    CommandInterface*	openVisualProgramEditorOption;
    CommandInterface*	openAllControlPanelsOption;
    CascadeMenu		*openControlPanelByNameMenu;
    CommandInterface*	openAllColormapEditorsOption;
    CommandInterface*	messageWindowOption;

    //
    // Options menu options:
    //
    CommandInterface*	renderingOptionsOption;
    CommandInterface*	autoAxesOption;
    CommandInterface*	throttleOption;
    CommandInterface*	viewControlOption;
    CommandInterface*	modeOption;
    CommandInterface*	undoOption;
    CommandInterface*	redoOption;
    CommandInterface*	resetOption;
    CommandInterface*	changeImageNameOption;
    CommandInterface*	backgroundColorOption;
    CommandInterface*	displayRotationGlobeOption;

    ToggleButtonInterface*	modeNoneOption;
    ToggleButtonInterface*	modeCameraOption;
    ToggleButtonInterface*	modeCursorsOption;
    ToggleButtonInterface*	modePickOption;
    ToggleButtonInterface*	modeNavigateOption;
    ToggleButtonInterface*	modePanZoomOption;
    ToggleButtonInterface*	modeRoamOption;
    ToggleButtonInterface*	modeRotateOption;
    ToggleButtonInterface*	modeZoomOption;

    ToggleButtonInterface*	imageDepth8Option;
    ToggleButtonInterface*	imageDepth12Option;
    ToggleButtonInterface*	imageDepth15Option;
    ToggleButtonInterface*	imageDepth16Option;
    ToggleButtonInterface*	imageDepth24Option;
    ToggleButtonInterface*	imageDepth32Option;
    CommandInterface*	setPanelAccessOption;

    //
    // Addition help menu options:
    //
    CommandInterface*	onVisualProgramOption;

    bool cameraInitialized;

    //
    // add a work proc for resetting the execute-on-resize flag because
    // resize events are async and must be turned off following parseCommonComments.
    // But before turning it back on, do a sync and wait once.  This is once per
    // class because doing a sync affects all image windows.  Therefore it's not
    // necessary to do one for each window.
    //
    //XtWorkProcId reset_eor_wp;
    int  pending_resize_x, pending_resize_y; 
    int  pending_resize_width, pending_resize_height;
    static bool NeedsSyncForResize;

  protected:

    //static String  DefaultResources[];

    //
    // Creates the editor window workarea (as required by MainWindow class).
    //
    virtual void* createWorkArea();

    //
    // Creates the editor window menus (as required by DXWindow class).
    //
    //virtual void createMenus(Widget parent);

    //
    // Creation routine for each of the editor menus:
    //   Intended to be used in derived class createMenus(), if needed,
    //   to better control the menu creation, or to be overriden in
    //   the derived classes.
    //
    //virtual void createFileMenu(Widget parent);
    //virtual void createWindowsMenu(Widget parent);
    //virtual void createOptionsMenu(Widget parent);
    //virtual void createHelpMenu(Widget parent);

    //
    // These routines send messages to the gl rendering portion of the
    // server software.
    void sendClientMessage(unsigned long atom, int num, long  *longs);
    void sendClientMessage(unsigned long atom, long oneLong)
    {
	this->sendClientMessage(atom, 1, &oneLong);
    }
    void sendClientMessage(unsigned long atom) 
    {
	this->sendClientMessage(atom, 0, (long*)NULL);
    }
    void sendClientMessage(unsigned long atom, int num, short *shorts);
    void sendClientMessage(unsigned long atom, int num, char  *chars);
    void sendClientMessage(unsigned long atom, int num, float *floats);
    void sendClientMessage(unsigned long atom, float oneFloat)
    {
	this->sendClientMessage(atom, 1, &oneFloat);
    }

    void wait4GLAcknowledge();

    //
    // Do any image window specific stuff to get the canvas ready for an
    // image.
    virtual void newCanvasImage();
    //virtual void trackFrameBuffer(XEvent *event, Boolean *continue_to_dispatch);
    //virtual bool handleExposures(XEvent *event);

    virtual void serverDisconnected();

    void saveImage();

    //
    // Set the state and sensitivity of the ImageDepth cascade menu and its
    // command interfaces.
    //
    void configureImageDepthMenu();

    //
    // Set the state and sensitivity of the Mode cascade menu and its
    // command interfaces.
    //
    void configureModeMenu();


    Node *getNodeByInstance(const char *classname, const char *name, 
					int instance);
    
    //
    // Install the default resources for this class and then call the
    // same super class method to get the default resources from the
    // super classes.
    //
    //virtual void installDefaultResources(Widget baseWidget);

    //
    // The superclass has responsibility for the wizard window but here we'll
    // substitute the application comment for the wizard window.  They look pretty
    // much the same.
    //
    virtual void postWizard();

    //
    // Allow subclasses to supply a string for the XmNgeometry resource
    // (i.e. -geam 90x60-0-0) which we'll use instead of createX,createY,
    // createWidth, createHeight when making the new window.  If the string
    // is available then initialize() won't call setGeometry.
    //
    virtual void getGeometryAlternateNames(char**, int*, int);

    //virtual int displayWidth() { return 1280; }
    //virtual int displayHeight() { return 1024; }

    //
    // Rather than triggering an execution following a window resize,
    // Queue the execution so that it happens soon after the execution
    // but not immediately after.  This gives better results for users
    // with window mgrs that deliver tons of resize events
    //
    //XtIntervalId execute_after_resize_to;


  public:
    //
    // Constructor for the masses:
    //
    ImageWindow(bool  isAnchor, Network* network);

	gcroot<dxui::ImageWinForm *> iw;

    //
    // Destructor:
    //
    ~ImageWindow();

    //
    // Sets the default resources before calling the superclass
    // initialize() function.
    //
    virtual void initialize();

    //
    // Handle client messages (not from the exec).
    //
    virtual void notify
	(const Symbol message, const void *msgdata=NULL, const char *msg=NULL);

    //
    // Redefine unmanage to unmanaged all child dialogs
    virtual void unmanage();

    //
    // Redefine manage to add tracking on frame buffer
    virtual void manage();

    //
    // Redefine setGeometry in order to deal with the WHERE parameter
    void setGeometry (int x, int y, int width, int height);

    // 
    // A routine to install all per-canvas callbacks.
    virtual void installCallbacks();

    //
    // Probe and Pick management:
    //
    void    addProbe(Node*);
    void    deleteProbe(Node*);
    void    changeProbe(Node*);
    bool selectProbeByInstance(int instanceNumber);
    ProbeNode    *getCurrentProbeNode();
    bool setCurrentProbe(int instanceNumber);

    void    addPick(Node*);
    void    deletePick(Node*);
    void    changePick(Node*);
    bool selectPickByInstance(int instanceNumber);
    PickNode   *getCurrentPickNode();
    bool setCurrentPick(int instanceNumber);

    //
    // three functions to control the hightlighting of the Execute button.
    //
    virtual void beginExecution();
    virtual void standBy();
    virtual void endExecution();

 //   Widget getCanvas()
 //   {
	//return this->canvas;
 //   }
    bool directInteractionAllowed()
    {
	return this->directInteraction;
    }
    void allowDirectInteraction(bool allow);

    virtual void clearFrameBufferOverlay();

    //
    // Associates an Image or Display style node with an ImageWindow.
    // Returns true if there wasn't another node already associated, false
    // if there was.
    bool associateNode(Node *n);
    Node   *getAssociatedNode() { return this->node; }
    bool isAssociatedWithNode();


    bool enablePerspective(bool enable);
    bool getPerspective();
    void setViewAngle(double viewAngle);
    void getViewAngle(double &viewAngle);
    void setResolution(int x, int y);
    void getResolution(int &x, int &y);
    void setWidth(double w);
    void getWidth(double &w);
    void setTo(double *v);
    void setFrom(double *v);
    void setUp(double *v);
    void getTo(double *v);
    void getFrom(double *v);
    void getUp(double *v);
    void getThrottle(double &v);
    void setThrottle(double v);
    bool updateThrottleDialog(double v);

    bool isAutoAxesCursorSet ();
    bool isAutoAxesCornersSet ();
    bool isSetAutoAxesFrame ();
    bool isSetAutoAxesGrid ();
    bool isSetAutoAxesAdjust ();
    bool isAutoAxesAnnotationSet ();
    bool isAutoAxesLabelsSet ();
    bool isAutoAxesColorsSet ();
    bool isAutoAxesFontSet ();
    bool isAutoAxesTicksSet ();
    bool isAutoAxesLabelScaleSet ();
    bool isAutoAxesXTickLocsSet ();
    bool isAutoAxesYTickLocsSet ();
    bool isAutoAxesZTickLocsSet ();
    bool isAutoAxesXTickLabelsSet ();
    bool isAutoAxesYTickLabelsSet ();
    bool isAutoAxesZTickLabelsSet ();

    bool isBGColorConnected ();
    bool isThrottleConnected ();
    bool isRecordEnableConnected ();
    bool isRecordFileConnected ();
    bool isRecordFormatConnected ();
    bool isRecordResolutionConnected ();
    bool isRecordAspectConnected ();
    bool isAutoAxesEnableConnected ();
    bool isAutoAxesCornersConnected ();
    bool isAutoAxesCursorConnected ();
    bool isAutoAxesFrameConnected ();
    bool isAutoAxesGridConnected ();
    bool isAutoAxesAdjustConnected ();
    bool isAutoAxesAnnotationConnected ();
    bool isAutoAxesLabelsConnected ();
    bool isAutoAxesColorsConnected ();
    bool isAutoAxesFontConnected ();
    bool isAutoAxesTicksConnected ();
    bool isAutoAxesXTickLocsConnected ();
    bool isAutoAxesYTickLocsConnected ();
    bool isAutoAxesZTickLocsConnected ();
    bool isAutoAxesXTickLabelsConnected ();
    bool isAutoAxesYTickLabelsConnected ();
    bool isAutoAxesZTickLabelsConnected ();
    bool isAutoAxesLabelScaleConnected ();
    bool isRenderModeConnected ();
    bool isButtonUpApproxConnected ();
    bool isButtonDownApproxConnected ();
    bool isButtonUpDensityConnected ();
    bool isButtonDownDensityConnected ();

    void getAutoAxesCorners (double dval[]);
    void getAutoAxesCursor (double *x, double *y, double *z);
    int getAutoAxesAnnotation (char *sval[]);
    int getAutoAxesLabels (char *sval[]);
    int getAutoAxesColors (char *sval[]);
    int getAutoAxesFont (char *sval);
    void getAutoAxesTicks (int *t1, int *t2, int *t3);
    void getAutoAxesTicks (int *t);
    void getAutoAxesXTickLocs (double **t, int *size);
    void getAutoAxesYTickLocs (double **t, int *size);
    void getAutoAxesZTickLocs (double **t, int *size);
    int getAutoAxesXTickLabels (char *sval[]);
    int getAutoAxesYTickLabels (char *sval[]);
    int getAutoAxesZTickLabels (char *sval[]);
    int getAutoAxesEnable ();
    double getAutoAxesLabelScale ();
    int getAutoAxesTicksCount ();

    void setAutoAxesCorners (double dval[], bool send);
    void setAutoAxesCursor (double x, double  y, double  z, bool send);
    void setAutoAxesFrame (bool state, bool send);
    void setAutoAxesGrid (bool state, bool send);
    void setAutoAxesAdjust (bool state, bool send);
    void setAutoAxesEnable (int d, bool send);
    void setAutoAxesLabelScale (double d, bool send);
    void setAutoAxesAnnotation (char *value, bool send);
    void setAutoAxesColors (char *value, bool send);
    void setAutoAxesLabels (char *value, bool send);
    void setAutoAxesFont (char *value, bool send);
    void setAutoAxesTicks (int t1, int t2, int t3, bool send);
    void setAutoAxesTicks (int t, bool send);
    void setAutoAxesXTickLocs (double *t, int size, bool send);
    void setAutoAxesYTickLocs (double *t, int size, bool send);
    void setAutoAxesZTickLocs (double *t, int size, bool send);
    void setAutoAxesXTickLabels (char *value, bool send);
    void setAutoAxesYTickLabels (char *value, bool send);
    void setAutoAxesZTickLabels (char *value, bool send);

    void unsetAutoAxesCorners (bool send);
    void unsetAutoAxesCursor (bool send);
    void unsetAutoAxesTicks (bool send);
    void unsetAutoAxesXTickLocs (bool send);
    void unsetAutoAxesYTickLocs (bool send);
    void unsetAutoAxesZTickLocs (bool send);
    void unsetAutoAxesXTickLabels (bool send);
    void unsetAutoAxesYTickLabels (bool send);
    void unsetAutoAxesZTickLabels (bool send);
    void unsetAutoAxesAnnotation (bool send);
    void unsetAutoAxesLabels (bool send);
    void unsetAutoAxesColors (bool send);
    void unsetAutoAxesFont (bool send);
    void unsetAutoAxesEnable (bool send);
    void unsetAutoAxesFrame (bool send);
    void unsetAutoAxesGrid (bool send);
    void unsetAutoAxesAdjust (bool send);
    void unsetAutoAxesLabelScale (bool send);

    void setTranslateSpeed(double);
    void setRotateSpeed(double);
    double getTranslateSpeed();
    double getRotateSpeed();

    void setSoftware(bool sw);
    void getSoftware(bool &sw);
    void setApproximation(bool up, ApproxMode mode);
    void getApproximation(bool up, ApproxMode &mode);
    void setDensity(bool up, int density);
    void getDensity(bool up, int &density);

    bool setInteractionMode(DirectInteractionMode mode);
    DirectInteractionMode getInteractionMode();

    void newCamera(int image_width, int image_height);
    void newCamera(double box[4][3], double aamat[4][4], double *from, double *to, 
	double *up, int image_width, int image_height, double width,
	bool perspective, double viewAngle);
    void undoCamera();
    void redoCamera();
    void resetCamera();
    bool setView(ViewDirection direction); 
    bool setLook(LookDirection direction); 
    bool setConstraint(ConstraintDirection direction); 
    ConstraintDirection getConstraint();

    bool setBackgroundColor(const char *color); 
    bool updateBGColorDialog(const char *color); 
    const char *getBackgroundColor();
    void  setDisplayGlobe();

    bool enableRecord(bool enable);
    bool useRecord();
    bool setRecordFile(const char *file);
    bool setRecordFormat(const char *format);
    const char *getRecordFile();
    const char *getRecordFormat();
    void getRecordResolution(int &x, int &y);
    double getRecordAspect();

    //
    // What to do when we need to reset the window because the server has
    // forgotten about us.
    //
    virtual void resetWindow();
    //
    // getDisplayString() returns a static char *.  It goes away on the next
    // call.  DON'T FREE or DELETE IT!  It returns NULL on error.
    //
    char *getDisplayString();

    //
    // Change the frame buffer depth of the picture widget
    //
    void changeDepth(int depth);

    //
    // Post several of the controlling dialogs.
    //
    bool postRenderingOptionsDialog();
    bool postAutoAxesDialog();
    bool postThrottleDialog();
    bool postViewControlDialog();
    bool postChangeImageNameDialog();
    bool postBackgroundColorDialog();
    bool postVPE();
    bool postSaveImageDialog();
    bool postPrintImageDialog();


    void sensitizePrintImageDialog(bool flag);
    void sensitizeSaveImageDialog(bool flag);
    void sensitizeThrottleDialog(bool flag);

    //
    // Get commands.
    //
    CommandScope *getCommandScope() { return this->commandScope; }
    Command *getUndoCmd() { return this->undoCmd; }
    Command *getRedoCmd() { return this->redoCmd; }
    Command *getResetCmd() { return this->resetCmd; }
    Command *getModeNoneCmd() { return this->modeNoneCmd; }
    Command *getModeCameraCmd() { return this->modeCameraCmd; }
    Command *getModeCursorsCmd() { return this->modeCursorsCmd; }
    Command *getModePickCmd() { return this->modePickCmd; }
    Command *getModeNavigateCmd() { return this->modeNavigateCmd; }
    Command *getModePanZoomCmd() { return this->modePanZoomCmd; }
    Command *getModeRoamCmd() { return this->modeRoamCmd; }
    Command *getModeRotateCmd() { return this->modeRotateCmd; }
    Command *getModeZoomCmd() { return this->modeZoomCmd; }
    Command *getSetViewNoneCmd() { return this->setViewNoneCmd; }
    Command *getSetViewTopCmd() { return this->setViewTopCmd; }
    Command *getSetViewBottomCmd() { return this->setViewBottomCmd; }
    Command *getSetViewFrontCmd() { return this->setViewFrontCmd; }
    Command *getSetViewBackCmd() { return this->setViewBackCmd; }
    Command *getSetViewLeftCmd() { return this->setViewLeftCmd; }
    Command *getSetViewRightCmd() { return this->setViewRightCmd; }
    Command *getSetViewDiagonalCmd() { return this->setViewDiagonalCmd; }
    Command *getSetViewOffTopCmd() { return this->setViewOffTopCmd; }
    Command *getSetViewOffBottomCmd() { return this->setViewOffBottomCmd; }
    Command *getSetViewOffFrontCmd() { return this->setViewOffFrontCmd; }
    Command *getSetViewOffBackCmd() { return this->setViewOffBackCmd; }
    Command *getSetViewOffLeftCmd() { return this->setViewOffLeftCmd; }
    Command *getSetViewOffRightCmd() { return this->setViewOffRightCmd; }
    Command *getSetViewOffDiagonalCmd() { return this->setViewOffDiagonalCmd; }
    Command *getPerspectiveCmd() { return this->perspectiveCmd; }
    Command *getParallelCmd() { return this->parallelCmd; }
    Command *getConstrainNoneCmd() { return this->constrainNoneCmd; }
    Command *getConstrainXCmd() { return this->constrainXCmd; }
    Command *getConstrainYCmd() { return this->constrainYCmd; }
    Command *getConstrainZCmd() { return this->constrainZCmd; }
    Command *getLookForwardCmd() { return this->lookForwardCmd; }
    Command *getLookLeft45Cmd() { return this->lookLeft45Cmd; }
    Command *getLookRight45Cmd() { return this->lookRight45Cmd; }
    Command *getLookUp45Cmd() { return this->lookUp45Cmd; }
    Command *getLookDown45Cmd() { return this->lookDown45Cmd; }
    Command *getLookLeft90Cmd() { return this->lookLeft90Cmd; }
    Command *getLookRight90Cmd() { return this->lookRight90Cmd; }
    Command *getLookUp90Cmd() { return this->lookUp90Cmd; }
    Command *getLookDown90Cmd() { return this->lookDown90Cmd; }
    Command *getLookBackwardCmd() { return this->lookBackwardCmd; }
    Command *getLookAlignCmd() { return this->lookAlignCmd; }
    Command *getSoftwareCmd()    { return this->softwareCmd; }
    Command *getHardwareCmd()    { return this->hardwareCmd; }
    Command *getUpNoneCmd()    { return this->upNoneCmd; }
    Command *getUpWireframeCmd()    { return this->upWireframeCmd; }
    Command *getUpDotsCmd()    { return this->upDotsCmd; }
    Command *getUpBoxCmd()    { return this->upBoxCmd; }
    Command *getDownNoneCmd()    { return this->downNoneCmd; }
    Command *getDownWireframeCmd()    { return this->downWireframeCmd; }
    Command *getDownDotsCmd()    { return this->downDotsCmd; }
    Command *getDownBoxCmd()    { return this->downBoxCmd; }

    void setAutoAxesDialogTicks();
    void setAutoAxesDialogFrame();
    void setAutoAxesDialogGrid();
    void setAutoAxesDialogAdjust();
    void setAutoAxesDialogLabels();
    void setAutoAxesDialogLabelScale();
    void setAutoAxesDialogFont();
    void setAutoAxesDialogAnnotationColors();
    void setAutoAxesDialogCorners();
    void setAutoAxesDialogCursor();
    void setAutoAxesDialogEnable();
    void setAutoAxesDialogXTickLocs();
    void setAutoAxesDialogYTickLocs();
    void setAutoAxesDialogZTickLocs();
    void setAutoAxesDialogXTickLabels();
    void setAutoAxesDialogYTickLabels();
    void setAutoAxesDialogZTickLabels();

    void sensitizeViewControl(bool flag);
    void sensitizeChangeImageName(bool flag);
    void sensitizeRenderMode(bool flag);
    void sensitizeButtonUpApprox(bool flag);
    void sensitizeButtonDownApprox(bool flag);
    void sensitizeButtonUpDensity(bool flag);
    void sensitizeButtonDownDensity(bool flag);


    //
    // Set the title of the window based on this windows associated node
    // and whether or not this window is the anchor or not.
    // The title will either be the assigned name, the name of the
    // associated node or the name of the network file.
    //
    void resetWindowTitle();

    //
    // Allow the DisplayNode to turn off execution on resizes due to
    // reading the 'window: pos=... size=...' comments. 
    //
    bool isExecuteOnResize() { return this->state.resizeCausesExecution; }
    void setExecuteOnResize(bool setting = true) 
				{ this->state.resizeCausesExecution = setting; }
    void resetExecuteOnResizeWhenAble();
    //bool hasPendingWindowPlacement() { return (bool)(this->reset_eor_wp != 0); }
 
    //
    // Before calling the super class method we verify that doing this will 
    // leave at least one startup image window.  If not, issue an error and
    // return without calling the super class method.
    //
    virtual void toggleWindowStartup();

    Network *getNetwork();

    //
    // Update the autoaxes dialog with whatever the current
    // values in the ImageNode are data-driven
    void updateAutoAxesDialog();
    void updateRenderingOptionsDialog();

    //
    // Update any displayed information from the new cfg state found in
    // the associated ImageNode. 
    //
    void updateFromNewCfgState();

    //
    // Allow the node to set the sensitivity of the background
    // color dialog box when the associated tab is attached/deattached
    // to an arc.
    void sensitizeBackgroundColorDialog(bool flag);

    //
    // Determine whether the camera has been initializes
    bool cameraIsInitialized() { return this->cameraInitialized;}

    //
    // Called by the MainWindow CloseCallback.  We call the super class
    // method and then, if we are not an anchor and are in DataViewer mode
    // then we exit the program.
    //
    virtual void closeWindow();

    //
    // On behalf of ImageFormatDialog (Save/Print Image dialogs) which needs to
    // know what strategy to use for saving the current image.
    //
    bool hardwareMode() { return this->state.hardwareRender; }

    //
    // Make sure the changing the window title doesn't change the where
    // parameter (due to new window placement features.)
    //
    virtual void setWindowTitle(const char* name, bool check_geometry=false);


    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassImageWindow;
    }
};


#endif // _ImageWindow_h
