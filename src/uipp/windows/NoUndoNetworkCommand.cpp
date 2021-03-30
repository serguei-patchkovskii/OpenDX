/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"




#include "NoUndoNetworkCommand.h"
#include "Network.h"
#include "DXApplication.h"
#include "DXWindow.h"
#include "EditorWindow.h"

NoUndoNetworkCommand::NoUndoNetworkCommand(const char*   name,
				       CommandScope* scope,
				       bool       active,
				       Network	*net,
				       NetworkCommandType comType ) :
	NoUndoCommand(name, scope, active)
{
	this->commandType = comType;
	this->network = net;
}


bool NoUndoNetworkCommand::doIt(CommandInterface *ci)
{
    Network *net = this->network;

    ASSERT(net);

    switch (this->commandType) {
	case NoUndoNetworkCommand::HelpOnNetwork:
	    net->postHelpOnNetworkDialog();
	    break;
	case NoUndoNetworkCommand::SetNetworkName:
	    net->postNameDialog();
	    break;
	case NoUndoNetworkCommand::SaveNetwork:
	    net->saveNetwork(net->getFileName());
	    break;
	case NoUndoNetworkCommand::SaveNetworkAs:
	    if (net->isNetworkSavable())
		net->postSaveAsDialog();
	    break;
	case NoUndoNetworkCommand::SaveConfiguration:
            net->postSaveCfgDialog();
	    break;
	case NoUndoNetworkCommand::OpenConfiguration:
            net->postOpenCfgDialog();
	    break;
	default:
	    ASSERT(0);
    }

    return true;
}


//
// Only activate the save and SaveAs commands when theDXApplication 
// allows saving networks as defined by appAllowsSavingNetFile()
//
void NoUndoNetworkCommand::activate()
{
    bool doit;

    switch (this->commandType) {
	case NoUndoNetworkCommand::SaveNetwork:
	case NoUndoNetworkCommand::SaveNetworkAs:
	    doit = theDXApplication->appAllowsSavingNetFile(this->network);
	    break;
	default:
	    doit = true;
	    break;
    }
    if (doit)
	this->NoUndoCommand::activate();

}
