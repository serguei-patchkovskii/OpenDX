/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

//#include <windows.h>
//#include <winsock.h>

#ifndef _DXChild_h
#define _DXChild_h

//#include "dxThreadMain.h"
#include "Base.h"

class DXExecThread;

//
// Class name definition:
//
#define ClassDXChild	"DXChild"

//extern "C" void DXChild_OutQueuedInputHandler(XtPointer    clientData,
//				              int       *socket,
//				              XtInputId *id);
//extern "C" void DXChild_ErrQueuedInputHandler(XtPointer    clientData,
//					      int       *socket,
//					      XtInputId *id);
//extern "C" void DXChild_OutInputHandler(XtPointer clientData,
//					int       *socket,
//					XtInputId *id);
//extern "C" void DXChild_ErrInputHandler(XtPointer clientData,
//					int       *socket,
//					XtInputId *id);
//extern "C" Boolean DXChild_DeleteObjectWP (XtPointer );


//
// Forward class definitions
//
class List;

//
// DXChild class definition:
//				
class DXChild : public Base
{
  private:
    //
    // Private member data:
    //
    char       *server;
    int         in;
    int         out;
    int         err;
	// DT FIXME: will need to remove child and replace with dxexec.
    int         child;
	DXExecThread * dxexec;

    //XtInputId   outId;
    //XtInputId   errId;
    int         queued;
    char       *errorString;
    int		lineSize;
    char       *outLine;
    char       *errLine;
    //XtWorkProcId deletion_wpid;
    bool    input_handlers_stalled;

	HANDLE	hpipeRead, hpipeWrite;
#define DX_STATIC

    DX_STATIC int  ConnectTo(const char *host,
			  const char *user,
			  const char *cwd,
			  int ac,
			  char *av[],
			  char *ep[],
			  int *remin,
			  int *remout,
			  int *remerr,
			  char *errstr);

    DX_STATIC void MakeLine(char *string, char *newString);
    DX_STATIC int StartExecutive(const char* host,
				       const char* user,
				       const char* cwd,
				       const char* cmd,
				       int*  in,
				       int*  out,
				       int*  err,
				       int*  port, 
				       int*  child,
				       int   block,
				       char **rstringParam);
    //friend void DXChild_OutQueuedInputHandler(XtPointer    clientData,
				//    int       *socket,
				//    XtInputId *id);
    //friend void DXChild_ErrQueuedInputHandler(XtPointer    clientData,
				//	int       *socket,
				//	XtInputId *id);
    //friend void DXChild_OutInputHandler(XtPointer clientData,
				//	int       *socket,
				//	XtInputId *id);
    //friend void DXChild_ErrInputHandler(XtPointer clientData,
				//	int       *socket,
				//	XtInputId *id);
    //friend Boolean DXChild_DeleteObjectWP (XtPointer );
 

  protected:
    //
    // Protected member data:
    //


  public:
    //
    // Constructor:
    //
    DXChild(char *host,
	    char *cmd,
	    int   block = 0,
	    char *user = NULL,
	    char *cwd = NULL);

    //
    // Destructor:
    //
    ~DXChild();

    // Various routines
    int 	getInputFd() { return this->in; }
    int 	getOutputFd() { return this->out; }
    int 	getErrorFd() { return this->err; }

    void 	closeOutput(bool closeConnection = true);
    void 	closeError(bool closeConnection = true);
    int  	waitForConnection();

    int         isQueued() { return this->queued; }
    void        unQueue();
    const char *failed() { return this->errorString; }
    const char *getServer() { return this->server; }
    static int  HostIsLocal(const char *);
    void	setServer(char *);

#if defined(intelnt)
    HANDLE GetWinPipeReadHandle() { return this->hpipeRead; }
    HANDLE GetWinPipeWriteHandle() { return this->hpipeWrite; }
#endif
    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassDXChild;
    }
};


#endif // _DXChild_h
