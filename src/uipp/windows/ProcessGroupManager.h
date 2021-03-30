/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"




#ifndef _ProcessGroupManager_h
#define _ProcessGroupManager_h


#include "GroupManager.h"
#include "Dictionary.h"
#include "DXStrings.h"

//
// Class name definition:
//
#define ClassProcessGroupManager	"ProcessGroupManager"
#define PROCESS_GROUP "process"

class List;
class DXApplication;
class Network;


//
// The class to hold the group info
//
class ProcessGroupRecord : public GroupRecord
{
    friend class ProcessGroupManager;

  private:
    
    char *host;  
    char *newhost;  

    ProcessGroupRecord(Network *network, const char *name): GroupRecord (network, name) {
	this->host    = NULL;
	this->newhost = NULL;
    };

    ~ProcessGroupRecord() {
	if(this->host) delete this->host;
    }

  public:
    virtual bool  changesWhere () { return true; }
};

//
// The class to hold the host info
//
class ProcessHostRecord
{
    friend class ProcessGroupManager;

  private:
   
    char *args;
    bool dirty;

    ProcessHostRecord(const char* args)
    {
	if(args)
            this->args  = DuplicateString(args);
	else
	    this->args  = NULL;

	this->dirty = false;
    };

    ~ProcessHostRecord()
    {
        if (this->args) delete this->args;
    }
};

//
// ProcessGroupManager class definition:
//				
class ProcessGroupManager : public GroupManager
{
  friend class ProcessGroupAssignDialog;
  friend class ProcessGroupCreateDialog;

  private:
    //
    // Private member data:
    //

  protected:
    //
    // The host-argument dictionary 
    //
    Dictionary	arguments;
    //
    // A dictionary of lists of host assignment. 
    //
    Dictionary	*assignment;

    //
    // Send commands to the executive.
    //
    void   attachGroup(const char *host, const char *group);
    void   detachGroup(const char *host, const char *group);

    //
    // Update the assignment dictionary.
    // Return false if given host does not exist.
    //
    bool addGroupAssignment(const char* host, const char *group);
    bool removeGroupAssignment(const char *group);

    virtual GroupRecord* recordAllocator (Network *net, const char *name) {
	return  new ProcessGroupRecord (net, name);
    }

  public:
    //
    // Constructor:
    //
    ProcessGroupManager(Network *);

    //
    // Destructor:
    //
    ~ProcessGroupManager();

    static bool SupportsMacros() { return false; }

    enum {
		ATTACH,
		DETACH
    };

    virtual void clear();

    // 
    // return the host name assigned to a group.
    //
    const char *getGroupHost(const char* name);
    const char *getGroupHost(int n);
    const char *getGroupNewHost(const char* name);
    const char *getGroupNewHost(int n);
    bool getGroupHostDirty(const char* name);
    void clearGroupHostDirty(const char* name);

    //
    // Assign a host name to a group
    // Return false if the given group doesn't exist
    //
    bool	assignHost(const char *groupname,const char *hostname);
    bool	assignHost(int n,const char *hostname);

    //
    // Really change host names when OK is pressed.
    //
    void updateHosts();

    //
    // clear the temporary storage of host names.
    //
    void clearNewHosts();

    //
    // Access the host's arguments.
    //
    const char *getArgument(const char* host);
    bool getArgumentDirty(const char* host);
    void clearArgumentDirty(const char* host);
    void assignArgument(const char *host,const char *args);
    void clearArgument();

    //
    // Remove modules from the existing group.
    //
    virtual bool     removeGroup(const char *name, Network *net);


    //
    // Create the assignment dictionary.
    //
    Dictionary *createAssignment();

    //
    // Clear the assignment dictionary.
    //
    void clearAssignment();

    //
    // Send commands to the executive.
    //
    void   sendAssignment(int func);

    void   updateAssignment();
    //
    // Management of sending assignment.
    //

    //
    // Parse/Print the  group assignment comment.
    //
    virtual bool parseComment(const char *comment, 
			const char *filename, 
			int lineno,
			Network *net);
    virtual bool printComment(FILE *f);
    virtual bool printAssignment(FILE *f);


    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassProcessGroupManager;
    }
};


#endif // _ProcessGroupManager_h
