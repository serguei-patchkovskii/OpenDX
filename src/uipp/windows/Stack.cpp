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
#include "Stack.h"


void dxc_Stack::push(const void *datum)
{
    this->insertElement(datum,1);  
}

const void *dxc_Stack::peek()
{
    return this->getElement(1);
}
const void *dxc_Stack::pop()
{
    const void *datum = this->peek();

    if (this->deleteElement(1))
	return datum;
    else
	return NULL;
}
    
void dxc_Stack::clear()
{
    this->List::clear();
}




