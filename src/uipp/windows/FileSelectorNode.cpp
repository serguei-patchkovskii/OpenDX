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

#include "FileSelectorNode.h"
#include "FileSelectorInstance.h"
#include "ErrorDialogManager.h"

//
// The Constructor... 
//
FileSelectorNode::FileSelectorNode(NodeDefinition *nd, Network *net, int instnc) :
                        ValueNode(nd, net, instnc)
{ 
}

//
// Destructure: needs to delete all its instances. 
//
FileSelectorNode::~FileSelectorNode()
{
}

InteractorInstance* FileSelectorNode::newInteractorInstance()
{
    FileSelectorInstance *ii;

    ii = new FileSelectorInstance(this);

    return ii;
}
//
// Print the file filter comment 
//
bool FileSelectorNode::cfgPrintInstanceAuxInfo(FILE *f,
					InteractorInstance *ii)
{
    FileSelectorInstance *fsi = (FileSelectorInstance*)ii;
    const char *filter = fsi->getFileFilter();

    if (!this->ValueNode::cfgPrintInstanceAuxInfo(f,ii))
	return false;

    if (filter && (fprintf(f,"// filter = %s\n",filter) < 0))
	return false;
    return true;
}
//
// Parse the file filter and all the super class's comments.
//
bool FileSelectorNode::cfgParseComment(const char *comment,
			const char *filename, int lineno)
{
    if (!EqualSubstring(comment," filter = ",10)) 
	return this->ValueNode::cfgParseComment(comment,filename,lineno);
   
    int instance = this->getInstanceCount();
    FileSelectorInstance *fsi = (FileSelectorInstance*)
					this->getInstance(instance);
    if (!fsi) {
        ErrorMessage("'filter' comment out of order (file %s, line%d)",
                        filename, lineno);
	// Return true though since we acknowledged the comment.
    } else  {
        fsi->setFileFilter(comment + 10);
    }
    return true;
}
//
// We implement this for FileSelector node so that we can keep the
// 2nd output (the basename of the full file name) up to date.
// One should never use this method to set the 2nd output, only the 1st.
// Well, this is used when we parse a .net file.
//
dx_Type FileSelectorNode::setOutputValue(
                                int indx,
                                const char *value,
                                dx_Type t,
                                bool send)
{
	char *localValue = DuplicateString(value);
	for (int i=0; i<strlen(localValue); i++) 
	    if (localValue[i] == '\\')
		localValue[i] = '/';

    if (indx == 2)
	return this->ValueNode::setOutputValue(2,localValue,t,send);

    dx_Type type = this->ValueNode::setOutputValue(1,localValue,t,false);
    if (type != DXType::UndefinedType) {
	char *basename = (char*)this->getOutputValueString(1);
	basename = DuplicateString(basename);
#ifdef DXD_NON_UNIX_DIR_SEPARATOR
	for (int i=0; i<strlen(basename); i++) {
	    if (basename[i] == '\\')
		basename[i] = '/';
	}
#endif
	char *p = strrchr(basename,'/');
	if (!p) {
	    type = this->ValueNode::setOutputValue(2,value,type,send);
	} else {
	    char *c;
	    p++;
	    c = strchr(p,(int)'"');
	    *c = '\0';
	    type = this->ValueNode::setOutputValue(2,p,type,send);
	}
	delete basename;
    }
    return type;
}

//
// Determine if this node is of the given class.
//
bool FileSelectorNode::isA(Symbol classname)
{
    Symbol s = theSymbolManager->registerSymbol(ClassFileSelectorNode);
    if (s == classname)
	return true;
    else
	return this->ValueNode::isA(classname);
}
