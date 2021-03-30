/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"


#ifndef _SaveFileDialog_h
#define _SaveFileDialog_h

#include "FileDialog.h"


//
// SaveFileDialog class definition:
//
namespace dxui {
	class SaveFileDialog : public dxui::FileDialog
	{
	private:
		char *forced_extension;

	protected:
		//static String  DefaultResources[];
		static  void ConfirmationOk(void *data);
		static  void ConfirmationCancel(void *data);

		void okFileWork(const char *string);

		//
		// Do work for okFileWork(), which implements confirmation. 
		//
		virtual void saveFile(const char *string) = 0;

		//
		// Constructor:
		//
		SaveFileDialog(const char *name, const char *ext=NULL);

		//
		// Install the default resources for this class and then call the
		// same super class method to get the default resources from the
		// super classes.
		//
		//virtual void installDefaultResources(Widget baseWidget);

	public:

		//
		// Destructor:
		//
		~SaveFileDialog();

	};
}

#endif // _SaveFileDialog_h
