/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"


// Base class for all other classes


#ifndef _Base_h
#define _Base_h




//
// Class name definition:
//
#define ClassBase	"Base"


//
// Class Base definition:
//
class Base
{
  protected:
    //
    // Constructor:
    //
    // Note that the constructor is protected to prevent direct instan-
    // tiation, although in this case, it is an overkill since this
    // is an official C++ abstract class because of the presence of 
    // pure virtual functions.
    //
    Base(){}

  public:

    //
    // Destructor:
    //
    // Note that the destructor is declared as virtual to ensure that
    // each derived class destructor is called even if a base class
    // pointer is pointing to a derived class.
    //
   virtual ~Base(){}

    //
    // Returns a pointer to the class object.
    //
    // NOTE: this function is required to be implemented by all subclasses.
    //
    virtual const char* getClassName() = 0;
};


#endif // _Base_h
