/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"


//////////////////////////////////////////////////////////////////////////////
// lex.h -								    //
//                                                                          //
// Contains various string lexing routines.				    //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

#ifndef _lex_h
#define _lex_h


#include "DXStrings.h"

//
// Tells whether the specified character is a white space or not.
//
inline
bool IsWhiteSpace(const char *string, int& index)
{
    return string[index] == ' ' || string[index] == '\t';
}
inline
bool IsWhiteSpace(const char *string)
{
    return *string == ' ' || *string == '\t';
}
//
// Increments the specified index until the corresponding characters in the
// string no longer contain space characters.
//
inline
void SkipWhiteSpace(const char* string,
	       int&  index)
{
    while (IsWhiteSpace(string, index))
	index++;
}
inline
void SkipWhiteSpace(char*& p)
{
    while (IsWhiteSpace(p))
	p++;
}

#if NOT_USED
inline 
char FindWhiteSpace(const char* string, int&  index)
{
    while (string[index] AND 
	   (string[index] != ' ' AND string[index] != '\t')) index++;
    return string[index];
}
#endif
inline
char FindWhiteSpace(char*& p)
{
    while (*p AND *p != ' ' AND *p != '\t') p++;
    return *p;
}

bool IsAllWhiteSpace(const char *string);

//
// Returns true if an integer string is found; returns false, otherwise.
// The index variable is updated to the character following the lexed
// string upon successful return.
//
bool IsEndOfString(const char* string,
		      int&        index);

//
// Returns true if an integer string is found; returns false, otherwise.
// The index variable is updated to the character following the lexed
// string upon successful return.
//
bool IsInteger(const char* string,
		  int&        index);

//
// Returns true if a flag string is found; returns false otherwise.
// The index variable is updated to the character following the lexed
// string upon successful return.
//
bool IsFlag(const char* string,
	       int&        index);

//
// Returns true if a scalar string is found; returns false otherwise.
// The index variable is updated to the character following the lexed
// string upon successful return.
//
bool IsScalar(const char* string,
		 int&        index);
//
// Returns true if a "string" string is found; returns false otherwise.
// The index variable is updated to the character following the lexed
// string upon successful return.
//
bool IsString(const char* string,
		 int&        index);

//
// Returns true if an identifier string is found; returns false otherwise.
// The index variable is updated to the character following the lexed
// string upon successful return.
//
bool IsIdentifier(const char* string,
		     int&        index);
//
// Returns true if the string is an identifier; returns false otherwise.
//
bool IsIdentifier(const char* string);

//
// Returns true if a restricted identifier string is found; returns false
// otherwise.  A restricted identifier does not contain an underscore or "@".
// The index variable is updated to the character following the lexed
// string upon successful return.
//
bool IsRestrictedIdentifier(const char* string,
			       int&        index);

//
// Returns true if the specified token is found; returns false otherwise.
// The index variable is updated to the character following the lexed
// string upon successful return.
//
bool IsToken(const char* string,
		const char* token,
		int&        index);

//
// Return true if the given word is a reserved word in the DX scripting
// language.
//
bool IsReservedScriptingWord(const char *word);


//
// Return true if the string matches the dxexec's expectation for a WHERE
// parameter.  For ui windows it's X{24|12|8},$(DISPLAY),##%d.  For external windows,
// it's . And for exec windows it's .  Make the index variable point to the
// first character after the end of what we considered likable.
//
bool IsWhere (const char* , int& );

#endif /* _lex_h */
