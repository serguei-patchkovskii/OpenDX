/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

using namespace System::Windows::Forms;

#include <stdio.h>

//
//
//
#include <errno.h> // for errno
#include <fcntl.h> // for stat
#include <ctype.h> // for tolower

#if defined(HAVE_UNISTD_H)
#include <unistd.h>
#endif

#if defined(HAVE_SYS_STAT_H)
#include <sys/stat.h>
#endif


#include "Application.h"
#include "Client.h"
#include "Command.h"
#include "DXStrings.h"
#include "TimedMessage.h"
#include "ResourceManager.h"
#include "XmlPreferences.h"

BaseApp* theApplication = NUL(BaseApp*);


bool BaseApp::ApplicationClassInitialized = false;
//Cursor  Application::BusyCursor                  = NUL(Cursor);


Symbol BaseApp::MsgCreate        = NUL(Symbol);
Symbol BaseApp::MsgManage        = NUL(Symbol);
Symbol BaseApp::MsgUnmanage      = NUL(Symbol);
Symbol BaseApp::MsgSetBusyCursor = NUL(Symbol);
Symbol BaseApp::MsgResetCursor   = NUL(Symbol);

Symbol BaseApp::MsgManageByLeafClassName   = NUL(Symbol);
Symbol BaseApp::MsgUnmanageByLeafClassName = NUL(Symbol);
Symbol BaseApp::MsgManageByTitle 		= NUL(Symbol);
Symbol BaseApp::MsgUnmanageByTitle 		= NUL(Symbol);

//
// This is used by the ASSERT macro in defines.h
// It should NOT be an Application method, because otherwise
// it requires that defines.h include Application.h.
//
extern "C" void AssertionFailure(const char *file, int line)
{
    fprintf(stderr,"Internal error detected at \"%s\":%d.\n",
		file, line);
    if (theApplication)
	theApplication->abortApplication();
    else
	abort();
}

BaseApp::BaseApp(char* className): UIComponent(className)
{
    ASSERT(className);

    //
    // Perform class initializtion, if necessary.
    //
    if (NOT BaseApp::ApplicationClassInitialized)
    {
	ASSERT(theSymbolManager);

	BaseApp::MsgCreate =
	    theSymbolManager->registerSymbol("Create");
	BaseApp::MsgManage =
	    theSymbolManager->registerSymbol("Manage");
	BaseApp::MsgUnmanage =
	    theSymbolManager->registerSymbol("Unmanage");
	BaseApp::MsgSetBusyCursor =
	    theSymbolManager->registerSymbol("SetBusyCursor");
	BaseApp::MsgResetCursor =
	    theSymbolManager->registerSymbol("ResetCursor");
	BaseApp::MsgManageByLeafClassName   = 
	    theSymbolManager->registerSymbol("ManageByLeafClassName");
	BaseApp::MsgUnmanageByLeafClassName = 
	    theSymbolManager->registerSymbol("UnmanageByLeafClassName");
	BaseApp::MsgManageByTitle = 
	    theSymbolManager->registerSymbol("ManageByTitle");
	BaseApp::MsgUnmanageByTitle= 
	    theSymbolManager->registerSymbol("UnmanageByTitle");

	BaseApp::ApplicationClassInitialized = true;
    }

    //
    // Set the global Application pointer.
    //
    theApplication = this;

    //
    // Initialize member data.
    //
    this->busyCursors	     = 0; 
//    this->display            = NUL(Display*);
//    this->applicationContext = NUL(XtAppContext);

    this->applicationClass   = DuplicateString(className);
    this->show_bubbles 	     = false;
//    this->help_viewer	     = NUL(Widget);
}


BaseApp::~BaseApp()
{
	if(this->applicationClass)
		delete[] this->applicationClass;
	applicationContext = NULL;
    theApplication = NULL;
}

//
// Install the default resources for this class.
//
//void Application::installDefaultResources(Widget baseWidget)
//{
//    //this->setDefaultResources(baseWidget, Application::DefaultResources);
//}

bool BaseApp::initializeWindowSystem(unsigned int *argcp, char **argv) 
{
    //
    // Install error and warning handlers.
    //
    //XtSetWarningHandler((XtErrorHandler)Application_XtWarningHandler);
    //XSetErrorHandler(Application_XErrorHandler);

	applicationContext = new System::Windows::Forms::ApplicationContext();

    return true;
}

void BaseApp::parseCommand(unsigned int* argcp, char** argv)
{
	char res_file[512] = "";
	char **newargv = NULL;
	unsigned int newargc=1;
	newargv = new char*[*argcp];
	newargv[0] = new char[strlen(argv[0])+1];
	strcpy(newargv[0], argv[0]); //Executable name

	// Open the defaults file first.
	if (this->getApplicationDefaultsFileName(res_file, false)) {
		if(!theXmlPreferences->readPrefs(res_file)) {
			printf("Preference File Corrupted. Please delete and restart!\n");
			exit(1);
		}
	} else
		theXmlPreferences->createPrefs();

	// What have we got for command line parsing? 
	// Parse command line and call setValue on XmlPreferences.

#define NOARGtrue(a,b) else if(strcmp(argv[i], a)==0) \
	theXmlPreferences->setPref(b, XmlPreferences::PrefType::TypeBool, "true")
#define NOARGfalse(a,b) else if(strcmp(argv[i], a)==0) \
	theXmlPreferences->setPref(b, XmlPreferences::PrefType::TypeBool, "false")
#define NOARGSTR(a,b,c) else if(strcmp(argv[i], a)==0) \
	theXmlPreferences->setPref(b, XmlPreferences::PrefType::TypeString, c)
#define ARGSTR(a, b) else if(strcmp(argv[i], a)==0) { \
		if(i+1 == *argcp || argv[i+1][0] == '-') { \
			printf("Missing argument for %s\n", argv[i]); \
			exit(1); \
		} \
		theXmlPreferences->setPref(b, XmlPreferences::PrefType::TypeString, argv[i+1]); \
		i++; \
	}

	unsigned int i = 1;
	while(i < *argcp) {
		if(0) {}
		NOARGtrue("-wizard", "wizard");
		NOARGSTR("-edit", "anchorMode", "EDIT");
		NOARGtrue("-execute", "executeProgram");
		NOARGtrue("-execute_on_change", "executeOnChange");
		NOARGtrue("-help", "printHelpMessage");
		NOARGSTR("-image", "anchorMode", "IMAGE");
		NOARGSTR("-kiosk", "anchorMode", "MENUBAR");
		NOARGSTR("-menubar", "anchorMode", "MENUBAR");
		NOARGtrue("-noAnchorAtStartup", "noAnchorAtStartup");
		NOARGtrue("-noConfirmedQuit", "noConfirmedQuit");
		NOARGtrue("-local", "runLocally");
		NOARGtrue("-metric", "metric");
		NOARGtrue("-suppress", "suppressStartupWindows");
		NOARGtrue("-uidebug", "debugMode");
		NOARGtrue("-showInstanceNumbers", "showInstanceNumbers");
		NOARGtrue("-uionly", "runUIOnly");
		NOARGtrue("-version", "DXVersion");
		//Backdoor Switches
		NOARGtrue("-noDXHelp", "noDXHelp");
		NOARGtrue("-noEditorAccess", "noEditorAccess");
		NOARGtrue("-notifySaveNet", "notifySaveNet");
		NOARGtrue("-noNetworkExecute", "noNetworkExecute");
		NOARGtrue("-noImageRWNetFile", "noImageRWNetFile");
		NOARGtrue("-noImageLoad", "noImageLoad");
		NOARGtrue("-limitImageOptions", "limitImageOptions");
		NOARGtrue("-limitedNetFileSelection", "limitedNetFileSelection");
		NOARGtrue("-noNetFileSelection", "noNetFileSelection");
		NOARGtrue("-noImageSaving", "noImageSaving");
		NOARGtrue("-noImagePrinting", "noImagePrinting");
		NOARGtrue("-noInteractorEdits", "noInteractorEdits");
		NOARGtrue("-noInteractorAttributes", "noInteractorAttributes");
		NOARGtrue("-noInteractorMovement", "noInteractorMovement");
		NOARGtrue("-noOpenAllPanels", "noOpenAllPanels");
		NOARGtrue("-noPanelAccess", "noPanelAccess");
		NOARGtrue("-noPanelOptions", "noPanelOptions");
		NOARGtrue("-noPanelEdit", "noPanelEdit");
		NOARGtrue("-noRWConfig", "noRWConfig");
		NOARGtrue("-noScriptCommands", "noScriptCommands");
		NOARGtrue("-noMessageInfoOption", "noMessageInfoOption");
		NOARGtrue("-noMessageWarningOption", "noMessageWarningOption");
		NOARGtrue("-noEditorOnError", "noEditorOnError");
		NOARGtrue("-noCMapSetNameOption", "noCMapSetNameOption");
		NOARGtrue("-noCMapSaveMap", "noCMapSaveMap");
		NOARGtrue("-noWindowPlacement", "noWindowPlacement");
		NOARGtrue("-noCMapOpenMap", "noCMapOpenMap");
		NOARGtrue("-noPGroupAssignment", "noPGroupAssignment");
		NOARGtrue("-warning", "warningEnabled");
		NOARGtrue("-info", "infoEnabled");
		NOARGtrue("-error", "errorEnabled");
		NOARGtrue("-exitAfter", "exitAfter");
		NOARGtrue("-noExecuteMenus", "noExecuteMenus"); 
		NOARGtrue("-noConnectionMenus", "noConnectionMenus");
		NOARGtrue("-noWindowsMenus", "noWindowsMenus");
		NOARGtrue("-noExitOptions", "noExitOptions");
		NOARGtrue("-noImageMenus", "noImageMenus");
		NOARGfalse("-noAutoScrollVPE", "noAutoScrollVPE"); 

		// Regular Args
		ARGSTR("-uiroot", "UIRoot")
		ARGSTR("-dismissedWizards", "dismissedWizards")
		ARGSTR("-exec", "executive")
		ARGSTR("-directory", "directory")
		ARGSTR("-memory", "memory")
		ARGSTR("-host", "host")
		ARGSTR("-macros", "macros")
		ARGSTR("-mdf", "userModuleDescriptionFile")
		ARGSTR("-dxmdf", "executiveModuleDescriptionFile")
		ARGSTR("-uimdf", "uiModuleDescriptionFile")
		ARGSTR("-port", "port")
		ARGSTR("-printImageFormat", "printImageFormat")
		ARGSTR("-printImagePageSize", "printImagePageSize")
		ARGSTR("-printImageSize", "printImageSize")
		ARGSTR("-printImageResolution", "printImageResolution")
		ARGSTR("-program", "program")
		ARGSTR("-cfg", "cfg")
		ARGSTR("-saveImageFormat", "saveImageFormat")
		ARGSTR("-saveImagePageSize", "saveImagePageSize")
		ARGSTR("-saveImageSize", "saveImageSize")
		ARGSTR("-saveImageResolution", "saveImageResolution")
		ARGSTR("-uimessages", "messages")
		// Backdoor Switches
		ARGSTR("-restrictionLevel", "restrictionLevel")
		ARGSTR("-appHost", "applicationHost")
		ARGSTR("-appPort", "applicationPort")
		ARGSTR("-netPath", "netPath")
		ARGSTR("-forceNetFileEncryption", "forceNetFileEncryption")
		ARGSTR("-cryptKey", "cryptKey")
		ARGSTR("-forceLicense", "forceLicense")
		ARGSTR("-view", "viewDataFile")
		ARGSTR("-autoLayoutHeight", "autoLayoutHeight")
		ARGSTR("-autoLayoutGroupSpacing", "autoLayoutGroupSpacing")
		ARGSTR("-autoLayoutNodeSpacing", "autoLayoutNodeSpacing")
		else {
			//Not found so copy to new argv and increment newargc
			newargv[newargc] = new char[strlen(argv[i])+1];
			strcpy(newargv[newargc], argv[i]);
			newargc++;
		}

		i++;
	}

	*argcp = newargc;
	argv = newargv;

	// Now go through the default parameters and set them if not already set.

	theXmlPreferences->setDefault("standInBackground", XmlPreferences::PrefType::TypeString, "#5F9EA0");
	theXmlPreferences->setDefault("executionHighlightForeground", XmlPreferences::PrefType::TypeString, "#00ff7e");
	theXmlPreferences->setDefault("backgroundExecutionForeground", XmlPreferences::PrefType::TypeString, "#7e7eb4");
	theXmlPreferences->setDefault("errorHighlightForeground", XmlPreferences::PrefType::TypeString, "#ff9b00");
	theXmlPreferences->setDefault("foreground", XmlPreferences::PrefType::TypeString, "Black");
	theXmlPreferences->setDefault("background", XmlPreferences::PrefType::TypeString, "#b4b4b4");
	theXmlPreferences->setDefault("InsensitiveColor", XmlPreferences::PrefType::TypeString, "#888888");	
	theXmlPreferences->setDefault("anchorMode", XmlPreferences::PrefType::TypeString, "EDIT");
	theXmlPreferences->setDefault("DXVersion", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("debugMode", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("showInstanceNumbers", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("directory", XmlPreferences::PrefType::TypeString, "");
	theXmlPreferences->setDefault("executive", XmlPreferences::PrefType::TypeString, "");
	theXmlPreferences->setDefault("executeProgram", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("executeOnChange", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("printHelpMessage", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("host", XmlPreferences::PrefType::TypeString, "");
	theXmlPreferences->setDefault("noAnchorAtStartup", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("noConfirmedQuit", XmlPreferences::PrefType::TypeBool, "false");


	theXmlPreferences->setDefault("memory", XmlPreferences::PrefType::TypeInt, "0");
	theXmlPreferences->setDefault("metric", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("messages", XmlPreferences::PrefType::TypeString, "");
	theXmlPreferences->setDefault("port", XmlPreferences::PrefType::TypeInt, "0");
	theXmlPreferences->setDefault("printImageCommand", XmlPreferences::PrefType::TypeString, "lpr");
	theXmlPreferences->setDefault("printImageFormat", XmlPreferences::PrefType::TypeString, "TIFF");
	theXmlPreferences->setDefault("printImagePageSize", XmlPreferences::PrefType::TypeString, "");
	theXmlPreferences->setDefault("printImageSize", XmlPreferences::PrefType::TypeString, "");
	theXmlPreferences->setDefault("printImageResolution", XmlPreferences::PrefType::TypeInt, "0");
	theXmlPreferences->setDefault("program", XmlPreferences::PrefType::TypeString, "");
	theXmlPreferences->setDefault("cfg", XmlPreferences::PrefType::TypeString, "");
	theXmlPreferences->setDefault("runLocally", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("runUIOnly", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("saveImageFormat", XmlPreferences::PrefType::TypeString, "");
	theXmlPreferences->setDefault("saveImagePageSize", XmlPreferences::PrefType::TypeString, "");
	theXmlPreferences->setDefault("saveImageSize", XmlPreferences::PrefType::TypeString, "");
	theXmlPreferences->setDefault("saveImageResolution", XmlPreferences::PrefType::TypeInt, "0");
	theXmlPreferences->setDefault("suppressStartupWindows", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("userModuleDescriptionFile", XmlPreferences::PrefType::TypeString, "");
	theXmlPreferences->setDefault("executiveModuleDescriptionFile", XmlPreferences::PrefType::TypeString, "");
	theXmlPreferences->setDefault("uiModuleDescriptionFile", XmlPreferences::PrefType::TypeString, "");
	theXmlPreferences->setDefault("noWindowPlacement", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("restrictionLevel", XmlPreferences::PrefType::TypeString, "");
	theXmlPreferences->setDefault("noRWConfig", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("noPanelEdit", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("noInteractorEdits", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("noInteractorAttributes", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("noInteractorMovement", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("noOpenAllPanels", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("noPanelAccess", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("noPanelOptions", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("noMessageInfoOption", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("noMessageWarningOption", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("noEditorOnError", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("noScriptCommands", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("noPGroupAssignment", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("noImageRWNetFile", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("limitedNetFileSelection", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("netPath", XmlPreferences::PrefType::TypeString, "");
	theXmlPreferences->setDefault("noImageLoad", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("noImageSaving", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("noImagePrinting", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("limitImageOptions", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("notifySaveNet", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("noNetworkExecute", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("noEditorAccess", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("noDXHelp", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("noCMapSetNameOption", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("noCMapOpenMap", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("noCMapSaveMap", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("applicationPort", XmlPreferences::PrefType::TypeInt, "0");
	theXmlPreferences->setDefault("applicationHost", XmlPreferences::PrefType::TypeString, "");
	theXmlPreferences->setDefault("infoEnabled", XmlPreferences::PrefType::TypeBool, "true");
	theXmlPreferences->setDefault("warningEnabled", XmlPreferences::PrefType::TypeBool, "true");
	theXmlPreferences->setDefault("errorEnabled", XmlPreferences::PrefType::TypeBool, "true");
	theXmlPreferences->setDefault("moduleInfoOpensMessage", XmlPreferences::PrefType::TypeBool, "true");
	theXmlPreferences->setDefault("infoOpenMessage", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("warningOpenMessage", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("errorOpenMessage", XmlPreferences::PrefType::TypeBool, "true");
	theXmlPreferences->setDefault("useWindowSpecs", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("forceNetFileEncryption", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("cryptKey", XmlPreferences::PrefType::TypeString, "");
	theXmlPreferences->setDefault("exitAfter", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("forceLicense", XmlPreferences::PrefType::TypeString, "");
	theXmlPreferences->setDefault("noExecuteMenus", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("noConnectionMenus", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("noWindowsMenus", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("noExitOptions", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("noImageMenus", XmlPreferences::PrefType::TypeBool, "false");
	theXmlPreferences->setDefault("oemApplicationName", XmlPreferences::PrefType::TypeString, "");
	theXmlPreferences->setDefault("oemApplicationNameCode", XmlPreferences::PrefType::TypeString, "");
	theXmlPreferences->setDefault("oemLicenseCode", XmlPreferences::PrefType::TypeString, "");
	theXmlPreferences->setDefault("viewDataFile", XmlPreferences::PrefType::TypeString, "");
	theXmlPreferences->setDefault("autoScrollVPE", XmlPreferences::PrefType::TypeBool, "true");
	theXmlPreferences->setDefault("autoLayoutHeight", XmlPreferences::PrefType::TypeInt, "0");
	theXmlPreferences->setDefault("autoLayoutGroupSpacing", XmlPreferences::PrefType::TypeInt, "0");
	theXmlPreferences->setDefault("autoLayoutNodeSpacing", XmlPreferences::PrefType::TypeInt, "0");
	theXmlPreferences->setDefault("cosmoDir", XmlPreferences::PrefType::TypeString, "");
	theXmlPreferences->setDefault("jdkDir", XmlPreferences::PrefType::TypeString, "");
	theXmlPreferences->setDefault("htmlDir", XmlPreferences::PrefType::TypeString, "");
	theXmlPreferences->setDefault("serverDir", XmlPreferences::PrefType::TypeString, "");
	theXmlPreferences->setDefault("dxJarFile", XmlPreferences::PrefType::TypeString, "");
	theXmlPreferences->setDefault("userHtmlDir", XmlPreferences::PrefType::TypeString, "");

	// The following is a little different. The default should actually be dxroot/samples/macros
	// Set it in DXApplication if null.
	theXmlPreferences->setDefault("macros", XmlPreferences::PrefType::TypeString, "");


	// Now setup the preferences in DXResource*

	// theXmlPreferences->writePrefs(res_file);

//    char res_file[256];
    //XrmDatabase resourceDatabase = 0;
    //
    // if the file exists, use it, but don't create an empty file.
    //
	//resourceDatabase = XrmGetFileDatabase(res_file);

    //
    // XrmParseCommand is spec'd to accept NULL in the resourceDatabase argument.
    //
    //char *appname = GetFileBaseName(argv[0],NULL);
    //XrmParseCommand(&resourceDatabase, optlist, optlistsize, 
	   //               appname, (int *)argcp, argv);
    //delete[] appname;

    //
    // Merge the resources into the Xt database with highest precedence.
    //
//    if (resourceDatabase)
//    {
//	//
//	// display->db overrides contents of resourceDatabase.
//	// O'Reilly, R5 prog. supplement, pg. 127
//	//
//#if defined XlibSpecificationRelease && XlibSpecificationRelease > 4
//        XrmDatabase db = XrmGetDatabase(display);
//        XrmCombineDatabase(resourceDatabase, &db, True);
//#else
//	
//	XrmMergeDatabases(resourceDatabase, &(display->db));
//#endif
//    }
//
    //
    // It's seems as though a call to XrmDestroyDatabase(resourceDatabase)
    // is in order here.  A quick reading of the doc doesn't explain to
    // me why that's wrong.  If I add the call however, there will be
    // a crash.
    //
}

bool BaseApp::initialize(unsigned int* argcp, char** argv)
{
	//
	// Initialize the preferences file
	//
	theXmlPreferences->BuildTheXmlPreferences();

    //
    // Initialize the window system if not done already.
    //
	if (!this->initializeWindowSystem(argcp, argv))
		return false;
	
    //
    // Since the instance name of this object was set in the UIComponent
    // constructor before the name of the program was visible, delete the
    // old name and set it to argv[0].
    //
	if(this->name)
		delete[] this->name;

    this->name = DuplicateString(argv[0]);

    //
    // Add Application specific actions. Fixme: apparently does nothing.
    //
    this->addActions();

    //
    // Initialize and manage any windows registered with this
    // application at this point.
    //
    this->notifyClients(BaseApp::MsgCreate);

    return true;
}


//
// Post the copyright notice that is returned by this->getCopyrightNotice().
// If it returns NULL, then don't post any notice.
//
void BaseApp::postCopyrightNotice()
{
    const char *c = this->getCopyrightNotice();

    if (c) {
	//
	// Post the copyright message.
	//
	TimedMessage *copyright =
	    new TimedMessage("copyrightMessage",
	    c, 
	    "Welcome",
	    5000);
	copyright->post();
    }
}

void BaseApp::handleEvents()
{
	if(this->applicationContext->MainForm) {
		System::Threading::Thread::CurrentThread->ApartmentState = System::Threading::ApartmentState::STA;
		Application::Run(this->applicationContext);
	}

	//XEvent event;
    //
    // Loop forever...
    //
    //for (;;) {
	//XtAppNextEvent (this->applicationContext, &event);
	//this->handleEvent(&event);
    //}
}

//void BaseApp::handleEvent (XEvent *xev)
//{
//    XtDispatchEvent (xev);
//}


void BaseApp::manage()
{
    //
    // Notify the client windows to manage themselves.
    //
    this->notifyClients(BaseApp::MsgManage);
}


void BaseApp::unmanage()
{
    //
    // Notify the client windows to unmanage themselves.
    //
    this->notifyClients(BaseApp::MsgUnmanage);
}


//
// Calls to this routine can be 'stacked' so that the first call
// sets the cursor and the last call resets the cursor.
// setBusyCursor(true);		// Sets busy cursor
// setBusyCursor(true);		// does not effect cursor
// setBusyCursor(true);		// does not effect cursor
// setBusyCursor(false);	// does not effect cursor
// setBusyCursor(true);		// does not effect cursor
// setBusyCursor(false);	// does not effect cursor
// setBusyCursor(false);	// does not effect cursor
// setBusyCursor(false);	// resets cursor
//
void BaseApp::setBusyCursor(bool setting)
{
	ASSERT(this->busyCursors >= 0);

	if (setting)
	{
		this->busyCursors++;	
	}
	else
	{
		this->busyCursors--;	
	}

	switch (this->busyCursors) {
	case 0:
		this->notifyClients(BaseApp::MsgResetCursor);
		break;
	case 1:
		if (setting)
			this->notifyClients(BaseApp::MsgSetBusyCursor);
		break;
	}

	ASSERT(this->busyCursors >= 0);
}


//
// This is currently only used for debugging.
//
//void BaseApp::DumpApplicationResources(const char *filename)
//{
//    Display *display = theApplication->getDisplay();
// 
//#if defined XlibSpecificationRelease && XlibSpecificationRelease > 4
//    XrmPutFileDatabase(XrmGetDatabase(display), filename);
//#else
//    XrmPutFileDatabase(display->db, filename);
//#endif
//}	

//
// Virtual methods that are called by Command::ExecuteCommandCallback()
// before and after Command::execute().
//
void BaseApp::startCommandInterfaceExecution()
{
    this->notifyClients(Command::MsgBeginExecuting);
}
void BaseApp::endCommandInterfaceExecution()
{
    this->notifyClients(Command::MsgEndExecuting);
}


const char *BaseApp::getFormalName() 
{
    return "'Your Application's Formal Name Here'";
}

const char *BaseApp::getInformalName() 
{
    return "'Your Application's Informal Name Here'";
}

const char *BaseApp::getCopyrightNotice() 
{
    return "'Your Application's Copyright Notice Here'";
}

void BaseApp::helpOn(const char *topic)
{
    printf("Your Application specific help on `%s' here\n", topic);
}
const char *BaseApp::getHelpDirectory()
{
    return ".";
}

const char *BaseApp::getHelpDirFileName()
{
    return "HelpDir";
}
const char *BaseApp::getHTMLDirectory()
{
    return ".";
}

const char *BaseApp::getHTMLDirFileName()
{
    return "Help.idx";
}

//extern "C" int Application_XErrorHandler(Display *display, XErrorEvent *event)
//{
//    if (theApplication)
//        return theApplication->handleXError(display, event);
//    else
//	return 1;
//}

//int Application::handleXError(Display *display, XErrorEvent *event)
//{
//    char buffer[BUFSIZ];
//    char mesg[BUFSIZ];
//    char number[32];
//    XGetErrorText(display, event->error_code, buffer, BUFSIZ);
//    XGetErrorDatabaseText(display, "XlibMessage", "XError",
//        "X Error", mesg, BUFSIZ);
//    fprintf(stderr, "%s:  %s\n", mesg, buffer);
//    XGetErrorDatabaseText(display, "XlibMessage", "MajorCode",
//        "Request Major code %d", mesg, BUFSIZ);
//    fprintf(stderr, mesg, event->request_code);
//    if (event->request_code < 128) {
//        sprintf(number, "%d", event->request_code);
//        XGetErrorDatabaseText(display, "XRequest", number, "", buffer, BUFSIZ);
//    } else {
//        sprintf(buffer, "Extension %d", event->request_code);
//    }
//    fprintf(stderr, " (%s)\n  ", buffer);
//    XGetErrorDatabaseText(display, "XlibMessage", "MinorCode",
//        "Request Minor code %d", mesg, BUFSIZ);
//    fprintf(stderr, mesg, event->minor_code);
//    if (event->request_code >= 128) {
//        sprintf(mesg, "Extension %d.%d",
//            event->request_code, event->minor_code);
//        XGetErrorDatabaseText(display, "XRequest", mesg, "", buffer, BUFSIZ);
//        fprintf(stderr, " (%s)", buffer);
//    }
//    fputs("\n  ", stderr);
//    XGetErrorDatabaseText(display, "XlibMessage", "ResourceID",
//        "ResourceID 0x%x", mesg, BUFSIZ);
//    fprintf(stderr, mesg, event->resourceid);
//    fputs("\n  ", stderr);
//    XGetErrorDatabaseText(display, "XlibMessage", "ErrorSerial",
//        "Error Serial #%d", mesg, BUFSIZ);
//    fprintf(stderr, mesg, event->serial);
//    fputs("\n  ", stderr);
//
//#if defined(XlibSpecificationRelease) && XlibSpecificationRelease <= 4
//    // R5 does not allow one to get at display->request.
//    XGetErrorDatabaseText(display, "XlibMessage", "CurrentSerial",
//        "Current Serial #%d", mesg, BUFSIZ);
//    fprintf(stderr, mesg, display->request);
//    fputs("\n", stderr);
//#endif
//
//    if (event->error_code == BadImplementation) return 0;
//
//    return 1;
//}

//extern "C" void Application_XtWarningHandler(char *message)
//{
//    if(theApplication)
//        theApplication->handleXtWarning(message);
//}
//void Application::handleXtWarning(char *message)
//{
//   if(strstr(message, "non-existant accelerators") ||
//      strstr(message, "to remove non-existant passive grab") ||
//      strstr(message, "remove accelerators"))
//        return;
//
//   fprintf(stderr, "XtWarning: %s\n", message);
//
//}
//
// Start a tutorial on behalf of the application.
// Return true if successful.  At this level in the class hierachy
// we don't know how to start a tutorial so we always return false.
//
bool BaseApp::startTutorial()
{
    return false;
}
//
// A virtual method that allows other applications to handle ASSERT
// failures among other things.
//
void BaseApp::abortApplication()
{
    abort();
}


//
// this is normally something like $HOME/DX.  There is a virtual version
// of this method in IBMApplication that uses UIRoot on the pc.
//
bool BaseApp::getApplicationDefaultsFileName(char* res_file, bool create)
{
    const char* class_name = this->getApplicationClass();
    char* home = (char*)getenv("HOME");
    int len = strlen(home);
    strcpy (res_file, home);
    res_file[len++] = '/';
    res_file[len++] = '.';
    char* cp = (char*)class_name;
    while (*cp) {
	res_file[len++] = tolower(*cp);
	cp++;
    }
    strcpy (&res_file[len], "-ad");
    return this->isUsableDefaultsFile(res_file, create);
}

bool BaseApp::isUsableDefaultsFile(const char* res_file, bool create)
{
#if !defined(DXD_OS_NON_UNIX)
    int ru = S_IRUSR;
    int wu = S_IWUSR;
    int rg = S_IRGRP;
    int ro = S_IROTH;
    int reg = S_IFREG;
#else
    int ru = _S_IREAD;
    int wu = _S_IWRITE;
    int rg = 0;
    int ro = 0;
    int reg = _S_IFREG;
#endif
    //
    // If the file isn't writable, then return false so we
    // won't try using it to store settings.
    //
    bool writable=true;
    bool erase_the_file=false;
    struct STATSTRUCT statb;
    if (STATFUNC(res_file, &statb)!=-1) {
	//if (S_ISREG(statb.st_mode)) {
	if (statb.st_mode & reg) {
	    if ((statb.st_mode & wu) == 0) {
		writable = false;
	    } else if ((statb.st_size==0) && (!create)) {
		// file is usable.  If we don't need the file
		// and the file size is 1, then erase it.  This
		// deals with the mistake I made in creating the
		// file in situations where it wouldn't ever be used.
		erase_the_file = true;
	    }
	} else {
	    writable = false;
	}
    } else if ((errno==ENOENT)&&(create)) {
	int fd = creat(res_file, ru | wu | rg | ro); //S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
	if (fd >= 0) {
	    close(fd);
	} else {
	    writable = false;
	    //perror(res_file);
	}
    } else {
	//perror(res_file);
	writable = false;
    }

    if ((writable) && (erase_the_file)) {
	unlink(res_file);
	writable = false;
    }

    return writable;
}

