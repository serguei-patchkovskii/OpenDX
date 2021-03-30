/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

#include <string.h> 
#include "FindStack.h"

//
// FindStackElement class definition
//
class FindStackElement
{
  friend class FindStack;

  private:

    char   name[64];		// FIXME: these should be duplicated
    char   label[64];		// FIXME: these should be duplicated
    int    instance;

  public:

    FindStackElement(char* name, int instance, char *label)
    {
        strcpy(this->name, name);
        strcpy(this->label, label);
        this->instance = instance;
    };

    ~FindStackElement() { };
};



void FindStack::push(char* name, int instance, char* label)
{
    FindStackElement* element = new FindStackElement(name, instance, label);
    this->dxc_Stack::push((const void*)element);
}

bool FindStack::pop(char* name, int* instance, char* label)
{
    FindStackElement* element;

    element = (FindStackElement*)this->dxc_Stack::pop();
    if (element) {
       strcpy(name, element->name);
       strcpy(label, element->label);
       *instance = element->instance;
       delete element;
       return (true); 
    }  

    return (false);
}
    
void FindStack::clear()
{
    FindStackElement *element;

    while ( (element = (FindStackElement *)this->dxc_Stack::pop()) )
       delete element;

    this->dxc_Stack::clear();
}

