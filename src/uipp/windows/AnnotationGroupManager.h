/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"




#ifndef _AnnotationGroupManager_h
#define _AnnotationGroupManager_h


#include "GroupManager.h"
#include "Dictionary.h"
#include "DXStrings.h"

//
// Class name definition:
//
#define ClassAnnotationGroupManager	"AnnotationGroupManager"
#define ANNOTATION_GROUP "annotation"

class Network;


//
// The class to hold the group info
//
class AnnotationGroupRecord : public GroupRecord
{
  friend class AnnotationGroupManager;
  private:
    
  protected:
     AnnotationGroupRecord(Network *net, const char *name): GroupRecord(net, name) {}

    ~AnnotationGroupRecord() { }

  public:
};


//
// AnnotationGroupManager class definition:
//				
class AnnotationGroupManager : public GroupManager
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
	return new AnnotationGroupRecord(net, name);
    }

  public:
    //
    // Destructor:
    //
    ~AnnotationGroupManager(){}

    static bool SupportsMacros() { return true; }

    //
    // Constructor:
    //
    AnnotationGroupManager(Network *net);

    virtual bool printComment (FILE*);
    virtual bool parseComment (const char*, const char*, int, Network*);

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassAnnotationGroupManager;
    }
};


#endif // _AnnotationGroupManager_h
