/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"




#ifndef _PageGroupManager_h
#define _PageGroupManager_h


#include "GroupManager.h"
#include "Dictionary.h"
#include "DXStrings.h"

//
// Class name definition:
//
#define ClassPageGroupManager	"PageGroupManager"
#define PAGE_GROUP "page"

class DXApplication;
class Network;
class UIComponent;
class PageSelector;


//
// The class to hold the group info
//
class PageGroupRecord : public GroupRecord
{
  friend class PageGroupManager;
  friend class PageSelector;
  friend class PageTab;
  private:
    
  protected:
     PageGroupRecord(Network *net, const char *name): GroupRecord(net, name) {
	this->page_window = NUL(UIComponent*);
	this->workspace = NUL(UIComponent*);
	this->order_in_list = 0;
	this->windowed = false;
	this->showing = false;
     }


    UIComponent* page_window;
    UIComponent* workspace;

    int order_in_list;
    bool windowed;
    bool showing;

  public:

    void setComponents (UIComponent* page_window, UIComponent* page);

    ~PageGroupRecord() { }
};


//
// PageGroupManager class definition:
//				
class PageGroupManager : public GroupManager
{
  private:
    //
    // Private member data:
    //

  protected:
    //
    // Protected member data:
    //

    virtual GroupRecord *recordAllocator(Network *net, const char *name) { 
	return new PageGroupRecord(net, name);
    }

  public:
    //
    // Destructor:
    //
    ~PageGroupManager(){}

    //
    // Constructor:
    //
    PageGroupManager(Network *net); 

    static bool SupportsMacros() { return true; }

    //
    // Parse/Print the  group assignment comment.
    //
    virtual bool parseComment(const char *, 
			const char *, 
			int ,
			Network *);
    virtual bool printComment(FILE *);

    virtual bool survivesMerging() { return true; }

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassPageGroupManager;
    }
};


#endif // _PageGroupManager_h
