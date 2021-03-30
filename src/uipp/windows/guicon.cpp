#include <windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>

#ifndef _USE_OLD_IOSTREAMS
using namespace std;
#endif

using namespace System;
using namespace System::IO;
using namespace System::Runtime::InteropServices;

// maximum mumber of lines the output console should have

static const WORD MAX_CONSOLE_LINES = 500;

void RedirectOutputToFile()
{
	int hConHandle;
	HANDLE lStdHandle;
	HANDLE hFile;
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	FILE *fp;
	char res_file[512];

	// allocate a console for this app

	//AllocConsole();

	#undef CreateDirectory

	System::String __gc *lad = Environment::GetFolderPath(Environment::SpecialFolder::LocalApplicationData);
	lad = System::String::Concat(lad, S"\\OpenDX");

	if(!Directory::Exists(lad)) {
		try {
			System::IO::Directory::CreateDirectory(lad);
		} catch (Exception *e) {
			MessageBox(NULL, "Unable to create OpenDX Application Data Directory\n", NULL, MB_ICONERROR | MB_OK);
			return;
		}
	}

	lad = System::String::Concat(lad, S"\\out.txt");

	strncpy(res_file, 
		(const char*) (Marshal::StringToHGlobalAnsi(lad)).ToPointer(),
		lad->Length);

	res_file[lad->Length] = '\0';


	hFile = CreateFile(res_file,
		GENERIC_WRITE, 
		FILE_SHARE_READ, 
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
			

	// set the screen buffer to be big enough to let us scroll text

	/*GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), 
		&coninfo);
	coninfo.dwSize.Y = MAX_CONSOLE_LINES;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), 
		coninfo.dwSize);*/

	// redirect unbuffered STDOUT to the console

	//lStdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	//hConHandle = _open_osfhandle((intptr_t)lStdHandle, _O_TEXT);
	hConHandle = _open_osfhandle((intptr_t)hFile, _O_TEXT);
	if(hConHandle == -1)
		MessageBox(NULL, "Unable to redirect stdout: _open_osfhandle", NULL, MB_ICONERROR | MB_OK);
	fp = _fdopen( hConHandle, "w" );
	*stdout = *fp;
	setvbuf( stdout, NULL, _IONBF, 0 );


	// redirect unbuffered STDIN to the console

	//lStdHandle = GetStdHandle(STD_INPUT_HANDLE);
	//hConHandle = _open_osfhandle((intptr_t)lStdHandle, _O_TEXT);
	//fp = _fdopen( hConHandle, "r" );
	//*stdin = *fp;
	//setvbuf( stdin, NULL, _IONBF, 0 );

	// redirect unbuffered STDERR to the console

	//lStdHandle = GetStdHandle(STD_ERROR_HANDLE);
	//hConHandle = _open_osfhandle((intptr_t)hFile, _O_TEXT);
	//if(hConHandle == -1)
	//	MessageBox(NULL, "Unable to redirect stderr: _open_osfhandle", NULL, MB_ICONERROR | MB_OK);
	//fp = _fdopen( hConHandle, "w" );
	*stderr = *fp;
	setvbuf( stderr, NULL, _IONBF, 0 );

	// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog 
	// point to console as well

	ios::sync_with_stdio();
}

