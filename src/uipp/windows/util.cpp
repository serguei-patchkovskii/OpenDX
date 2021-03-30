/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/
#include <string.h>

#include <dxconfig.h>
#include "defines.h"

//
// This is used by the ASSERT macro in defines.h
// It should NOT be an Application method, because otherwise
// it requires that defines.h include Application.h.
//

int
STRLEN(char *a)
{
    if (!a) return 0;
    else return strlen(a);
}

int
STRCMP(char *a, char *b)
{
    if (!a || !b) 
        if (!a) return strcmp("", b);
	else return strcmp(a, "");
    else return strcmp(a, b);
}

int
STRNCMP(char *a, char *b, int n)
{
    if (!a || !b) 
        if (!a) return strncmp("", b, n);
	else return strncmp(a, "", n);
    else return strncmp(a, b, n);
}

#if !defined(HAVE_STRRSTR)
extern "C"
char *
strrstr(char *a, char *b)
{
    char *l, *n;
    l = strstr(a, b);
    if (l)
    {
	while ( (n = strstr(l+1, b)) )
	    l = n;
    }
    return l;
}
#endif

// The following is how to convert String to Char* from .NET
//
//char * StringToChar(System::String __gc *a) {
//	char* str = NULL;
//	str = new char[a->Length + 1];
//	strncpy(str, 
//		(const char*) (Marshal::StringToHGlobalAnsi(a)).ToPointer(),
//		a->Length);
//	str[a->Length] = '\0';
//	return str;
//}