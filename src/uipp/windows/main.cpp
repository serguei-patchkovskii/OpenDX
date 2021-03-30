/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>

#include "stdafx.h"
#include "defines.h"

#include <windows.h>
#include <winsock.h>

#include "DXApplication.h"
#include "XmlPreferences.h"
#include "guicon.h"

#include <stdio.h>
#include <stdlib.h>

using namespace System::Runtime::InteropServices;


//
// Used by the assert macro.
//
const char *AssertMsgString = "Internal error detected at \"%s\":%d.\n";
 
//int main(unsigned int argc, char** argv)
//{
//
//	//
//	// Initialize, build all the windows, and enter event loop.
//	// Note that all the windows are created elsewhere (<Application>Application.cpp),
//	// and managed in the application initialization routine.
//	//
//	if (!theApplication)
//	{
//		theApplication = new DXApplication("DX");
//	}
//
//	if (!theApplication->initialize(&argc, argv))
//		exit(1);
//
//	theApplication->handleEvents();
//
//	WSACleanup();
//
//	return 0;
//}

[STAThread]
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	RedirectOutputToFile();
	WSADATA *wsadata = new WSADATA;
	WSAStartup(MAKEWORD(1,1),wsadata);
	delete wsadata;

	if (!theApplication)
	{
		theApplication = new DXApplication("DX");
	}

	// The following is pretty standard to convert 
	// the .NET command line to standard argv,arg
	System::String __gc* allargs[];
	allargs = System::Environment::GetCommandLineArgs();

	unsigned int argc = allargs->Length;
	char **argv = new char*[argc];

	for(int i=0; i< allargs->Length; i++) {
		argv[i] = new char[allargs[i]->Length + 1];
		strncpy(argv[i], 
			(const char*) (Marshal::StringToHGlobalAnsi(allargs[i])).ToPointer(),
			allargs[i]->Length);
		argv[i][allargs[i]->Length] = '\0';
	}

	// On with our app.
	if (!theApplication->initialize(&argc, argv))
		exit(1);

	theApplication->handleEvents();
	return 0;
}
