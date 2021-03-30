/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"


#ifndef _DXExecCtl_h
#define _DXExecCtl_h


#include "Base.h"


//
// Class name definition:
//
#define ClassDXExecCtl	"DXExecCtl"

//
// Referenced classes.
class Network;

//
// DXExecCtl class definition:
//				
class DXExecCtl : public Base
{
  private:
    //
    // Private member data:
    //
    static void BGBeginMessage(void *clientData, int id, void *p);
    static void BGEndMessage(void *clientData, int id, void *p);
    static void HWBeginMessage(void *clientData, int id, void *p);
    static void HWEndMessage(void *clientData, int id, void *p);
    static void ExecComplete(void *clientData, int id, void *p);
    static void ResumeExecOnChange(void *clientData, int id, void *p);
    static void ResetVcrNextFrame(void *clientData, int id, void *p);

    void 	beginSingleExecution(bool update_macros);
    void	endLastExecution(bool resume = false);

    bool 	endExecOnChangePending;

  protected:
    //
    // Protected member data:
    //

    //
    // Execution flag.
    //
    bool isCurrentlyExecuting;
    bool vcrIsExecuting;
    bool execOnChange;
    int	    execOnChangeSuspensions;
    int     hwExecuting;  	// counter for HW rendering messages
    bool hwBusy;  		// setting of busy cursor for HW rendering 
    bool forceNetworkResend;	
    bool forceParameterResend;	
    bool resumeExecOnChangeAfterExecution;	
    bool isExecOnChangeSuspended()  
			     {	return this->execOnChangeSuspensions > 0; }
  public:
    //
    // Constructor:
    //
    DXExecCtl();

    //
    // Destructor:
    //
    ~DXExecCtl(){}


    //
    // Enter/leave execute on change mode.
    //
    void newConnection();
    void suspendExecOnChange();
    void resumeExecOnChange();

    //
    // Go out of execution on change mode without terminating the current
    // graph execution.  If not current executing, then we go ahead and
    // go out of eoc mode, otherwise schedule the exit from eoc mode for
    // the end of the current graph execution (see endLastExecution()).
    // We return true if we were able to go out of eoc mode now, false if
    // we won't be going out until the end of the current execution.
    //
    bool endExecOnChange();

    void enableExecOnChange();
    void updateMacros(bool force = false);
    void executeOnce();

    bool inExecOnChange() { return this->execOnChange;}
    bool isExecuting() { return this->isCurrentlyExecuting; }
    bool isVcrExecuting() { return this->vcrIsExecuting; }
    bool assignmentRequiresExecution()
		{ return !this->isVcrExecuting() && !this->inExecOnChange(); }

    //
    // Functions called by the Sequencer.
    //
    void vcrFrameSet(char* command);
    void vcrTransmit();
    void vcrExecute(int action);
    void vcrCommand(int action, bool state);
    
    //
    // Will take you out of execute on change if in it, and
    // terminate the current execution.
    void terminateExecution();
    void updateMacro(Network *n);

    //
    // This is used to force networks and parameters to be resent
    // after a reset.
    //
    void forceFullResend();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassDXExecCtl;
    }
};


#endif // _DXExecCtl_h
