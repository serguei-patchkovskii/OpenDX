/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"



#ifndef _DXLInputNode_h
#define _DXLInputNode_h



#include "UniqueNameNode.h"


//
// Class name definition:
//
#define ClassDXLInputNode	"DXLInputNode"

//
// Referenced Classes

//
// DXLInputNode class definition:
//				
class DXLInputNode : public UniqueNameNode
{
  private:
    //
    // Private member data:
    //
    static bool Initializing;

  protected:
    //
    // Protected member data:
    //
    virtual char *netNodeString(const char *prefix);

    virtual bool initialize();

    virtual char        *valuesString(const char *prefix);

  public:
    //
    // Constructor:
    //
    DXLInputNode(NodeDefinition *nd, Network *net, int instnc);

    //
    // Destructor:
    //
    ~DXLInputNode();

    virtual bool     sendValues(bool     ignoreDirty = true);

    //
    // This is the same as the super-class except that we restrict the
    // label with this->verifyRestrictedLabel().
    //
    virtual bool setLabelString(const char *label);

    //
    // In addition to the superclass' work, make a new label string if our
    // labelString is still of the form DXLIinput_%d
    //
    virtual int assignNewInstanceNumber();

    //
    // Determine if this node is a node of the given class
    //
    virtual bool isA(Symbol classname);

    //
    // Java Beans
    //
    virtual bool printAsBean(FILE*);
    virtual bool printAsBeanInitCall(FILE*);


    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassDXLInputNode;
    }
};


#endif // _DXLInputNode_h
