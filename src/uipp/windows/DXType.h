/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"



#ifndef _DXType_h
#define _DXType_h


#include "Base.h"
//#include "List.h"
//#include "ListIterator.h"


//
// Type type definition:
//

typedef long dx_Type;

class List;

//
// DXTypeName type definition:
//
typedef struct _DXTypeName
{
    bool		userDefined;
    char*		name;
    dx_Type		type;

} DXTypeName;


//
// DXType class definition:
//				
class DXType : public Base
{
  private:
    //
    // Performs class initialization.
    //
    inline void InitializeClass();

  protected:
    //
    // Protected class data:
    //
    static List*	TypeList;		// global type list
    static bool	DXTypeClassInitialized;	// is class initialized?

    //
    // Protected member data:
    //
    dx_Type		type;		// type value
    const char*		name;		// type name

  public:
    //
    // Ennumeration of base types plus six user-definable types.
    //
    // NOTE: Each type is a bit flag and some times inherit other
    //       types by ORing the bit of the inherited types with
    //       into its bit.
    //
    enum
    {
	UndefinedType		= 0x00000000,	// undefined
	IntegerType		= 0x00000001,	// integer
	FlagType		= 0x00000003,	// flag   |= integer
	ScalarType		= 0x00000005,	// scalar |= integer
	VectorType		= 0x00000008,	// vector
	TensorType		= 0x00000010,	// tensor
	ValueType		= 0x0000001d,	// value =
						//  integer|scalar|vector|tensor
	StringType		= 0x00000020,	// string
	CameraType		= 0x00000040,	// camera
	LightType		= 0x00000080,	// light

	UserType1		= 0x00000100,	// user-defined
	UserType2		= 0x00000200,	// user-defined
	WhereType		= 0x00000400,	// WHERE parameter

	FieldType		= 0x00000800,	// field
	GeometryFieldType	= 0x00001800,	// geometry field |= field
	ColorFieldType		= 0x00002800,	// color field    |= field
	ScalarFieldType		= 0x00004800,	// scalar field   |= field
	VectorFieldType		= 0x00008800,	// vector field   |= field
	DataFieldType		= 0x00010800,	// data field     |= field
	ImageType		= 0x00020800,	// image |= field

	SeriesType		= 0x00040800,	// series |= field
	FieldSeriesType		= 0x000c0800,	// field series |= field|series
	
	GroupType		= 0x00100800,	// group |= field
	ValueGroupType		= 0x00300800,	// value group |= group|field
	ValueListGroupType	= 0x00500800,	// value list group |=
						//   group|field
	FieldGroupType		= 0x00900800,	// field group

	ListType		= 0x01000000,	// list
	ListTypeMask		= 0x0effffff,	// list mask
	ObjectType		= 0x03ffffff,	// object
	DescriptionType		= 0x04000000,	// description

	ValueListType		= DXType::ValueType | DXType::ListType,
	ScalarListType		= DXType::ScalarType | DXType::ListType,
	IntegerListType		= DXType::IntegerType | DXType::ListType,
	FlagListType		= DXType::FlagType | DXType::ListType,
	TensorListType		= DXType::TensorType | DXType::ListType,
	VectorListType		= DXType::VectorType | DXType::ListType,
	StringListType		= DXType::StringType | DXType::ListType,

	ReservedType		= 0x08000000,	// RESERVED FOR FUTURE

	UserType4		= 0x10000000,	// user-defined
	UserType5		= 0x20000000,	// user-defined
	UserType6		= 0x40000000	// user-defined
    };

    //
    // Determine the types of the items in a list.
    // If there are mixed types then the returned type is DXType::ValueType.
    // If there are not mixed types than the type of each item is returned.
    // If an unrecognized   list item is found, DXType::UndefinedType is 
    // returned.
    //
    static dx_Type DetermineListItemType(const char *val);

    //
    // Adds a user-defined type to the class type list.
    // Returns true if successful; otherwise, false.
    // Note: The name string is copied by the function.
    //
    static bool AddUserType(const dx_Type  type,
			       const char* name);

    //
    // Deletes a type (by type) from the class type list.
    // Returns true if successful; otherwise, false.
    //
    static bool DeleteType(const dx_Type type);

    //
    // Given a string containing a value, determine its type. 
    //
    static bool ValueToType(const char *value, List& typelist);


    //
    // Deletes a type (by name) from the class type list.
    // Returns true if successful; otherwise, false.
    //
    static bool DeleteType(const char* name);

    //
    // Returns a name string of the specified type.
    //
    static const char* TypeToString(const dx_Type type);

    //
    // Returns the type of the specified name string.
    //
    static dx_Type StringToType(const char* string);

    //
    // Convert a version 1.0 (DX/6000 1.2 11/92) type to new type system. 
    //
    static dx_Type ConvertVersionType(dx_Type t);

    //
    // Find the first type in the list of DXTypes, that matches the value. 
    //
    static dx_Type FindTypeMatch(const char *value, List *typelist);

    //
    // Returns true if the source and destination types match;
    // false, otherwise.
    //
    static bool MatchType(DXType& source,
			     DXType& destination);

    static bool MatchType(const dx_Type source,
			     const dx_Type destination);

    //
    // Returns true if there exists a matching type in both lists.
    // Returns false otherwise.  Note that the source list is
    // semantically different from the destination list.
    //
    static bool MatchTypeLists(List& source,
				  List& destination);

    //
    // Returns an intersection list of the first two type lists
    // The returned list may be empty, and it must be deleted
    // by the client.
    //
    static List* IntersectTypeLists(List& first,
				    List& second);

    //
    // Constructor:
    //
    DXType();
    DXType(const dx_Type type);

    //
    // Destructor:
    //
    ~DXType(){}

    //
    // Sets the type value IFF the type is a base or user-defined type.
    // Returns true if successful; false, otherwise.
    //
    bool setType(const dx_Type type);

    //
    // Returns a pointer to the type name string.
    //
    const char* getName()
    {
	return this->name;
    }

    //
    // Returns the type value.
    //
    long getType()
    {
	return this->type;
    }

    //
    // DXType comparison equality operator.
    //
    bool operator==(DXType type)
    {
	return this->type == type.type;
    }

    //
    // Type bitwise AND operator.
    //
    bool operator&(DXType type)
    {
		if((this->type & type.type)==0)
			return false;
		else
			return true;
    }

    //
    // Copy the instance data from this to newt.  If newt is null allocate
    // a new DXType.   newt is returned.
    //
    DXType *duplicate(DXType *newt = NULL);

    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return "DXType";
    }
};


#endif // _DXType_h





