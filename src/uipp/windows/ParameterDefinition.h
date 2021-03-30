/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"


//////////////////////////////////////////////////////////////////////////////

#ifndef _ParameterDefinition_h
#define _ParameterDefinition_h


#include "List.h"
#include "Definition.h"
#include "DXValue.h"
#include "DXType.h"

#include "Cacheability.h"


//
// Class name definition:
//
#define ClassParameterDefinition	"ParameterDefinition"


class Dictionary;

#define FOR_EACH_PARAM_TYPE(pd, dxtype, iterator) \
 for (iterator.setList(pd->types) ; (dxtype = (DXType*)iterator.getNext()) ; )

//
// Used in the .net file to flag macro parameters as dummies.
//
#define DUMMY_DESCRIPTION_STRING	"<<< Dummy parameter (do not edit) >>>"

//
// ParameterDefinition class definition:
//				
class ParameterDefinition : public Definition 
{

  private:

#if 0 // FIXME: circular includes won't let us do this.
    friend dx_Type Parameter::setValue(const char *v);
#else
    friend class Parameter;
#endif

    //
    // Private member data:
    //
    List		types;
    const char**	typeStrings;	// If !NULL, contains type names
    const char		*description;
    char		*default_value;	
    bool		viewable;	// Is this parameter viewable (in a cdb)
    bool		required;
    bool		default_visibility;
    bool		descriptive_default;
    bool		is_input;	// Does this define an input or output 
    bool		dummy;          // Is this a dummy parameter
    char 		**valueOptions;

    //
    // The following is only valid for inputs and when the value is >= 0.
    // It indicates the output to which this input is rerouted when the
    // executive decides not to schedule the module owning the input.
    // Currenlty, we only keep track of it so we can send it to the 
    // executive if the input belongs to an OUTBOARD module.
    //
    int			rerouteOutput;	

    //
    // Cacheability status of parameter.  
    // Initially used for outputs only.
    //
    Cacheability	defaultCacheability;
    bool	 	writeableCacheability;

#if 1	// FIXME
	friend class NodeDefinition;
#else
	friend bool NodeDefinition::addInput(Symbol Name, 
					ParameterDefinition *pd);
	friend bool NodeDefinition::addOutput(Symbol Name, 
					ParameterDefinition *pd);
#endif
    void buildTypeStrings(void);

  protected:
    //
    // Protected member data:
    //

  public:
    //
    // Constructor:
    //
    ParameterDefinition(Symbol key);

    //
    // Destructor:
    //
    ~ParameterDefinition();

    // 
    // Append the given type t to the list of acceptable types for this
    // parameter definition.  The given type is then owned by the 
    // ParameterDefinition and will be deleted when it is deleted.
    //
    bool	addType(DXType *t);	

    //
    // Remove (and free) the type in the list that matches t 
    //
    bool	removeType(DXType *t);

    //
    // Manipulate the default visibility of the tab for this parameter 
    //
    void 	setDefaultVisibility(bool v = true) 
					{ this->default_visibility = v; }
    bool	getDefaultVisibility() { return default_visibility; }

    //
    // S/Get the 1 based index of the output to which this input can be
    // be rerouted. 
    //
    void setRerouteOutput(int val) 
		{ ASSERT(val > 0 && this->isInput());
		  this->rerouteOutput = val;
		}
    int getRerouteOutput() 
		{ ASSERT(this->isInput());
		  return this->rerouteOutput; 
		}
    //
    // Manipulate the viewability of the tab for this parameter 
    //
    void 	setViewability(bool v) { this->viewable = v; 
					    if (!v) 
					       this->default_visibility = false;
					  }
    bool	isViewable() 	{ return this->viewable; }

    //
    // Retrieves a NULL terminated array of pointers to strings.
    // Each string contains the name of a type that this parameter 
    // can accept.  This returns a pointer to a constant array of
    // pointers to constant character strings.
    //
    const char* const *getTypeStrings() { 
			if (typeStrings == NUL(const char**))
					 buildTypeStrings();
				 ASSERT(this->typeStrings);
				 return (const char* const *)this->typeStrings;
				}
    List *getTypes() { return &this->types; }

    //
    // Manipulate the type of I/O this parameter definition represents. 
    //
    void	markAsInput()	{ is_input = true; }
    void	markAsOutput()	{ is_input = false; }
    bool	isInput()	{ return is_input; }
    bool	isOutput()	{ return !is_input; }
    
    //
    // Change the Description of this parameter ;
    //
    void 	setDescription(const char *d) 
			{  if (description)  delete (char*)description;
			   description = DuplicateString(d); }
    const char  *getDescription(); 

    //
    // Change need for this parameter 
    //
    bool 	isRequired() { return required; }
    void 	setRequired() { required = true; }
    void 	setNotRequired() { required = false; }

    //
    // Set/Get the default value, which must be of a type found in the type list. 
    //
    bool     isDefaultValue() { return descriptive_default == false; }
    bool	setDefaultValue(const char *value); 
    const char  *getDefaultValue()  { return default_value; }

    //
    // Get the default type of this parameter.  When a parameter has more
    // than 1 type, always return the first type on the type list.
    //
    dx_Type getDefaultType();

    //
    // Set the default value, which must be of a type found in the type list. 
    //
    bool	isDefaultDescriptive()   { return descriptive_default; }
    void	setDescriptiveValue(const char *d);

    void    setWriteableCacheability(bool v)
                	{ this->writeableCacheability = v; }
    bool hasWriteableCacheability()
                	{ return this->writeableCacheability; }
    void        setDefaultCacheability(Cacheability c)
                        { this->defaultCacheability = c; }
    Cacheability getDefaultCacheability()
                	{ return this->defaultCacheability; }


    //
    // Get the INPUT/OUTPUT entry in the MDF for this parameter.
    // The returned string must be freed by the caller.
    //
    char *getMDFString();

    //
    // Manage the dummy status of this parameter (typically a macro parameter)
    //
    void  setDummy(bool b);
    bool isDummy();

    //
    // Make a brand new copy of this and return it.
    // If newpd is NULL, then the new ParameterDefinition is allocated.
    //
    ParameterDefinition *duplicate(ParameterDefinition *newpd = NULL);

    //
    // Add the given value to the list of suggested values for this parameter
    //
    bool addValueOption(const char *value);

    //
    // Get the selectable values for this parameter.
    // This returns a pointer to a constant array of pointers to
    // constant strings which is NOT to be manipulated by the caller.
    // The returned array of pointers is NULL terminated.
    //
    const char* const *getValueOptions();

    //
    // On behalf of MacroParameterNodes which ought to be able to
    // take on new types during the running of dxui, permit the
    // user to create new value options.
    //
    void removeValueOptions();

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassParameterDefinition;
    }
};


#endif // _ParameterDefinition_h
