/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"



#include "lex.h"
#include "DXStrings.h"


//
// Internal state constants needed for the tensor routine:
//
#define TY_NONE			0
#define TY_VECTOR		1
#define TY_TENSOR		2


bool IsEndOfString(const char* string,
		      int&        index)
{
    int i;

    i = index;
    SkipWhiteSpace(string, i);

    if (string[i] == '\0')
    {
	index = i;
	return true;
    }
    else
    {
	return false;
    }
}


bool IsInteger(const char* string,
		  int&        index)
{
    int i;
    int j;

    //
    // Parameter validity check...
    //
    if (string == NUL(char*))
    {
	return false;
    }
    
    ASSERT(index >= 0 AND index <= STRLEN(string) + 1);

    //
    // Skip space.
    //
    i = index;
    SkipWhiteSpace(string, i);

    //
    // Lex optional minus sign.
    //
    if (string[i] == '-')
    {
	i++;
    }
    
    //
    // Lex digit(s).
    //
    for (j = i; string[j] >= '0' AND string[j] <= '9'; j++)
	;

    //
    // No digits... return unsuccessfully.
    //
    if (j == i)
    {
	return false;
    }

    //
    // Return successfully.
    //
    index = j;
    return true;
}


bool IsFlag(const char* string,
	       int&        index)
{
    int i;

    //
    // Parameter validity check...
    //
    if (string == NUL(char*))
    {
	return false;
    }
    
    ASSERT(index >= 0 AND index <= STRLEN(string) + 1);

    //
    // Skip space.
    //
    i = index;
    SkipWhiteSpace(string, i);

    //
    // Lex "true", "false", or an integer value.
    //
    if (EqualSubstring(&(string[i]), "true", 4))
    {
	i += 4;
    }
    else if (EqualSubstring(&(string[i]), "false", 5))
    {
	i += 5;
    }
    else if (NOT IsInteger(string, i))
    {
	//
	// No match; return unsuccessfully.
	//
	return false;
    }

    //
    // Return successfully.
    //
    index = i;
    return true;
}


bool IsScalar(const char* string,
		 int&        index)
{
    int i;
    int j;

    //
    // Parameter validity check...
    //
    if (string == NUL(char*))
    {
	return false;
    }
    
    ASSERT(index >= 0 AND index <= STRLEN(string) + 1);

    //
    // Skip space.
    //
    i = index;
    SkipWhiteSpace(string, i);

    //
    // Lex optional minus sign.
    //
    if (string[i] == '-')
    {
	i++;
    }
    
    //
    // Lex digit(s).
    //
    for (j = i; string[j] >= '0' AND string[j] <= '9'; j++)    
	;

    //
    // Lex decimal point.
    //
    if (string[j] == '.')
    {
	bool is_integer = (j > i);
	
	i = j + 1;

	/*
	 * Lex more digit(s).
	 */
	for (j = i; string[j] >= '0' AND string[j] <= '9'; j++)    
	    ;

	if (j == i AND NOT is_integer)
	{
	    return false;
	}

	if (string[j] != 'e' && string[j] != 'E')
	{
	    //
	    // Return successfully.
	    //
	    index = j;
	    return true;
	}
    }
    else if (j == i)
    {
	//
	// No digits... return unsuccessfully.
	//
	return false;
    }
    else if (string[j] != 'e' && string[j] != 'E')
    {
	//
	// No decimal point: an integer.  Return successfully.
	//
	index = j;
	return true;
    }

    //
    // Just lex'd the exponential sign....
    //
    i = j + 1;

    //
    // Lex optional minus sign.
    //
    if (string[i] == '+' OR string[i] == '-')
    {
	i++;
    }
    
    //
    // Lex digit(s).
    //
    for (j = i; string[j] >= '0' AND string[j] <= '9'; j++)    
	;

    //
    // No digits... return unsuccessfully.
    //
    if (j == i)
    {
	return false;
    }

    /*
     * Return successfully.
     */
    index = j;
    return true;
}


bool IsString(const char* string,
		 int&        index)
{
    int i;

    //
    // Parameter validity check...
    //
    if (string == NUL(char*))
    {
	return false;
    }
    
    ASSERT(index >= 0 AND index <= STRLEN(string) + 1);

    //
    // Skip space.
    //
    i = index;
    SkipWhiteSpace(string, i);

    //
    // Lex first quote.
    //
    if (string[i] != '"')
    {
	return false;
    }

    //
    // Find the matching end quote.
    //
    while (true)
    {
	i++;
	if ((string[i] == '\0') OR
	    ((string[i - 1] != '\\') && (string[i] == '"')))
	    break;
    }

    //
    // No end quote... return unsuccessfully.
    //
    if (string[i] != '"')
    {
	return false;
    }

    //
    // Return successfully.
    //
    index = i + 1;
    return true;
}

bool IsIdentifier(const char* string)
{
    int i = 0;

    //
    // Make sure the first character is not white space.
    //
    SkipWhiteSpace(string,i);
    if (i != 0)
	return false;

    if (string && IsIdentifier(string,i) && (i == STRLEN(string)-1)) 
	return true;
    return false;
}

bool IsIdentifier(const char* string,
		     int&        index)
{
    int i;

    //
    // Parameter validity check...
    //
    if (string == NUL(char*))
    {
	return false;
    }
    
    ASSERT(index >= 0 AND index <= STRLEN(string) + 1);

    //
    // Skip space.
    //
    i = index;
    SkipWhiteSpace(string, i);

    //
    // First character should be an alphabetic character, an undersocre, or
    // an "@" character.
    //
    if ((string[i] < 'a' OR string[i] > 'z') AND
	(string[i] < 'A' OR string[i] > 'Z') AND
	string[i] != '_' AND
	string[i] != '@')
    {
	return false;
    }

    //
    // Lex alphanumeric character(s), underscores, and "@" characters.
    //
    for (i++;
	 (string[i] >= '0' AND string[i] <= '9') OR
	 (string[i] >= 'a' AND string[i] <= 'z') OR
	 (string[i] >= 'A' AND string[i] <= 'Z') OR
	 string[i] == '_' OR
	 string[i] == '@';
	 i++)
	;

    //
    // Return successfully.
    //
    index = i;
    return true;
}


bool IsRestrictedIdentifier(const char* string,
			       int&        index)
{
    int i;

    //
    // Parameter validity check...
    //
    if (string == NUL(char*))
    {
	return false;
    }
    
    ASSERT(index >= 0 AND index <= STRLEN(string) + 1);

    //
    // Skip space.
    //
    i = index;
    SkipWhiteSpace(string, i);

    //
    // First character should be an alphabetic character, an undersocre, or
    // an "@" character.
    //
    if ((string[i] < 'a' OR string[i] > 'z') AND
	(string[i] < 'A' OR string[i] > 'Z'))
    {
	return false;
    }

    //
    // Lex alphanumeric character(s), underscores, and "@" characters.
    //
    for (i++;
	 (string[i] >= '0' AND string[i] <= '9') OR
	 (string[i] >= 'a' AND string[i] <= 'z') OR
	 (string[i] >= 'A' AND string[i] <= 'Z');
	 i++)
	;

    //
    // Return successfully.
    //
    index = i;
    return true;
}


bool IsToken(const char* string,
		const char* token,
		int&        index)
{
    int length;
    int i;

    //
    // Parameter validity check...
    //
    if (string == NUL(char*))
    {
	return false;
    }
    
    ASSERT(index >= 0 AND index <= STRLEN(string) + 1);

    //
    // Skip space.
    //
    i = index;
    SkipWhiteSpace(string, i);

    //
    // Lex token.
    //
    length = (int)STRLEN(token);
    if (EqualSubstring(&string[i], token, length))
    {
	i += (int)length;
    }
    else
    {
	return false;
    }

    //
    // Return successfully.
    //
    index = i;
    return true;
}

bool IsAllWhiteSpace(const char *string)
{
    int ndx;
    ndx = 0;
    SkipWhiteSpace(string, ndx);
    return (ndx == STRLEN(string));
}


bool IsReservedScriptingWord(const char *word)
{
    static char *ReservedScriptingWords[] = {
	// Reserved key words
	    "begin",
	    "cancel",
	    "describe",
	    "else",
	    "end",
	    "for",
	    "if",
	    "include",
	    "list",
	    "macro",
	    "print",
	    "quit",
	    "repeat",
	    "then",
	    "until",
	    "while",
	// VCR interface
	    "backward",
	    "forward",
	    "loop",
	    "off",
	    "on",
	    "palindrome",
	    "pause",
	    "play",
	    "sequence",
	    "step",
	    "stop",
	    NULL
    };      
    char *w, **p = ReservedScriptingWords;

    while ( (w = *p) ) {
        if (EqualString(w,word))
            return true;
	p++;
    }
    return false;

}

//
// It isn't really necessary to distinguish valid Where values because (as of
// 1/21/97) the Where input for Display was actually marked window or string.
// Thus something which is typed incorrectly for being a real Where param would
// still be accepted and the Display module would barf when the net executes.
//
bool IsWhere (const char* string, int& index)
{
#if defined(DONT_DEFINE_WINDOW_TYPE)
    return IsString(string, index);
#else
    int junk = index;
    if (!IsString(string, junk))
	return false;

    bool retVal = false;

    const char* dupstring = &string[1];

    if (strncmp (dupstring, "X8,,", 4) == 0) {
	index = 5;
	if (dupstring[index] == '"') {
	    index++;
	    retVal = true;
	}
    } else if (strncmp (dupstring, "x8,,", 4) == 0) {
	index = 5;
	if (dupstring[index] == '"') {
	    index++;
	    retVal = true;
	}
    } else if (strncmp (dupstring, "X12,,", 5) == 0) {
	index = 6;
	if (dupstring[index] == '"') {
	    index++;
	    retVal = true;
	}
    } else if (strncmp (dupstring, "x12,,", 5) == 0) {
	index = 6;
	if (dupstring[index] == '"') {
	    index++;
	    retVal = true;
	}
    } else if (strncmp (dupstring, "X16,,", 5) == 0) {
      index = 6;
      if (dupstring[index] == '"') {
          index++;
          retVal = true;
      }
    } else if (strncmp (dupstring, "x16,,", 5) == 0) {
      index = 6;
      if (dupstring[index] == '"') {
          index++;
          retVal = true;
      }
    } else if (strncmp (dupstring, "X24,,", 5) == 0) {
	index = 6;
	if (dupstring[index] == '"') {
	    index++;
	    retVal = true;
	}
    } else if (strncmp (dupstring, "x24,,", 5) == 0) {
	index = 6;
	if (dupstring[index] == '"') {
	    index++;
	    retVal = true;
	}
    } else if (strncmp (dupstring, "X32,,", 5) == 0) {
	index = 6;
	if (dupstring[index] == '"') {
	    index++;
	    retVal = true;
	}
    } else if (strncmp (dupstring, "x32,,", 5) == 0) {
	index = 6;
	if (dupstring[index] == '"') {
	    index++;
	    retVal = true;
	}
    } else {
	int depth;
	char dispstr[256];
	int xwid;

	int items_parsed = sscanf (dupstring, "X%d,%[^,],##%d",
		&depth, dispstr, &xwid);

	if (items_parsed != 3)
	    items_parsed = sscanf (dupstring, "x%d,%[^,],##%d",
		&depth, dispstr, &xwid);

	if (items_parsed != 3)
	    items_parsed = sscanf (dupstring, "X%d,%[^,],#X%d",
		    &depth, dispstr, &xwid);

	if (items_parsed != 3)
	    items_parsed = sscanf (dupstring, "x%d,%[^,],#x%d",
		    &depth, dispstr, &xwid);

	if (items_parsed != 3)
		items_parsed = sscanf (dupstring, "w%d,%[^,],##%d",
			&depth, dispstr, &xwid);

	if (items_parsed != 3)
		items_parsed = sscanf (dupstring, "W%d,%[^,],##%d",
			&depth, dispstr, &xwid);

	if (items_parsed == 3) {
	    if ((depth == 8) || (depth == 12) || (depth == 16) || (depth == 24)
			|| (depth == 32)) {
		index = strlen(string);
		retVal = true;
	    }
	}
    }

    return retVal;
#endif
}
