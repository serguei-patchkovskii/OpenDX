/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

#include <sys/stat.h>
#include <string.h>

#include "DXStrings.h"
#include "SaveFileDialog.h"
#include "QuestionDialogManager.h"

using namespace dxui;

class confirmation_data {
    public:
    confirmation_data() { filename=NULL; }
    ~confirmation_data() { if (this->filename) 
			delete this->filename; 
		    }
    char *filename;
    dxui::SaveFileDialog *dialog;
}; 

//String SaveFileDialog::DefaultResources[] =
//{
//        NULL
//};

using namespace dxui;

dxui::SaveFileDialog::SaveFileDialog(
		const char *name, const char *ext) : 
		FileDialog(name)
{
    if (ext)
	this->forced_extension = DuplicateString(ext);
    else
	this->forced_extension = NULL; 
}

dxui::SaveFileDialog::~SaveFileDialog()
{
    if (this->forced_extension)
	delete this->forced_extension;
}

//void SaveFileDialog::installDefaultResources(Widget  baseWidget)
//{
//    this->setDefaultResources(baseWidget, SaveFileDialog::DefaultResources);
//    this->FileDialog::installDefaultResources( baseWidget);
//}

void dxui::SaveFileDialog::ConfirmationCancel(void *data)
{
    confirmation_data *cd = (confirmation_data *)data;
    delete cd;
}
void dxui::SaveFileDialog::ConfirmationOk(void *data)
{
    confirmation_data *cd = (confirmation_data *)data;

    cd->dialog->saveFile(cd->filename);
    delete cd;
}

void dxui::SaveFileDialog::okFileWork(const char *filename)
{
    struct STATSTRUCT buffer;

    int len = STRLEN(this->forced_extension);
    char *file = new char[STRLEN(filename) + len + 1];
    strcpy(file, filename);

    // 
    // Build/add the extension
    // 
    if(len > 0)
    {
#if defined(HAVE_STRRSTR)
	const char *ext = strrstr(file, this->forced_extension);
#else
	const char *nxt, *ext = strstr(file, this->forced_extension);
	nxt = ext;
	while(nxt)
	{
	    nxt = strstr(ext+1, this->forced_extension);
	    if (nxt)
		ext = nxt;
	}
#endif

	if (!ext || (strlen(ext) != len))
	    strcat(file,this->forced_extension);
    }
    


    if (STATFUNC(file, &buffer) == 0)
	{
	confirmation_data *cd = new confirmation_data;
	cd->dialog = this;
	cd->filename = file;
        theQuestionDialogManager->modalPost(
	    "Do you want to overwrite an existing file?",
	    "Overwrite existing file",
	    (void *)cd,
	    dxui::SaveFileDialog::ConfirmationOk,
	    dxui::SaveFileDialog::ConfirmationCancel,
	    NULL);
    } else {
        this->saveFile(file);
	delete file;
    }

}


