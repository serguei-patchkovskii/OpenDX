/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"


#ifndef _SelectionNode_h
#define _SelectionNode_h


#include "InteractorNode.h"
#include "DeferrableAction.h"
#include "List.h"

class Network;

//
// Class name definition:
//
#define ClassSelectionNode	"SelectionNode"


//
// SelectionNode class definition:
//				
class SelectionNode : public InteractorNode 
{
    friend class SelectionInstance;	

  private:
    //
    // Private member data:
    //
    //
    // This is used during parsing of the .cfg, to delay setting of the 
    // selected option.
    //
    static      int OptionsLeftToSet;

    int		optionCount;
    bool	alwaysEnlistOutputs;

    static void InstallNewOptions(void *staticdata, void *requestData);
    DeferrableAction *deferNewOptionInstallation;

    //
    // Update the output values based on the current selections, then send
    // the values to the server.
    //
    void updateOutputs(bool fromServer = false);

    //
    // Update the selected option index, and if requested, update the output
    // values to match the values indicated by the index.
    //
    void changeSelectedOptionIndex(int index, bool set,
                        bool send = true, bool update_outputs = true);


    //
    // Update the selected option index, and if requested, update the output
    // values to match the values indicated by the index.
    //
#if 00 // Not used
    void removeSelectedOptionIndex(int index, bool send = true, 
						bool update_outputs = true);
#endif
    void addSelectedOptionIndex(int index, bool send = true, 
						bool update_outputs = true);
    void clearSelections(bool send = true, bool update = true);

  protected:
    //
    // Protected member data:
    //

    List	selectedOptions;

    bool cfgPrintInteractorAuxInfo(FILE *f);
    bool cfgPrintSelectionsComment(FILE *f);
    bool cfgPrintOptionComments(FILE *f);

    //
    // Parse comments the 'option[' comment. 
    //
    bool cfgParseOptionComment(const char *comment,
					const char *filename, int lineno);

    //
    // Parse comments the 'selections: ' comment. 
    //
    bool cfgParseSelectionsComment(const char *comment,
					const char *filename, int lineno);

    // The messages we parse can contain one or more of the following...
    //
    //      'value list={...}' or 'string list={...}'
    //
    // If any input or output values are to be changed, don't send them
    // because the module backing up the interactor will have just executed
    // and if the UI is in 'execute on change' mode then there will be an
    // extra execution.
    //
    // Returns the number of attributes parsed.
    //
    virtual int handleInteractorMsgInfo(const char *line);

    //
    // Define the mapping of inputs that shadow outputs.
    // By default, all data driven interactors, have a single output that is
    // shadowed by the third (hidden) input.
    // Returns an input index (greater than 1) or 0 if there is no shadowing 
    // input for the given output index.
    //
    virtual int getShadowingInput(int output_index);

    //
    // If either of the list inputs has changed, we must determine the size
    // of the smaller of the two lists and reset this->optionCount to that 
    // value.  
    // NOTE: If this routine is being called, then one of the values must 
    //    have a set value (even though both are allowed not too).
    //
    void ioParameterStatusChanged(bool input, int index,
				NodeParameterStatusChange status);

    bool setValueOptionsAttribute(const char *vlist);
    bool setStringOptionsAttribute(const char *slist);
    bool initValueOptionsAttribute(const char *vlist);
    bool initStringOptionsAttribute(const char *slist);
    const char *getValueOptionsAttribute();
    const char *getStringOptionsAttribute();

    //
    // Get a a SelectorInstance instead of an InteractorInstance.
    //
    InteractorInstance *newInteractorInstance();

    //
    // These define the initial values 
    // Also, nice to force this class to be pure abstract.
    //
    virtual const char *getInitialValueList() = 0;
    virtual const char *getInitialStringList() = 0;

  public:
    //
    // Constructor:
    //
    SelectionNode(NodeDefinition *nd, Network *net, 
				int instnc, 
				bool alwaysEnlistOutputs = false);

    //
    // Destructor:
    //
    ~SelectionNode();

    //
    // Get the number of components for this interactor.
    //
    int getSelectedOptionCount() { return this->selectedOptions.getSize(); }
    int getOptionCount() { return this->optionCount; }

    //
    // Get the value of the indicated option.
    // The returned string must be deleted by the caller.
    //
    char  *getOptionValueString(int optind);
    //
    // Get the name of the indicated option.
    // The return string is not double quoted unless keep_quotes is true.
    // Ther returned string must be deleted by the caller.
    //
    char  *getOptionNameString(int optind, bool keep_quotes = false);

    bool appendOptionPair(const char *val, const char *label);

    //  
    // Use the value list and string list to set the new list of options.
    // Also, notify all instances that the state has changed.
    //
    void installNewOptions(const char *vlist, const char *slist, bool send);


    //
    // Called once for each class by the allocator in definition. 
    // 
    virtual bool initialize();

    //
    // Parse comments found in the .cfg that the InteractorNode knows how to
    // parse plus ones that it does not.
    //
    virtual bool cfgParseComment(const char *comment,
					const char *filename, int lineno);

    //
    // Return true of the given index'ed option is selected.
    //
    bool isOptionSelected(int index);

    //
    // Determine if this node is a node of the given class
    //
    virtual bool isA(Symbol classname);


    //
    // Update the selected option index, and if requested, update the output
    // values to match the values indicated by the index.
    //
    void setSelectedOptions(int *setIndices, int count, 
				bool send = true, 
				bool update_outputs = true);

    virtual bool printJavaType(FILE*, const char*, const char*);

    virtual const char* getJavaNodeName() { return "SelectionNode"; }
    virtual bool printJavaValue(FILE*);

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassSelectionNode;
    }
};


#endif // _SelectionNode_h


