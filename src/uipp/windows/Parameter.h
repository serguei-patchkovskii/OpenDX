/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"




#ifndef _Parameter_h
#define _Parameter_h


#include "Base.h"
#include "List.h"
#include "DXValue.h"
#include "DXType.h"
#include "ParameterDefinition.h"
#include "Node.h"
#include "Cacheability.h"


//
// Class name definition:
//
#define ClassParameter	"Parameter"

class ParameterDefinition;
class DXValue;
class Ark;

#define FOR_EACH_PARAMETER_ARC(p,a,iterator) \
    for (iterator.setList(p->arcs) ; (a = (Parameter*)iterator.getNext()) ; )

//
// Parameter class definition:
//				
class Parameter : public Base
{
        friend const List *Node::getIOArks(List *, int);
  private:
    //
    // Private member data:
    //
	ParameterDefinition	*definition;
	DXValue	*value;
	List	arcs;	    // List of paraters that where connected too
 	bool defaultingWhenUnconnected; // Should we use the default value. 
 	bool viewable;  // Is this parameter's tab exposable. 
 	bool visible;    // Is this parameter's tab visible. 
 	bool dirty;	    // Has parameter changed	

  protected:
    //
    // Protected member data:
    //

    // Valid for Outputs only. Indicates how the exec should cache an
    // output.
    Cacheability cacheability;

    //
    // For the given type, try and augment the given string value with
    // syntactic sugar to coerce the given value to the given type.
    // The types we can coerce are StringType, ListType, VectorType and 
    // TensorType.
    // Return T/F indicating whether the value was successfully set (and 
    // coerced).
    //
    bool coerceAndSetValue(const char *value, dx_Type type);


  public:


    //
    // Constructor:
    //
    Parameter(ParameterDefinition *pd);

    //
    // Destructor:
    //
    ~Parameter(); 

    //
    // Add/remove an arc to/from the given parameter 
    //
    bool 	addArk(Ark *a);
    bool 	removeArk(Ark *a) { return arcs.removeElement(a); }
    Ark 	*getArk(int i) { return (Ark *)arcs.getElement(i); }
    bool 	isConnected() { return this->arcs.getSize() != 0; }

    //
    // Manipulate the exposability and visibility 
    //
    void 	setVisibility(bool v) { this->visible = 
					   this->isViewable() && v; }
    void 	setVisible()		{ this->visible = true; }
    bool	isVisible()		{ return this->visible; }
    bool	isVisibleByDefault()	
			{ ASSERT(this->definition);
			  return this->definition->getDefaultVisibility(); }
    void 	clearVisible()		{ this->visible = false; }
    bool	isViewable()		{ ASSERT(this->definition);
					  return this->definition->isViewable();
					}
    
    //
    // Manipulate the Value and definition
    //
    void 	setDirty()	{ this->dirty = true; }
    bool 	isDirty()	{ return this->dirty == true; }
    void 	clearDirty()	{ this->dirty = false; }
    bool  	isNeededValue(bool ignoreDirty = true);
    bool  	isRequired() { return this->definition->required; }
			
    bool 	isInput()		{ return this->definition->isInput(); }
    bool 	isDefaulting();	
    void 	setUnconnectedDefaultingStatus(bool defaulting=true);
   
    //
    // Set the value of this parameter to the value represented by v which 
    // must match the given type.  If coerce is true, then try and add
    // syntactic sugar to make the value match the type.
    //
    bool 	setValue(const char *v, dx_Type t, bool coerce = true);

    //
    // Use setValue(v,t,c) to try and set the value to one of the types.
    //
    dx_Type	setValue(const char *v);

    //
    // Uset setValue(v,t,c) to set the stored value.
    // If the parameter is not defaulting, this is
    // the same as setValue, but if it is defaulting, then we set the
    // value but leave the parameter clean and defaulting.
    //
    bool setSetValue(const char *value, dx_Type type);


    // DXValue 	*getValue() { return this->value; } 
    bool 	hasValue() 
		{ return (this->value != NUL(DXValue*)) && 
 		 	 (this->value->getType() != DXType::UndefinedType); } 
    dx_Type    	getValueType() 
			{ ASSERT(this->value); return this->value->getType(); }
    void   	setDefinition(ParameterDefinition *pd) { this->definition=pd;}
    ParameterDefinition *getDefinition() { return this->definition; }
    const char *getDescription() { return getDefinition()->getDescription(); }

    const char 	*getSetValueString() 
		    { const char *s = "NULL"; 
		      if (this->hasValue())
			    s = this->value->getValueString();
		      return s;
		    }
    const char 	*getValueString() 
		    { const char *s = "NULL"; 
		      if (!this->isDefaulting() && this->value)
			    s = this->value->getValueString();
		      return s;
		    }
    const char 	*getValueOrDefaultString() 
		    {
			const char *s;
		        if (!this->isDefaulting() && this->value)
			    s = this->value->getValueString();
			else
			{
			    ParameterDefinition *pd = this->getDefinition();
			    s = pd->getDefaultValue();
			}
		        return s;
		    }

    //
    // Get the default type of this parameter.  When a parameter has more
    // than 1 type, always return the first type on the type list.
    //
    dx_Type getDefaultType() { return this->getDefinition()->getDefaultType(); }

    //
    // Get the i'th component of a vector value.  
    //
    double getVectorComponentValue(int index) 
		{ ASSERT(this->value); 
		  return this->value->getVectorComponentValue(index);
		}
    //
    // Get the floating point value of a scalar
    //
    double getScalarValue() 
		{ ASSERT(this->value); return this->value->getScalar(); }
    //
    // Get the value of an integer... 
    //
    int   getIntegerValue() 
		{ ASSERT(this->value); return this->value->getInteger(); }
 
    //
    // These methods are somewhat of a hack, but at least they belong here and
    // not in ScalarNode.C which is what uses them (for now anyway).
    //
    // G/Set the n'th component of a vector, scalar or integer.  For scalars
    // and integers, the component number must be 1.
    // Components are indexed from 1.
    //
    int getComponentCount();
    double getComponentValue(int component);
    bool setComponentValue(int component, double val);

#if 0
    //
    // Get the value list... 
    //
//    List*  getValueList()
//               { ASSERT(this->value); return this->value->getValueList(); }
#endif
    //
    // Get the name of this parameter (no instance, index numbers or prefix). 
    //
    const char *getNameString() { return this->definition->getNameString(); }

    //
    // Get the list of allowed types for this parameter. 
    // Returns a null terminated list of strings.
    //
    const char* const *getTypeStrings() 
		{ return this->definition->getTypeStrings(); }

    //
    // Determine if this (input) and another parameter (output) are type 
    // compatible. 
    //
    bool typeMatch(Parameter *src) 
 		{ return DXType::MatchTypeLists(src->definition->types,
					        this->definition->types); }
    
    //
    // Inquire and change the cacheability of a parameter.  This (today) is
    // only available for outputs.
    //
    Cacheability getCacheability()
    {
	return this->cacheability;
    }
    bool isFullyCached()
    {
	return this->cacheability == OutputFullyCached;
    }
    void setCacheability(Cacheability c) 
    {
	ASSERT(!this->isInput());
	if (this->cacheability != c)
	{
	    this->cacheability = c;
	    this->setDirty();
	}
    }
    bool hasWriteableCacheability()
                { return this->definition->hasWriteableCacheability(); }
    bool getDefaultCacheability()
                { return this->definition->getDefaultCacheability(); }

    //
    // Determine if this instance is derived  from the give class.
    //
    bool isA(const char *classname);
    virtual bool isA(Symbol classname);

    //
    // Remove all the Arks connected to this parameter.
    //
    void disconnectArks();

    //
    // Get the selectable values for this parameter.
    // This returns a pointer to a constant array of pointers to
    // constant strings which is NOT to be manipulated by the caller.
    // The returned array of pointers is NULL terminated.
    //
    const char* const *getValueOptions();

#ifdef DXUI_DEVKIT
    //
    // Get any variable declarations that will be required by the code
    // generated in getObjectCreateCode(). NULL is returned if none required.
    // The returned string must be freed by the caller.
    //
    char *getObjectCodeDecl(const char *indent, const char *tag);

    //
    // Get a string that represents the libDX C code to generate
    // a DX Object from the value of the parameter.  The code is
    // created to assign the object to the given lvalue variable name.
    // The returned string must be freed by the caller.
    //
    char *getObjectCreateCode(const char *indent, 
				const char *tag, const char *lvalue);
    // 
    // Generate code to clean up after the code from getObjectCreateCode()
    // was executed. lvalue must be the same value that was passed to 
    // getObjectCreateCode().
    // The returned string must be freed by the caller.
    //
    char *getObjectCleanupCode(const char *indent, const char *tag);
#endif // DXUI_DEVKIT

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassParameter;
    }
};


#endif // _Parameter_h
