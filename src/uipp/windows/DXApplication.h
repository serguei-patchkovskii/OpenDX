/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

#ifndef _DXApplication_h
#define _DXApplication_h

#include "IBMApplication.h"
#include "List.h"
#include "Dictionary.h"
#include "DXExecCtl.h"
#include "License.h"
#include "FileDialog.h"

class HelpWin;
class MsgWin;
class ImageWindow;
class ControlPanel;

#define RECENT_NETS "recentNets"

//
// Class name definition:
//
#define ClassDXApplication	"DXApplication"

//extern "C" int DXApplication_DXAfterFunction(Display *display);

extern "C" void
#if defined(ALTERNATE_CXX_SIGNAL) 
	DXApplication_HandleCoreDump(int dummy, ... );
#else
	DXApplication_HandleCoreDump(int dummy);
#endif

typedef struct
{
    //
    // options and resources:
    //
    char*	server;
    char*	executive;
    char*	workingDirectory;

    char*	program;
    char*	cfgfile;
    char*	userModules;
    char*	macros;
    char*      errorPath;

    char*	executiveModule;
    char*	uiModule;

    bool	noWindowPlacement;

    int		port;
    int		memorySize;

    bool	echoVersion;
    char*	anchorMode;
    bool	noAnchorAtStartup;
    bool	noConfirmedQuit;
    bool	debugMode;
    bool	showInstanceNumbers;
    bool	runUIOnly;
    bool	runLocally;
    bool	showHelpMessage;
    bool	executeProgram;
    bool	executeOnChange;
    bool	suppressStartupWindows;
    bool	isMetric;
    bool	exitAfter;
    bool	noExitOptions;
    bool	noExecuteMenus;
    bool	noConnectionMenus;
    bool	noWindowsMenus;

    //
    // Image window image saving/printing control
    //
    char*	printImageFormat;
    char*	printImagePageSize;	// wxh in inches or cm (see isMetric)
    int		printImageResolution;	// Dots per inch or cm (see isMetric)
    char*	printImageSize;		// "8" or "8x" or "x10" or "8x10"
    char*	printImageCommand;

    char*	saveImageFormat;	
    char*	saveImagePageSize;	// wxh in inches or cm (see isMetric)
    int		saveImageResolution;	// Dots per inch or cm (see isMetric)
    char*	saveImageSize;		// "8", "8x", "x10" or "8x10" cm or "
 
    //
    // Message Window control
    //
    bool	infoEnabled;
    bool	warningEnabled;
    bool	errorEnabled;
    bool	moduleInfoOpensMessage;
    bool	infoOpensMessage;
    bool	warningOpensMessage;
    bool	errorOpensMessage;

    //
    // Configurability level 
    //
    char*	restrictionLevel;
    bool	useWindowSpecs;
    bool	noRWConfig;

    //
    // Panel configurability 
    //
    bool	noOpenAllPanels;
    bool	noPanelEdit;
    bool	noPanelAccess;
    bool	noPanelOptions;

    //
    // Interactor/panel  configurability 
    //
    bool	noInteractorEdits;
    bool	noInteractorAttributes;
    bool	noInteractorMovement;

    //
    // Image/Editor window configurability 
    //
    bool	noImageMenus;
    bool	noImageRWNetFile;
    bool	limitedNetFileSelection;
    char*	netPath;
    bool	noImageLoad;
    bool	noEditorAccess;
    bool	limitImageOptions;
    bool	noImageSaving;
    bool	noImagePrinting;
    bool     notifySaveNet;
    bool     noNetworkExecute;

    //
    // Message window  configurability
    //
    bool	noScriptCommands;
    bool	noMessageInfoOption;
    bool	noMessageWarningOption;
    bool	noEditorOnError;

    //
    // ColormapEditor window configurability
    //
    bool	noCMapSetNameOption;
    bool	noCMapOpenMap;
    bool	noCMapSaveMap;


    //
    // Process group defining and host assignments. 
    //
    bool	noPGroupAssignment;

    //
    // Global configurability 
    //
    bool	noDXHelp;

    char*      cryptKey;       // Key used to decrypt the .net and .cfg files
    bool     forceNetFileEncryption; // Do we force encryption 
    char*      forceFunctionalLicense; // If non-null, 
					// force the given license type 
    //Pixel	errorNodeForeground;
    //Pixel	executionHighlightForeground;
    //Pixel	backgroundExecutionForeground;
    //Pixel	foreground;
    //Pixel	background;
    //Pixel       insensitiveColor;
    //Pixel       accentColor;
    //Pixel       standInBackground; // This one is shared.

    int		applicationPort;
    char*	applicationHost;

    char*	oemApplicationName;	// Allow alternate app name if verified 
    char* 	oemApplicationNameCode;	// Crypted app name for verification
    char* 	oemLicenseCode;		// Used to not require a license 

    char*	viewDataFile;		// Data file to use in viewer mode. 

    bool 	autoScrollVPEInitVal;	// set to false by default, provides an
					// initial value to EditorWorkSpace for
					// repositioning scrollbars during page changes.
    char*	cosmoDir;		// On behalf of java generation
    char*	jdkDir;
    char*	htmlDir;
    char*	dxJarFile;
    char*	userHtmlDir;
    char*	serverDir;

    //
    // Automatic graph layout
    //
    int		autoLayoutHeight;
    int		autoLayoutGroupSpacing;
    int		autoLayoutNodeSpacing;
} DXResource;


//
// Referenced classes:
//
class Dictionary;
class DXWindow;
class Command;
class CommandScope;
class DXChild;
class DXPacketIF;
class ApplicIF;
class Network;
class StartServerDialog;
class LoadMacroDialog;
class LoadMDFDialog;
class OpenNetworkDialog;
class MsgWin;
class DebugWin;
class HelpWin;
class ProcessGroupAssignDialog;
class ProcessGroupManager;
class EditorWindow;

struct DXServerInfo
{
    int 	autoStart;
    char       *server;
    char       *executive;
    char       *workingDirectory;
    char       *userModules; 	// -mdf option
    char       *executiveFlags; // Other flags, as required, for dxexec.
    int		port;
    int		memorySize;

    List    	children;
    List	queuedPackets;
    DXPacketIF *packet;
};

typedef int WindowPlacementPolicyEnum;

//
// DXApplication class definition:
//				
class DXApplication : public IBMApplication
{
    friend class DXExecCtl;
    friend class DXPacketIF;
    friend class DXLinkHandler;

  private:
    //
    // Private class data:
    //
    static bool    DXApplicationClassInitialized; // class initialized?
    static void 	DebugEchoCallback(void *clientData, char *echoString);
    static void       QueuedPacketAccept(void *data);
    static void       QueuedPacketCancel(void *data);
    
    static void InitializeSignals();
    friend void
#if defined(ALTERNATE_CXX_SIGNAL) 
    DXApplication_HandleCoreDump(int dummy, ... );
#else
    DXApplication_HandleCoreDump(int dummy);
#endif

    //
    // License manager stuff
    //
    static void       LicenseMessage(void *, int, void *);

    //
    // Dumped object list.
    //
    List	dumpedObjects;
    
    //
    // Should we do a disconnect from the executive next time through the 
    // handleEvents.
    //
    bool 	serverDisconnectScheduled;

    //
    // Private member data:
    //
    bool runApplication;	// continue to run the application?

    //
    // Define a mapping of integer levels and the restriction level names and
    // determine if the current restriction level is at the given level.
    // The highest level of restriction is 1 the lowest and +infinity.
    //
    bool isRestrictionLevel(int level);

    //
    // Called if DIAGNOSTICS is defined
    //
    //friend int DXApplication_DXAfterFunction(Display *display);

    //
    // Have we read the first network yet.
    //
    bool readFirstNetwork;

    //
    // Save all dirty files and return a message string
    //
    void emergencySave (char *msg);

    //
    // Check the oemApplicationName and oemApplicationNameCode resources and see
    // if an alternate application name can be verified.  If so, return it
    // otherwise return NULL.  The return value of the effects the return
    // values of getFormalName() and getInformalName().
    //
    const char *getOEMApplicationName();

    //
    // See if there is an OEM license code (see oemApplicationName and
    // oemLicenseCode resources) and if so see if it is valid.
    // If so return true and the type of functional license (rt/dev) that
    // was granted to the oem.
    //
    bool verifyOEMLicenseCode(LicenseTypeEnum *);

#if defined(BETA_VERSION) && defined(NOTDEF)
    //
    // Exit if this is a beta version and its old
    //
    void betaTimeoutCheck();
#endif

  protected:
    //
    // Protected class data:
    //
    static DXResource resource;	// resources and options

    static char* ListValuedSettings[];

    //
    // Protected member data:
    //
    DXWindow	       *anchor;		// anchor window
    CommandScope       *commandScope;	// command scope
    DXServerInfo	serverInfo;
    DXExecCtl		execCtl;
#ifdef HAS_CLIPNOTIFY_EXTENSION
    bool		hasClipnotifyExtension;
    int			clipnotifyEventCode;
#endif

	dxui::FileDialog         *openFileDialog;

    ApplicIF	       *applicationPacket;

    //
    // Overrides the Application class version:
    //   Initializes Xt Intrinsics with option list (switches).
    //
    virtual bool initialize(unsigned int* argcp,
			    char**        argv);

    //
    // Override of superclass handleEvents() function:
    //   Handles application events.
    //   This routine should be called by main() only.
    //
    virtual void handleEvents();
    //virtual void handleEvent(XEvent *xev);

    //
    // If we're using an anchor window with its own copyright then be satisfied
    // with that.  Otherwise use the superclass method.
    virtual void postCopyrightNotice();

    void highlightNodes(char* path, int highlightType);

    StartServerDialog 	*startServerDialog;
    OpenNetworkDialog	*openNetworkDialog;
    LoadMacroDialog	*loadMacroDialog;
    LoadMDFDialog	*loadMDFDialog;
    MsgWin		*messageWindow;

    LicenseTypeEnum	appLicenseType;		// nodelocked or concurrent
    LicenseTypeEnum	funcLicenseType;	// run-time or development

    //
    // The list of errors for the current (or most recent) execution.
    List errorList;

    //
    // Read the module description file into the Node Definition Dictionary.
    //
    virtual void loadMDF();
    //
    // Read the interactor description file into the Node Definition Dictionary.
    //
    virtual void loadIDF();

    //
    // Destroy the objects that have been dumped.
    //
    void destroyDumpedObjects();

    virtual void clearErrorList(void);
    virtual void addErrorList(char *line);

    //
    // Manage the software licenses 
    //
    virtual void determineUILicense(LicenseTypeEnum *appLicense,
				    LicenseTypeEnum *funcLicense);

    virtual bool	    verifyServerLicense();

    //
    // Disconnect from Exec next time through the main loop
    //
    void		scheduleServerDisconnect();

    //
    // Send the command to the flush the dictionaries.
    //
    virtual void flushExecutiveDictionaries(DXPacketIF *pif);

    //
    // Handle cancelation of (disconnection from) a packet interface. 
    //
    virtual void packetIFCancel(DXPacketIF *p);
    //
    // Handle acceptance of (connection to) a packet interface. 
    //
    virtual void packetIFAccept(DXPacketIF *p);

    //
    //  Get the functional license that was asked for by the user.
    //
    LicenseTypeEnum getForcedFunctionalLicenseEnum();

    //
    // Install the default resources for this class and then call the
    // same super class method to get the default resources from the
    // super classes.
    //
    //virtual void installDefaultResources(Widget baseWidget);

	void getResources();

  public:
    //
    // Public static data:
    //
    static Symbol MsgExecute;
    static Symbol MsgStandBy;
    static Symbol MsgExecuteDone;
    static Symbol MsgServerDisconnected;
    static Symbol MsgPanelChanged;

    //
    // The input pointer is a pointer to an Application. 
    //
#if 0
    static void       ShutdownApplication(void *);
#endif

    //
    // Public member data:
    //
    Network	       *network;	// Main network
    List		macroList;	// list of user macros 
    Command*		quitCmd;	// DX application Quit command
    Command*            exitCmd;        // DX application Quit command with
                                        // checking if macros modified
    Command*		openFileCmd;	
    Command*		loadMacroCmd;	
    Command*		executeOnceCmd;
    Command*		executeOnChangeCmd;
    Command*		endExecutionCmd;
    Command*		connectedToServerCmd;
    Command*		disconnectedFromServerCmd;
    Command*		connectToServerCmd;
    Command*		resetServerCmd;
    Command*		disconnectFromServerCmd;
    Command*            messageWindowCmd;
    Command*            openSequencerCmd;
    Command*            openAllColormapCmd;
    Command*		assignProcessGroupCmd;


    //
    // Used to do autoactivation/deactivation of commands that register
    // themselves with this command.
    //
    Command*		executingCmd;
    Command*		notExecutingCmd;

#if USE_REMAP	
    Command*            toggleRemapInteractorsCmd;
#endif
    Command*            loadMDFCmd;
    Command*            toggleInfoEnable;
    Command*            toggleWarningEnable;
    Command*            toggleErrorEnable;

#if !defined(WORKSPACE_PAGES)
    ProcessGroupManager *PGManager;
#endif

    ProcessGroupAssignDialog *processGroupAssignDialog;

    //
    // Constructor:
    //
    DXApplication(char* className);

    //
    // Destructor:
    //
    ~DXApplication();

    void notifyPanelChanged();

    //
    // Add dumped object to the list so as to delete it later.
    //
    void dumpObject(Base *object);

    //
    // return the CommandScope.
    //
    CommandScope *getCommandScope() { return this->commandScope; }

    //
    // Access routines:
    //
    DXWindow* getAnchor()
    {
	return this->anchor;
    }
    void shutdownApplication(); 

    //
    // Functions to manage the server connection.
    int connectToServer(int port, DXChild *c = NULL);
    bool disconnectFromServer();
    void closeConnection(DXChild *c);
    void completeConnection(DXChild *c);
    DXChild *startServer();
    void setServer(char *server);

    DXPacketIF *getPacketIF() { return this->serverInfo.packet; }
    DXExecCtl  *getExecCtl()  { return &this->execCtl; }

    virtual bool openFile(const char *netfile, 
				const char *cfgfile = NULL,
				bool resetTheServer = true);

    virtual bool saveFile(const char *netfile, 
				bool force = false);

    virtual bool resetServer(void);
    bool postStartServerDialog();
    void postProcessGroupAssignDialog();
    void postOpenNetworkDialog();
    void postLoadMDFDialog();
    void postLoadMacroDialog();
    void getServerParameters(int 	 *autoStart,
			     const char **server,
			     const char **executive,
			     const char **workingDirectory,
			     const char **executiveFlags,
			     int	 *port,
			     int	 *memorySize);
    void setServerParameters(int 	 autoStart,
			     const char *server,
			     const char *executive,
			     const char *workingDirectory,
			     const char *executiveFlags,
			     int	 port,
			     int	 memorySize);
    //
    // Functions to manage the application connection
    //
    virtual void connectToApplication(const char *host, const int port);
    virtual void disconnectFromApplication(bool terminate);

    //
    // Pre-allocate required ui colors
    //
    //const char* *DXAllocateColors(XtResource*, int);

 //   Pixel getAccentColor()
 //   {
	//return this->resource.accentColor;
 //   }
 //   Pixel getStandInBackground()
 //   {
	//return this->resource.standInBackground;
 //   }
 //   Pixel getErrorNodeForeground()
 //   {
	//return this->resource.errorNodeForeground;
 //   }
 //   Pixel getExecutionHighlightForeground()
 //   {
	//return this->resource.executionHighlightForeground;
 //   }
 //   Pixel getBackgroundExecutionForeground()
 //   {
	//return this->resource.backgroundExecutionForeground;
 //   }
 //   Pixel getForeground()
 //   {
	//return this->resource.foreground;
 //   }
 //   Pixel getInsensitiveColor()
 //   {
 //       return this->resource.insensitiveColor;
 //   }
    bool inDebugMode() { return this->resource.debugMode; }

    //
    // I added trace on/off buttons to the msgwin and I want to be able to see
    // the instance numbers in the vpe conditionally as well.
    //
    bool showInstanceNumbers() 
	{ return (this->resource.debugMode || this->resource.showInstanceNumbers); }
    void showInstanceNumbers(bool on_or_off);

    bool inEditMode();
    bool inImageMode();
    bool inMenuBarMode();

    bool inDataViewerMode();		// Object viewer, requires ui/viewer.net
    const char *getDataViewerImportFile();  // Data file to view	

    bool isMetricUnits()
    {
	return this->resource.isMetric;
    }

    MsgWin *getMessageWindow()
    {
	return this->messageWindow;
    }
    const char *getLimitedNetPath()
    {
	return this->resource.netPath;
    }

    //
    // Get the default image printing/saving options specified through
    // command line options or resources.
    //
    char*      getPrintImageFormat();
    char*      getPrintImageSize();
    char*      getPrintImagePageSize();
    int         getPrintImageResolution();
    char*      getPrintImageCommand();
    char*      getSaveImageFormat();
    char*      getSaveImageSize();
    char*      getSaveImagePageSize();
    int         getSaveImageResolution();

    //
    // Create a new network editor.  
    // This particular implementation makes the returned editor an anchor
    // if this->anchor is NULL.
    // This may return NULL in which case a message dialog is posted. 
    //
	virtual EditorWindow * newNetworkEditor(Network *n);

    virtual Network *newNetwork(bool nonJava=false);
    virtual MsgWin *newMsgWin();
    virtual ImageWindow *newImageWindow(Network *n);
    virtual ControlPanel *newControlPanel(Network *n);



    //
    // Mark all the networks owned by this application as dirty.
    //
    void markNetworksDirty(void);

    bool	isInfoEnabled();
    bool	isWarningEnabled();
    bool	isErrorEnabled();
    bool	doesInfoOpenMessage(bool fromModule = false);
    bool	doesWarningOpenMessage();
    bool	doesErrorOpenMessage();
    int 	doesErrorOpenVpe(Network*);
    void	enableInfo(bool enable);
    void	enableWarning(bool enable);
    void	enableError(bool enable);

    //
    // constants returned by doesErrorOpenVpe()
    //
    enum {
	DontOpenVpe = 0,
	MayOpenVpe  = 1,
	MustOpenVpe = 2
    };

    //
    // Read the user's description file into the Node Definition Dictionary.
    // If dict is not null then fill the given dictionary with the 
    // NodeDefintions found in the given MDF. 
    // If uiLoadedOnly is true, then the user has asked to have these loaded
    // from somewhere other than the command line (in which case the 
    // exec does not know about them yet).
    //
    virtual void loadUDF(const char *fileName, Dictionary *dict = NULL,
				bool uiLoadedOnly = false);

    //
    // Get selected NodeDefinitoins from the newdefs dictionary and send 
    // their representative MDF specs to the server if they are
    // 	1) outboard 
    // 	2) dynamically loaded 
    // 	3) outboardness or dynmacity changes compared to the possibly 
    //	    existing definition in the current dictionary if provided. 
    //
    void sendNewMDFToServer(Dictionary *newdefs, Dictionary *current = NULL);

    //
    // Define a set of methods that indicate a level of UI capability. 
    //
    virtual bool appAllowsDXHelp();
    virtual bool appSuppressesStartupWindows();
    virtual bool appLimitsNetFileSelection();

    virtual bool appAllowsPanelEdit();
    virtual bool appAllowsRWConfig();
    virtual bool appAllowsPanelAccess();
    virtual bool appAllowsOpenAllPanels();
    virtual bool appAllowsPanelOptions();

    virtual bool appAllowsInteractorEdits();
    virtual bool appAllowsInteractorSelection();
    virtual bool appAllowsInteractorMovement();
    virtual bool appAllowsInteractorAttributeChange();

    virtual bool appAllowsImageRWNetFile();
    virtual bool appAllowsSavingNetFile(Network *n = NULL);
    virtual bool appAllowsSavingCfgFile();
    virtual bool appAllowsImageLoad();
    virtual bool appAllowsImageSaving();
    virtual bool appAllowsImagePrinting();
    virtual bool appLimitsImageOptions();

    virtual bool appAllowsEditorAccess();
    virtual bool appAllowsPGroupAssignmentChange();

    virtual bool appAllowsMessageInfoOption();
    virtual bool appAllowsMessageWarningOption();
    virtual bool appAllowsScriptCommands();
    
    virtual bool appAllowsCMapSetName();
    virtual bool appAllowsCMapOpenMap();
    virtual bool appAllowsCMapSaveMap();
    virtual bool appForcesNetFileEncryption();
    bool appAllowsExitOptions();
    bool appAllowsExecuteMenus();
    bool appAllowsConnectionMenus();
    bool appAllowsWindowsMenus();
    bool appAllowsImageMenus();
    bool appAllowsConfirmedQuit();

    bool dxlAppNotifySaveNet()
    { return DXApplication::resource.notifySaveNet; }

    bool dxlAppNoNetworkExecute()
    { return DXApplication::resource.noNetworkExecute; }





    //
    // Return the name of the application (i.e. 'Data Explorer',
    // 'Data Prompter', 'Medical Visualizer'...).
    //
    virtual const char *getInformalName();

    //
    // Return the formal name of the application (i.e. 
    // 'Open Visualization Data Explorer', 'Open Visualization Data Prompter'...)
    //
    virtual const char *getFormalName();

    //
    // Get the applications copyright notice, for example...
    // "Copyright International Business Machines Corporation 1991-1993
    // All rights reserved"
    //
    virtual const char *getCopyrightNotice();

    //
    // Go through the error list and highlight all nodes that got errors.
    //
    void refreshErrorIndicators();

    virtual bool printComment(FILE *f);
    virtual bool parseComment(const char *line, const char *filename, 
					int lineno);

    //
    // Return true if the DXWindows are supposed to use the window placement
    // information saved in the .net or .cfg files.
    //
    virtual bool applyWindowPlacements();

    virtual const char* getCryptKey() { return this->resource.cryptKey; }

    const char* getCosmoDir() { return this->resource.cosmoDir; }
    const char* getJdkDir() { return this->resource.jdkDir; }
    const char* getHtmlDir() { return this->resource.htmlDir; }
    const char* getServerDir() { return this->resource.serverDir; }
    const char* getDxJarFile() { return this->resource.dxJarFile; }
    const char* getUserHtmlDir() { return this->resource.userHtmlDir; }

    //
    // Should we force the functional license to be that returned by
    // getForcedFunctionalLicenseEnum(). 
    //
    virtual bool isFunctionalLicenseForced();

    //
    // Get the functional license that was granted.
    //
    LicenseTypeEnum getFunctionalLicenseEnum();

    //
    // Do an emergencySave() and then call the super class method 
    //
    virtual void abortApplication();

    bool getAutoScrollInitialValue() { return this->resource.autoScrollVPEInitVal; }

#if WORKSPACE_PAGES
    ProcessGroupManager *getProcessGroupManager();
#endif

    ApplicIF            *getAppConnection() { return this->applicationPacket; }

    void appendReferencedFile (const char* file);
    void removeReferencedFile (const char* file);
    void getRecentNets(List& result);


    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassDXApplication;
    }
};


extern DXApplication* theDXApplication;

#endif /*  _DXApplication_h */
