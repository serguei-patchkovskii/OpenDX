/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"




#ifndef _ImageNode_h
#define _ImageNode_h


#include "DisplayNode.h"
#include "DXPacketIF.h"
#include "enums.h"


#define NO_RECORD_ENABLE              0
#define RECORD_ENABLE_NO_RERENDER     1
#define RECORD_ENABLE_RERENDER                2

//
// Class name definition:
//
#define ClassImageNode	"ImageNode"

//
// Referenced Classes
class ImageWindow;
class Network;

//
// ImageNode class definition:
//				
class ImageNode : public DisplayNode
{
  private:
    //
    // Private member data:
    //

    //
    //  Print/parse comments that are common to both .nets and .cfgs.
    //
    bool printCommonComments(FILE *f, const char *indent = NULL);
    bool parseCommonComments(const char* comment, const char *file,
                                        int lineno);
    //
    // The mode that was saved in the .net/.cfg file (when not data-driven). 
    //
    enum DirectInteractionMode savedInteractionMode;

    //
    // cache value for the nodes internal to the image macro.
    //
    enum Cacheability internalCache;

    //
    // FIXME!: this should really be being done through ImageWindow via
    // ImageNode::reflectStateChange().  ImageNode has no business setting
    // senstivities of another object.  That is ImageWindow's decision.
    //
    void  updateWindowSensitivities();

    Node* getWebOptionsNode();

    static bool SendString(void* , PacketIFCallback , FILE* , char* , bool);
    static void FormatMacro (FILE* , PacketIFCallback , void* , char* [], bool);


  protected:
    //
    // Protected member data:
    //
    static char*  GifMacroTxt[];
    static char*  VrmlMacroTxt[];
    static char*  ImageMacroTxt[];
    static char*  DXMacroTxt[];

    // The height which isn't stored in the parameter list.
    int height;

    // A bool which says whether we're translating old values
    // into new ones.
    bool translating;

    //
    // Fields and members to control the image macro.  When a parameter
    // that affects the image macro changes, macroDirty should be set
    // indicating that when ready, the system should update the macro.
    bool macroDirty;
    virtual bool sendMacro(DXPacketIF *pif);
    virtual bool printMacro(FILE *f,
			       PacketIFCallback callback = NULL,
                               void *callbackData = NULL,
                               bool viasocket  = false);

    
    // Fields for handling and storing parts of the image messages
    // sent from the executive.
    virtual void handleImageMessage(int id, const char *line);

    virtual void openDefaultWindow();

    //
    // Let the caller of openDefaultWindow() know what kind of window she's getting.
    // This is intended for use in EditorWindow so that we can sanity check the number
    // of cdbs were going to open before kicking off the operation and so that we
    // don't question the user before opening large numbers of interactors.
    // A name describing the type of window can be written into window_name in order
    // to enable nicer warning messages.
    //
    virtual bool defaultWindowIsCDB(char* window_name = NULL)
	{ if (window_name) strcpy (window_name, "Image Window"); return false; }

    double  boundingBox[4][3];

    // Overrides of Node members to ensure that the correct stuff
    // gets printed and sent to the server.  The image node prevents
    // "RECENABLE", whether to record frames or not, from being saved.
    virtual char   *inputValueString(int i, const char *prefix);
    virtual bool printIOComment(FILE *f, bool input, int index, 
					const char *indent = NULL,
					bool valuesOnly = false);

    virtual void notifyProjectionChange(bool newPersp);
    virtual void notifyUseVectorChange(bool newUse);

    virtual char *netEndOfMacroNodeString(const char *prefix);

    virtual bool netParseComment(const char* comment,
				    const char *file, int lineno);
    virtual bool netPrintAuxComment(FILE *f);
    virtual bool netParseAuxComment(const char *comment,
		const char *file,
		int lineno);



    virtual int  handleNodeMsgInfo(const char *line);
    virtual void reflectStateChange(bool unmanage);

    virtual void ioParameterStatusChanged(bool input, int index,
			    NodeParameterStatusChange status);

    //
    // Used by setAutoAxes{X,Y,Z}TickLocs().
    //
    void setAutoAxesTickLocs (int param, double *t, int size, bool send);

  public:
    //
    // Constructor:
    //
    ImageNode(NodeDefinition *nd, Network *net, int instnc);

    //
    // Destructor:
    //
    ~ImageNode();

    virtual bool initialize();

    virtual void setTitle(const char *title, bool fromServer = false);
    virtual const char *getTitle();

    virtual dx_Type setInputValue(int index,
		       const char *value,
		       dx_Type t = DXType::UndefinedType,
		       bool send = true);
    bool sendValues(bool ignoreDirty = true);
    virtual bool	printValues(FILE *f, const char *prefix, PrintType dest);
    virtual bool associateImage(ImageWindow *w);

    enum Cacheability getInternalCacheability() { return this->internalCache; }
    void setInternalCacheability(enum Cacheability c) { this->internalCache = c; }

    //
    // Access functions
    bool useVector();
    void    enableVector(bool use, bool send = true);
    void    setTo(double *to, bool send = true);
    void    setFrom(double *from, bool send = true);
    void    setResolution(int x, int y, bool send = true);
    void    setWidth(double w, bool send = true);
    void    setAspect(double a, bool send = true);
    void    setThrottle(double a, bool send = true);
    void    setUp(double *up, bool send = true);
    void    setBox(double box[4][3], bool send = true);
    void    setProjection(bool persp, bool send = true);
    void    setViewAngle(double angle, bool send = true);
    void    setButtonUp(bool up, bool send = true);
    void    setApprox(bool up, const char *approx, bool send = true);
    void    setDensity(bool up, int density, bool send = true);
    void    setBackgroundColor(const char *color, bool send = true);

    void    getTo(double *to);
    void    getFrom(double *from);
    void    getResolution(int &x, int &y);
    void    getWidth(double &w);
    void    getAspect(double &a);
    void    getThrottle(double &v);
    void    getUp(double *up);
    void    getBox(double box[4][3]);
    void    getProjection(bool &persp);
    void    getViewAngle(double &angle);
    bool isButtonUp();
    void    getApprox(bool up, const char *&approx);
    void    getDensity(bool up, int &density);
    void    getBackgroundColor(const char *&color);
    void    getRecordEnable(int &x);
    void    getRecordResolution(int &x, int &y);
    void    getRecordAspect(double &aspect);

    bool useAutoAxes();

    void    setRecordEnable(int use, bool send = true);
    void    setRecordResolution(int x, bool send = true);
    void    setRecordAspect(double aspect, bool send = true);
    void    setRecordFile(const char *file, bool send = true);
    void    setRecordFormat(const char *format, bool send = true);
    void    getRecordFile(const char *&file);
    void    getRecordFormat(const char *&format);

    void enableSoftwareRendering(bool use, bool send = true);

    //
    //
    //
    void getAutoAxesCorners (double dval[]);
    void getAutoAxesCursor (double *x,  double *y,   double *z);
    int getAutoAxesStringList (int index, char *sval[]);
    int getAutoAxesLabels (char *sval[]);
    int getAutoAxesAnnotation (char *sval[]);
    int getAutoAxesColors (char *sval[]);
    int getAutoAxesXTickLabels (char *sval[]);
    int getAutoAxesYTickLabels (char *sval[]);
    int getAutoAxesZTickLabels (char *sval[]);
    int getAutoAxesString (int index, char *sval);
    int getAutoAxesFont (char *sval);
    void getAutoAxesTicks (int *t1, int *t2, int *t3);
    void getAutoAxesTicks (int *t);
    void getAutoAxesXTickLocs (double **t, int *size);
    void getAutoAxesYTickLocs (double **t, int *size);
    void getAutoAxesZTickLocs (double **t, int *size);
    int getAutoAxesInteger (int index);
    int getAutoAxesEnable ();
    double getAutoAxesDouble (int index);
    double getAutoAxesLabelScale ();
    int getAutoAxesTicksCount ();

    void setAutoAxesCorners (double dval[], bool send);
    void setAutoAxesCursor (double x,   double  y,   double  z,    bool send);
    void setAutoAxesFlag (int index, bool state, bool send);
    void setAutoAxesFrame (bool state, bool send);
    void setAutoAxesGrid (bool state, bool send);
    void setAutoAxesAdjust (bool state, bool send);
    void setAutoAxesInteger (int index, int d, bool send);
    void setAutoAxesEnable (int d, bool send);
    void setAutoAxesDouble (int index, double d, bool send);
    void setAutoAxesLabelScale (double d, bool send);
    void setAutoAxesStringList (int index, char *value, bool send);
    void setAutoAxesLabels (char *value, bool send);
    void setAutoAxesAnnotation (char *value, bool send);
    void setAutoAxesColors (char *value, bool send);
    void setAutoAxesXTickLocs (double *t, int size, bool send);
    void setAutoAxesYTickLocs (double *t, int size, bool send);
    void setAutoAxesZTickLocs (double *t, int size, bool send);
    void setAutoAxesXTickLabels (char *value, bool send);
    void setAutoAxesYTickLabels (char *value, bool send);
    void setAutoAxesZTickLabels (char *value, bool send);
    void setAutoAxesString (int index, char *value, bool send);
    void setAutoAxesFont (char *value, bool send);
    void setAutoAxesTicks (int t1, int t2, int t3, bool send);
    void setAutoAxesTicks (int t, bool send);

    void disableAutoAxesCorners (bool send);
    void unsetAutoAxesCorners (bool send);
    void unsetAutoAxesCursor (bool send);
    void unsetAutoAxesTicks (bool send);
    void unsetAutoAxesXTickLocs (bool send);
    void unsetAutoAxesYTickLocs (bool send);
    void unsetAutoAxesZTickLocs (bool send);
    void unsetAutoAxesStringList (int index, bool send);
    void unsetAutoAxesAnnotation (bool send);
    void unsetAutoAxesLabels (bool send);
    void unsetAutoAxesColors (bool send);
    void unsetAutoAxesXTickLabels (bool send);
    void unsetAutoAxesYTickLabels (bool send);
    void unsetAutoAxesZTickLabels (bool send);
    void unsetAutoAxesString (int index, bool send);
    void unsetAutoAxesFont (bool send);
    void unsetAutoAxesEnable (bool send);
    void unsetAutoAxesFrame (bool send);
    void unsetAutoAxesGrid (bool send);
    void unsetAutoAxesAdjust (bool send);
    void unsetAutoAxesLabelScale (bool send);

    void unsetRecordResolution (bool send);
    void unsetRecordAspect (bool send);
    void unsetRecordFile (bool send);
    void unsetRecordFormat (bool send);
    void unsetRecordEnable (bool send);

    bool isAutoAxesCornersSet ();
    bool isAutoAxesCursorSet ();
    bool isSetAutoAxesFlag (int index);
    bool isSetAutoAxesFrame ();
    bool isSetAutoAxesGrid ();
    bool isSetAutoAxesAdjust ();
    bool isAutoAxesStringListSet (int index);
    bool isAutoAxesAnnotationSet ();
    bool isAutoAxesLabelsSet ();
    bool isAutoAxesColorsSet ();
    bool isAutoAxesStringSet (int index);
    bool isAutoAxesFontSet ();
    bool isAutoAxesTicksSet ();
    bool isAutoAxesXTickLocsSet ();
    bool isAutoAxesYTickLocsSet ();
    bool isAutoAxesZTickLocsSet ();
    bool isAutoAxesXTickLabelsSet ();
    bool isAutoAxesYTickLabelsSet ();
    bool isAutoAxesZTickLabelsSet ();
    bool isAutoAxesDoubleSet (int index);
    bool isAutoAxesLabelScaleSet ();


    bool useSoftwareRendering();

    virtual const char *getPickIdentifier();


    //
    // Save and retrieve image window state (camera, approx, render mode...)
    // to and from the .cfg file.
    //
    virtual bool cfgParseComment(const char* comment,
                                const char* filename, int lineno);
    virtual bool cfgPrintNode(FILE *f, PrintType);


    virtual void setDefaultCfgState();


    virtual dx_Type setInputSetValue(int index, const char *value,
				dx_Type type = DXType::UndefinedType,
				bool send = true);
    
    bool isAutoAxesEnableConnected();
    bool isAutoAxesCornersConnected();
    bool isAutoAxesCursorConnected();
    bool isAutoAxesFrameConnected();
    bool isAutoAxesGridConnected();
    bool isAutoAxesAdjustConnected();
    bool isAutoAxesAnnotationConnected();
    bool isAutoAxesLabelsConnected();
    bool isAutoAxesColorsConnected();
    bool isAutoAxesFontConnected();
    bool isAutoAxesTicksConnected();
    bool isAutoAxesXTickLocsConnected();
    bool isAutoAxesYTickLocsConnected();
    bool isAutoAxesZTickLocsConnected();
    bool isAutoAxesXTickLabelsConnected();
    bool isAutoAxesYTickLabelsConnected();
    bool isAutoAxesZTickLabelsConnected();
    bool isAutoAxesLabelScaleConnected();
    bool isBGColorConnected();
    bool isThrottleConnected();

    bool isViewControlInputSet();
    bool isImageNameInputSet();
    bool isRecordEnableSet();
    bool isRecordFileSet();
    bool isRecordFormatSet();
    bool isRecordResolutionSet();
    bool isRecordAspectSet();
    bool isRecFileInputSet();

    bool isRecordEnableConnected();
    bool isRecordFileConnected();
    bool isRecordFormatConnected();
    bool isRecordResolutionConnected();
    bool isRecordAspectConnected();
    bool isInteractionModeConnected();
    
    bool isRenderModeSet();
    bool isButtonUpApproxSet();
    bool isButtonDownApproxSet();
    bool isButtonUpDensitySet();
    bool isButtonDownDensitySet();
    bool isRenderModeConnected();
    bool isButtonUpApproxConnected();
    bool isButtonDownApproxConnected();
    bool isButtonUpDensityConnected();
    bool isButtonDownDensityConnected();

    bool isDataDriven();

    bool setInteractionMode(const char *mode);
    void    setInteractionModeParameter (DirectInteractionMode mode);
    virtual void    openImageWindow(bool manage = true);

    //  
    // Most nodes' id parameter is number 1 but a few aren't.  This number is
    // important because whenever you merge 2 nets, you update instance numbers.
    // When you do that, you must also change the id parameter and for that you
    // need its number.
    //
    virtual int getMessageIdParamNumber();

    //
    // On behalf of ImageFormatDialog (Save/Print Image dialogs) which needs to
    // know what strategy to use for saving the current image.
    //
    bool hardwareMode();
 

    //
    // Determine if this node is a node of the given class
    //
    virtual bool isA(Symbol classname);

    virtual void enableJava(const char* base_name, bool send=false);
    virtual void disableJava(bool send=false);
    virtual bool isJavified();
    virtual bool isJavified(Node* webOptions);
    virtual void javifyNode(Node* webOptions, Node*);
    virtual void unjavifyNode();
    virtual const char* getJavaNodeName() { return "ImageNode"; }
    virtual bool printInputAsJava(int input);
    const char* getWebOptionsFormat();
    bool isWebOptionsOrbit();
    virtual bool printAsJava(FILE*);
    bool isWebOptionsImgIdConnected();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassImageNode;
    }
};


#endif // _ImageNode_h
