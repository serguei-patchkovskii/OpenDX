/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

#include "Application.h"
#include "QuitCommand.h"


QuitCommand::QuitCommand(BaseApp*  app,
			 const char*   name,
			 CommandScope* scope,
			 bool       active,
			 char*         dialogTitle,
			 char*         dialogQuestion) :
	ConfirmedCommand(name, scope, active, dialogTitle, dialogQuestion)
{
    //
    // No op.
    //
    this->application = app;
}


bool QuitCommand::doIt(CommandInterface *ci)
{
    //
    // Terminate the application
    //
    application->shutdownApplication();

    return true;
}


