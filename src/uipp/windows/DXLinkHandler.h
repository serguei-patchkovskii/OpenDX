/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"


#ifndef _DXLinkHandler_h
#define _DXLinkHandler_h

#include "Base.h"
#include "PacketIF.h"
#include "LinkHandler.h"

//
// Class name definition:
//
#define ClassDXLinkHandler "DXLinkHandler"

class DXLinkHandler : public LinkHandler
{
    private:

	static bool SaveNetwork(const char *c, int id, void *va);
	static bool OpenNetwork(const char *c, int id, void *va);
	static bool OpenNetworkNoReset(const char *c, int id, void *va);
	static bool OpenConfig(const char *c, int id, void *va);
	static bool SaveConfig(const char *c, int id, void *va);
	static bool ResetServer(const char *c, int id, void *va);
	static bool Version(const char *c, int id, void *va);
	static bool SetTabValue(const char *c, int id, void *va);
	static bool SetGlobalValue(const char *c, int id, void *va);
	static bool Terminate(const char *, int id, void *);
	static bool Disconnect(const char *, int id, void *);
	static bool QueryValue(const char *c, int id, void *va);
	static bool QueryExecution(const char *c, int id, void *va);
	static bool ConnectToServer(const char *c, int id, void *va);
	static bool StartServer(const char *c, int id, void *va);
	static void    SyncCB(void *clientData, int id, void *line);
	static bool Sync(const char *, int id, void *va);
	static bool SyncExec(const char *, int id, void *va);
	static bool OpenControlPanel(const char *c, int id, void *va);
	static bool CloseControlPanel(const char *c, int id, void *va);
	static bool ResendParameters(const char *c, int id, void *va);
	static bool SetProbePoint(const char *c, int id, void *va);
	static bool SetInteractionMode(const char *c, int id, void *va);
	static bool LoadMacroFile(const char *c, int id, void *va);
	static bool LoadMacroDirectory(const char *c, int id, void *va);
	static bool ExecOnce(const char *c, int id, void *va);
	static bool ExecOnChange(const char *c, int id, void *va);
	static bool EndExecution(const char *c, int id, void *va);
	static bool EndExecOnChange(const char *c, int id, void *va);
	static bool PopupVCR(const char *c, int id, void *va);
	static bool OpenVPE(const char *c, int id, void *va);
	static bool CloseVPE(const char *c, int id, void *va);
	static bool OpenSequencer(const char *c, int id, void *va);
	static bool CloseSequencer(const char *c, int id, void *va);
	static bool OpenColormapEditor(const char *c, int id, void *va);
	static bool CloseColormapEditor(const char *c, int id, void *va);
	static bool OpenImage(const char *c, int id, void *va);
	static bool CloseImage(const char *c, int id, void *va);
	static bool SelectProbe(const char *c, int id, void *va);
        static bool SequencerPlay(const char *c, int id, void *va);
        static bool SequencerPause(const char *c, int id, void *va);
        static bool SequencerStep(const char *c, int id, void *va);
        static bool SequencerStop(const char *c, int id, void *va);
        static bool SequencerPalindrome(const char *c, int id, void *va);
        static bool SequencerLoop(const char *c, int id, void *va);

	static bool SetHWRendering(const char *c, int id, void *va);
	static bool SetSWRendering(const char *c, int id, void *va);
	bool setRenderMode(const char *msg, int id, bool swmode);


	static bool StallNTimes(void *d);
        static bool StallUntil(const char *c, int id, void *va);

	//
	// These two are used to delay the handling of messages
	// until the executive is done executing.  They also serve, to
	// interleave X events with the handling of messages which
	// keeps messages from being handled consecutively.
	//
	static bool DestallOnNoExecution(void *d);
	void stallForExecutionIfRequired();
    
	int stallCount;	// For implementing StallNTimes().

    public:

	DXLinkHandler(PacketIF *);

	//
	// Returns a pointer to the class name.
	//
	const char* getClassName()
	{
	    return ClassDXLinkHandler;
	}

};

#endif
