/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"



#ifndef _MacroNode_h
#define _MacroNode_h


#include "Node.h"


//
// Class name definition:
//
#define ClassMacroNode	"MacroNode"

//
// Referenced Classes
class EditorWindow;
class Network;

//
// MacroNode class definition:
//				
class MacroNode : public Node
{
  private:
    //
    // Private member data:
    //

  protected:
    //
    // Protected member data:
    //

  public:
    //
    // Constructor:
    //
    MacroNode(NodeDefinition *nd, Network *net, int instnc);

    //
    // Destructor:
    //
    ~MacroNode();

    virtual void updateDefinition();

    virtual bool initialize();

    virtual bool     sendValues(bool     ignoreDirty = true);

    virtual void openMacro();

    //
    // Determine if this node is a node of the given class
    //
    virtual bool isA(Symbol classname);

    virtual bool needsFastSort() { return true; }

    //
    // WebOptions is a macro.  I would like to represent it with its own
    // Node subclass but that would require sending down the text of the
    // macro the way the image macro is sent and it seems too cumbersome
    // to include it in every .net file.  this->getJavaNodeName() will
    // only be called from printAsJava and only in the case where the
    // macro is WebOptions
    //
    virtual bool hasJavaRepresentation();
    virtual const char* getJavaNodeName() { return "WebOptionsNode"; }
    virtual bool printInputAsJava(int input);


    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassMacroNode;
    }
};


#endif // _MacroNode_h
