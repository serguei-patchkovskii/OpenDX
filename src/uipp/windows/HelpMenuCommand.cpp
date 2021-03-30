/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"


#include "HelpMenuCommand.h"
#include "IBMApplication.h"
#include "CommandInterface.h"
#include "InfoDialogManager.h"
#include "TimedMessage.h"
#include "StartWebBrowser.h"

HelpMenuCommand::HelpMenuCommand(const char*   name,
				       CommandScope* scope,
				       bool       active,
				       HelpMenuCommandType comType ) :
	NoUndoCommand(name, scope, active)
{
	this->commandType = comType;
}


bool HelpMenuCommand::doIt(CommandInterface *ci)
{
    bool ret = false;

    switch (this->commandType) {

    case HelpMenuCommand::GenericHelp:
	ASSERT(ci);
	//
	// This is a bit bogus, in that the following normally implies
	// asking help on the option itself, but we use the option name
	// to drive help on specific topics as defined by the name of
	// the CommandInterface referencing this command. 
	//
	ci->componentHelp();
	ret = true;
	break;

    case HelpMenuCommand::HelpTutorial:
	
	ret = theApplication->startTutorial();

	break;

    case HelpMenuCommand::AboutApp:
	
	InfoMessage(theIBMApplication->getAboutAppString());
	ret = true;

	break;

    case HelpMenuCommand::TechSupport:
	{
	char *url = new char[strlen(theIBMApplication->getUIRoot()) + 35];
	strcpy(url, "file://");
	strcat(url, theIBMApplication->getUIRoot());
	strcat(url, "/html/pages/qikgu033.htm");
	if(!_dxf_StartWebBrowserWithURL(url))
	    InfoMessage(theIBMApplication->getTechSupportString());
	delete url;
	}
	ret = true;

	break;

    default:
	ASSERT(0);
    }

    return ret;
}

