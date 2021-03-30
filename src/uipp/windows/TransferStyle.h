/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"



#ifndef _TransferStyle_h_
#define _TransferStyle_h_

#include "Base.h"
#include "SymbolManager.h"


#define ClassTransferStyle  "TransferStyle"

//
//
// An object of this type will be added to a set stored in a Dictionary.  The purpose
// is to organize the Atom,convert_proc pairs from DragSource and DropSite objects.
// Each of them defines some set of data types he can {supply,accept}.  This mechanism
// allows folks who subclass off DragSource or DropSite to identify types they 
// understand and to associate with those types, a proc which can {un}ravel the data.
//
//

class TransferStyle: public Base {

    // P R I V A T E   P R I V A T E   P R I V A T E   P R I V A T E   
    // P R I V A T E   P R I V A T E   P R I V A T E   P R I V A T E   
    private:
	Symbol			atomName;
	bool			preferred;
//	Atom			atom;
	char 			*name;
	int			tag;

    // P R O T E C T E D   P R O T E C T E D   P R O T E C T E D   
    // P R O T E C T E D   P R O T E C T E D   P R O T E C T E D   
    protected:


    // P U B L I C   P U B L I C   P U B L I C   P U B L I C   
    // P U B L I C   P U B L I C   P U B L I C   P U B L I C   
    public:
	bool			isPreferred() { return preferred; }
//	Atom			getAtom() { return this->atom; }
	int			getTag() { return this->tag; }

	const char		*getClassName() { return ClassTransferStyle; }

	TransferStyle (int ,const char *, bool); 
	~TransferStyle();
};

#endif // _TransferStyle_h_
