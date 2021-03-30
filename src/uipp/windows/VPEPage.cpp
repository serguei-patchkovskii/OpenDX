/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>



#include "VPEPage.h"
#include "EditorWindow.h"


VPEPage::VPEPage (const char* name, WorkSpaceInfo *info,
    EditorWindow* editor, WorkSpaceRoot* root) :
    EditorWorkSpace(name, info, editor), WorkSpacePage(root)
{
}

bool VPEPage::isA(Symbol classname)
{
    Symbol s = theSymbolManager->registerSymbol(ClassVPEPage);
    return (s == classname);
}

bool VPEPage::isA(const char* classname)
{
    Symbol s = theSymbolManager->registerSymbol(classname);
    return this->isA(s);
}

void VPEPage::saveWorkSpaceParams(WorkSpace*)
{
    this->EditorWorkSpace::saveWorkSpaceParams(this->editor->getWorkSpace());
}
