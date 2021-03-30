%{
/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/


#define DXD_ENABLE_SOCKET_POINTERS	/* define SFILE in arch.h, os2 */
#include <dx/dx.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#if defined(HAVE_UNISTD_H)
#include <unistd.h>
#endif
#include <string.h>
#ifndef DXD_LACKS_UNIX_UID
#include <pwd.h>
#endif

#if  defined(DXD_NON_UNIX_DIR_SEPARATOR)
#define DX_DIR_SEPARATOR ';'
#define DX_DIR_SEPARATOR_STR ";"
#else
#define DX_DIR_SEPARATOR ':'
#define DX_DIR_SEPARATOR_STR ":"
#endif

#include "exobject.h"
#include "config.h"
#include "parse.h"
#include "vcr.h"
#include "log.h"
#include "background.h"
#include "lex.h"
#include "command.h"

#include "sfile.h"

extern int	yylineno;
extern int	yycharno;
extern char	*yyText;
extern SFILE	*yyin;
extern int	yyLeng;
extern int	_dxd_exPPID;

extern int	_dxd_exRemote;


extern int 	_dxd_exUIPacket;

static int		*fnum;
static int		*linenum;
static int		*charnum;
static SFILE		**fps;
static char		**fname;

SFILE		*_dxd_exBaseFD = NULL;

int		_dxd_exParseError = 0;
node		*_dxd_exParseTree = NULL;
char		*_dxd_exParseMesg = NULL;

static int	data_len;

static int 	_pushInput	(char *name);
int		yyerror		(char *s);


#define	LIST_APPEND_CHECK(_l,_e)\
{\
    if (_l)\
	LIST_APPEND (_l, _e)\
    else\
	_dxd_exParseError = TRUE;\
}


static void one_dxrc (char *f)
{
    SFILE	*fp;

    if ((fp = fopen (f, "r")) != NULL)
    {
	fclose (fp);
	_pushInput (f);
    }
}

#define	DIFFERENT_FILES(_a,_b) \
(((_a).st_dev != (_b).st_dev) ||\
 ((_a).st_ino != (_b).st_ino) ||\
 (((_a).st_dev == 0) && ((_a).st_ino == 0)) ||\
 (((_b).st_dev == 0) && ((_b).st_ino == 0)))

void _dxf_ExReadDXRCFiles ()
{
    struct passwd	*pass;
    char		buf [1024];
    struct stat		curr;				/* local dir */
    struct stat		home;				/* home  dir */
    struct stat		sys;				/* system dir */
    struct stat		sys2;				/* system dir */
    int			n;
    char		*root;

    /*
     * Since the inputs get stacked we want them in reverse order.
     *
     * We use the stat calls to make sure that we don't include an init
     * file twice.  This could occur previously if $HOME == current dir,
     * etc.
     */

    /* If we are connected to the UI then this is called from the command
     * to get a license. The linefeed from the license command gets read
     * by the include in the dxrc system file. When we return we don't read
     * the linefeed from the license command and our char ptr is not reset.
     * this will cause a syntax error if the next command is a "$" command.
     */
    if(_dxd_exRemote)
        yycharno = 0;

    curr.st_dev = curr.st_ino = 0;
    home.st_dev = home.st_ino = 0;
    sys .st_dev = sys .st_ino = 0;

    buf[0] = '\0';

    if (getcwd (buf, 1022) == NULL)
	buf[0] = '\0';

    n = strlen (buf);
    sprintf (&buf[n], "/%s", DXRC);
    stat (buf, &curr);

    one_dxrc (DXRC);					/* local dir */

#if DXD_LACKS_UNIX_UID
    sprintf(buf, "C:\\%s", DXRC);
    stat(buf, &home);
    if(DIFFERENT_FILES (curr, home))
	one_dxrc (buf);					/* home dir */

#else
    if ((pass = getpwuid (geteuid ())) != NULL)
    {
	sprintf (buf, "%s/%s", pass->pw_dir, DXRC);
	stat (buf, &home);

	if (DIFFERENT_FILES (curr, home))
	    one_dxrc (buf);				/* home dir */
    }
#endif

    if ((root = (char *) getenv ("DXROOT")) != NULL)
    {
	sprintf (buf, "%s/%s", root, DXRC);
	stat (buf, &sys);

	if (DIFFERENT_FILES (curr, sys) &&
	    DIFFERENT_FILES (home, sys))
	    one_dxrc (buf);				/* system */

	sprintf (buf, "%s/lib/%s", root, SYSDXRC);
	stat (buf, &sys2);
        
	if (DIFFERENT_FILES (curr, sys2) &&
	    DIFFERENT_FILES (home, sys2) &&
	    DIFFERENT_FILES (sys, sys2))
	    one_dxrc (buf);				/* 2nd system */

    }
}


Error
_dxf_ExParseInit (char *name, SFILE *sf)
{
    int i;

    if (_dxf_ExInitLex() != OK)
	return (ERROR);

    fnum	= (int *)   DXAllocate (sizeof (int));
    linenum	= (int *)   DXAllocate (sizeof (int)    * MAXINCLUDES);
    charnum	= (int *)   DXAllocate (sizeof (int)    * MAXINCLUDES);
    fps		= (SFILE **)DXAllocate (sizeof (SFILE *)* MAXINCLUDES);
    fname	= (char **) DXAllocate (sizeof (char *) * MAXINCLUDES);

    if (fnum == NULL || linenum == NULL || charnum == NULL ||
	fps == NULL || fname == NULL)
	return (ERROR);

    for (i = 0; i < MAXINCLUDES; i++)
	if ((fname[i] = (char *) DXAllocate (sizeof (char) * 128)) == NULL)
	    return (ERROR);

    *fnum = 0;
    linenum[*fnum] = 1;
    charnum[*fnum] = 0;
    strcpy (fname[*fnum], name);
    fps[*fnum] = sf;
    yyin = fps[*fnum];
    _dxd_exBaseFD = sf;

    /*
     * can do .rc file processing here.
     * Unlicensed PC's will always load dxrc files here since they don't get "license" message.
     */
    _dxf_ExReadDXRCFiles ();

    return (OK);
}

#if 0
_parseCleanup()
{
    int i;

    /* close stdin */
    fclose (fps[0]);

    DXFree((Pointer) fnum);
    DXFree((Pointer) linenum);
    DXFree((Pointer) charnum);
    DXFree((Pointer) fps);

    for (i=0; i < MAXINCLUDES; i++)
	DXFree((Pointer)fname[i]);
    DXFree((Pointer)fname);

    _dxf_ExCleanupLex();
}
#endif


typedef struct
{
    char	*path;
    int		len;
} IPath;

void
_dxf_ExBeginInput()
{
    yyin = fps[*fnum];
    yylineno = linenum[*fnum];
    yycharno = charnum[*fnum];
}

void
_dxf_ExEndInput()
{
    linenum[*fnum] = yylineno;
    charnum[*fnum] = yycharno;
}


static int
_pushInput (char *name)
{
    static int		initme = TRUE;
    static int		npaths = 0;
    static IPath	*ipaths	= NULL;
    int			i;
    int			len;
    SFILE		*sf;
    FILE		*fptr;
    char		buf[4096];

    while (initme)
    {
	char		*tmp1;
	char		*tmp2;
	int		size;

	buf[0] = 0;

	initme = FALSE;

	tmp1 = (char *) getenv ("DXINCLUDE");
        tmp2 = (char *) getenv ("DXMACROS");
	buf[0]='\0';
	if (tmp1 == NULL && tmp2 == NULL) 
	    break;

        if(tmp1 && *tmp1 != '\000') {
            strcpy(buf, tmp1);
            if(tmp2 && *tmp2 != '\000')
                strcat(buf, DX_DIR_SEPARATOR_STR);
        }
        if(tmp2 && *tmp2 != '\000') 
            strcat(buf, tmp2);

	tmp2 = _dxf_ExCopyStringLocal (buf);
        if (tmp2 == NULL) {
           DXWarning("Ignoring DXINCLUDE and DXMACROS environment variables\n");
           break;
        }
	for (tmp1 = tmp2, npaths = 1; *tmp1; )
	    if (*tmp1++ == DX_DIR_SEPARATOR)
		npaths++;
	size = npaths * sizeof (IPath);
	ipaths = (IPath *) DXAllocate (size);
	if (ipaths == NULL)
	{
	    DXPrintError ("Can't initialize file inclusion path");
	    break;
	}
	ExZero (ipaths, size);
	for (tmp1 = tmp2, ipaths[0].path = tmp1, i = 1; i < npaths; tmp1++)
	{
	    if (*tmp1 == DX_DIR_SEPARATOR)
	    {
		*tmp1 = '\000';
		ipaths[i++].path = tmp1 + 1;
	    }
	}
	for (i = 0; i < npaths; i++)
	    ipaths[i].len = strlen (ipaths[i].path);
    }

    if (*fnum >= MAXINCLUDES - 1)
    {
	DXPrintError ("include:  input file nesting level exceeded");
	return ERROR;
    }

    fptr = fopen (name, "r");
    for (i = 0; fptr == NULL && i < npaths; i++)
    {
	len = ipaths[i].len;
	if (len <= 0)
	    continue;
	strcpy (buf, ipaths[i].path);
#if  defined(DXD_NON_UNIX_DIR_SEPARATOR)
	buf[len] = '\\';
#else
	buf[len] = '/';
#endif
	strcpy (buf + len + 1, name);
	fptr = fopen (buf, "r");
    }

    if (fptr == NULL && getenv("DXROOT"))
    {
#if  defined(DXD_NON_UNIX_DIR_SEPARATOR)
	sprintf(buf, "%s\\lib\\%s", getenv("DXROOT"), name);
#else
	sprintf(buf, "%s/lib/%s", getenv("DXROOT"), name);
#endif
	fptr = fopen (buf, "r");
    }

    if (fptr != NULL)
    {
        sf = FILEToSFILE(fptr);

	linenum[*fnum] = yylineno;
	charnum[*fnum] = yycharno;
	(*fnum)++;
	linenum[*fnum] = 1;
	charnum[*fnum] = 0;
	strncpy (fname[*fnum], name, 128);
	fname[*fnum][127] = '\0';
	fps[*fnum] = sf;
	_dxf_ExBeginInput ();
    }
    else
    {
	DXUIMessage ("ERROR", "include:  can't open file '%s'", name);
        /* in script mode running MP you will get 2 prompts on error
         * unless you flush out the newline after the error.
         */
        if(! _dxd_exRemote)
            _dxf_ExFlushNewLine();
    }

    return OK;
}

static char PopMessage[] = "< INCLUDED FILE > ";

static int
_popInput()
{
    char	*cp;
    char	*mp;
    int		i;

    yyerror (NULL);		/* reset error file name and line number */

    if (*fnum > 0)
    {
	closeSFILE(yyin);
	yyin = fps[--(*fnum)];
	yylineno = linenum[*fnum];
	yycharno = charnum[*fnum];
				/* obliterate include file text */
	for (i = 0, cp = yyText, mp = PopMessage; i < yycharno; i++)
	    *cp++ = *mp ? *mp++ : '.';

	return (0);
    }

    return (1);
}

%}

%union
{
    char		c;
    int			i;
    float		f;
    char		*s;
    void		*v;
    node		*n;
};

/* Assign precedences to logical and arithmetic symbols */
%left   L_OR
%left   L_AND
%left   L_NOT
%left   L_EQ            L_NEQ
%left   L_LT            L_GT            L_LEQ           L_GEQ
%left   A_PLUS          A_MINUS
%left   A_TIMES         A_DIV           A_IDIV          A_MOD
%left   A_EXP

%left   U_MINUS         /* unary minus */

%pure_parser

/* Whenever we detect a lexically syntactic problem */
%token	LEX_ERROR

/* Values */
%token	V_DXTRUE
%token	V_DXFALSE

/* Other Symbols */
%token	T_EOF		/* end-of-file  */
%token	T_EOL		/* end-of-line  */
%token	T_BAR		/*	|	*/
%token	T_LPAR		/*	(	*/
%token	T_RPAR		/*	)	*/
%token	T_LBRA		/*	{	*/
%token	T_RBRA		/*	}	*/
%token	T_LSQB		/*	[	*/
%token	T_RSQB		/*	]	*/
%token	T_ASSIGN	/*	=	*/
%token	T_COMMA		/*	,	*/
%token	T_DOT		/*	.	*/
%token	T_DOTDOT	/*	..	*/
%token	T_COLON		/*	:	*/
%token	T_SEMI		/*	;	*/
%token	T_PP		/*	++	*/
%token	T_MM		/*	--	*/
%token	T_RA		/*	->	*/


/* Reserved Keywords */
%token	K_BEGIN
%token	K_CANCEL
%left	K_DESCRIBE
%left	K_ELSE
%token	K_END
%token	K_IF
%token	K_INCLUDE
%token	K_LIST
%token	K_MACRO
%token	K_PRINT
%token	K_QUIT
%token	K_THEN

/* VCR interface commands */
%token K_BACKWARD
%token K_FORWARD
%token K_LOOP
%token K_OFF
%token K_ON
%token K_PALINDROME
%token K_PAUSE
%token K_PLAY
%token K_STEP
%token K_STOP
%token K_VCR

/* Packet types */
%token P_INTERRUPT
%token P_SYSTEM
%token P_ACK
%token P_MACRO
%token P_FOREGROUND
%token P_BACKGROUND
%token P_ERROR
%token P_MESSAGE
%token P_INFO
%token P_LINQ
%token P_SINQ
%token P_VINQ
%token P_LRESP
%token P_SRESP
%token P_VRESP
%token P_DATA
%token P_COMPLETE
%token P_IMPORT
%token P_IMPORTINFO


/* Constant Types */
%token	<i> T_INT
%token	<f> T_FLOAT
%token	<s> T_STRING

/* Identifiers */
%token	<s> T_ID
%token	<s> T_EXID

%type <i> interrupt_data
%type <n> system
%type <n> system_s
%type <n> system_data
%type <n> message_data
%type <n> info_data
%type <i> l_inquiry_data
%type <i> s_inquiry_data
%type <i> v_inquiry_data
%type <i> l_response_data
%type <i> s_response_data
%type <i> v_response_data
%type <i> data_data
%type <n> ex_id_s
%type <i> message_id
%type <i> ack_data

/* Types returned by reductions */
%type <n> assignment
%type <n> attribute
%type <n> attribute_s
%type <n> attribute_s0
%type <n> attributes
%type <n> attributes_0
%type <n> argument
%type <n> argument_s
%type <n> argument_s0
%type <n> arithmetic
%type <n> background_data
%type <n> block
%type <n> complex
%type <n> constant
%type <n> error_data
%type <n> data
%type <n> empty
%type <n> ex_id
%type <n> expression
%type <n> expression_s
%type <n> f_assignment
%type <f> float
%type <f> nfloat
%type <n> formal_s0
%type <n> formal_s
%type <n> formal
%type <n> foreground_data
%type <n> function_call
%type <i> handle
%type <n> id
%type <n> id_s
%type <n> id_s0
%type <n> import_data
%type <i> int
%type <i> nint
%type <n> list
%type <n> macro
%type <n> macro_data
%type <n> nreal
%type <n> packet
%type <n> quaternion
%type <n> real
%type <n> s_assignment
%type <n> s_assignment_0
%type <n> scalar
%type <n> scalar_s
%type <n> statement
%type <n> statement_s
%type <n> statement_s0
%type <n> string
%type <n> string_s
%type <n> tensor
%type <n> tensor_s
%type <n> top
%type <n> value

%type <i> switch
%type <n> vcr

%start	start

%%

start		:
		{
		    _dxd_exParseTree  = NULL;
		    _dxd_exParseMesg  = NULL;
		    _dxd_exParseError = FALSE;
		    _dxf_ExLexInit ();
		    _dxf_ExEvaluateConstants (FALSE);
		}
		top
		{
		    if (_dxd_exParseError)
		    {
			_dxd_exParseTree = NULL;
			if (_dxd_exParseMesg != NULL)
			    yyerror (_dxd_exParseMesg);
			YYABORT;
		    }
		    else
		    {
			_dxd_exParseTree = $2;
			_dxf_ExEvaluateConstants (TRUE);
			YYACCEPT;
		    }
		}
		;

top		: statement
		| macro
		| packet
		| vcr
		| K_INCLUDE T_STRING
		{
		    _pushInput ($2);
		    DXFree ((Pointer) $2);
		    $$ = NULL;
		}
		| K_INCLUDE T_ID
		{
                    /* needed to zero out char count here because */
                    /* parser gets a bit confused                 */
                    yycharno = 0;
		    _pushInput ($2);
		    DXFree ((Pointer) $2);
		    $$ = NULL;
		}
		| K_QUIT
		{
		    *_dxd_exTerminating = TRUE;
		    _dxf_ExVCRCommand (VCR_C_FLAG, VCR_F_LOOP, 0);
		    _dxf_ExBackgroundCommand (BG_CANCEL, NULL);
		    $$ = NULL;
		}
		| T_EOF
		{
		    /* if eof on stdin, exit cleanly */
		    if (_popInput ())
		    {
                        /* if we are connected to UI kill running graph */
                        if(_dxd_exRemote) {
                            _dxf_ExExecCommandStr ("kill");
                            _dxf_ExVCRCommand (VCR_C_STOP, 0, 0);
                        }
			*_dxd_exTerminating = TRUE;
			_dxf_ExVCRCommand (VCR_C_FLAG, VCR_F_LOOP, 0);
			_dxf_ExBackgroundCommand (BG_CANCEL, NULL);
		    }
		    $$ = NULL;
		}
		| T_EOL
		{
		    $$ = NULL;
		}
		| semicolon
		{
		    $$ = NULL;
		}
		;

vcr		: K_VCR statement
		{
		    _dxf_ExEvaluateConstants (TRUE);
		    _dxf_ExVCRCommand (VCR_C_TREE, (long) $2, 0);
		    $$ = NULL;
		}
		| K_PAUSE semicolon
		{
		    _dxf_ExExecCommandStr ("kill");
		    _dxf_ExVCRCommand (VCR_C_PAUSE, 0, 0);
#if 0
                   /* let UI handle this, removed 7/20/93 */
		    _dxf_ExBackgroundCommand (BG_CANCEL, NULL);
#endif
		    $$ = NULL;
		}
		| K_PLAY semicolon
		{
		    _dxf_ExVCRCommand (VCR_C_PLAY, 0, 0);
		    $$ = NULL;
		}
		| K_STEP semicolon
		{
		    _dxf_ExVCRCommand (VCR_C_STEP, 0, 0);
		    $$ = NULL;
		}
		| K_STOP semicolon
		{
		    _dxf_ExExecCommandStr ("kill");
		    _dxf_ExVCRCommand (VCR_C_STOP, 0, 0);
#if 0
                    /* let UI handle this, removed 7/20/93 */
		    _dxf_ExBackgroundCommand (BG_CANCEL, NULL);
#endif
		    $$ = NULL;
		}
		| K_FORWARD semicolon
		{
		    _dxf_ExVCRCommand (VCR_C_DIR, VCR_D_FORWARD, 0);
		    $$ = NULL;
		}
		| K_BACKWARD semicolon
		{
		    _dxf_ExVCRCommand (VCR_C_DIR, VCR_D_BACKWARD, 0);
		    $$ = NULL;
		}
		| K_PALINDROME switch semicolon
		{
		    _dxf_ExVCRCommand (VCR_C_FLAG, VCR_F_PALIN, $2);
		    $$ = NULL;
		}
		| K_LOOP switch semicolon
		{
		    _dxf_ExVCRCommand (VCR_C_FLAG, VCR_F_LOOP, $2);
		    $$ = NULL;
		}
		;

switch		: K_ON
		{
		    $$ = TRUE;
		}
		| K_OFF
		{
		    $$ = FALSE;
		}
		;


packet	: T_BAR int T_BAR P_INTERRUPT  T_BAR int
	{
	    _dxf_ExUIPacketActive ($2, PK_INTERRUPT, $6);
	}
	T_BAR interrupt_data  T_BAR
	{
	    _dxf_ExExecCommandStr ("kill");
	    _dxf_ExVCRCommand (VCR_C_STOP, 0, 0);
	    _dxf_ExBackgroundCommand (BG_CANCEL, NULL);
	    $$ = _dxf_ExPCreatePacket (PK_INTERRUPT, $2, $6, NULL);
	}

	| T_BAR int T_BAR P_SYSTEM     T_BAR int
	{
	    _dxf_ExUIPacketActive ($2, PK_SYSTEM, $6);
	}
	T_BAR system_data     T_BAR
	{
	    $$ = NULL;
	}

	| T_BAR int T_BAR P_ACK        T_BAR int
	{
	    _dxf_ExUIPacketActive ($2, PK_ACK, $6);
	}
	T_BAR ack_data        T_BAR
	{
	    $$ = NULL;
	}

	| T_BAR int T_BAR P_MACRO      T_BAR int
	{
	    _dxf_ExUIPacketActive ($2, PK_MACRO, $6);
	}
	T_BAR macro_data      T_BAR
	{
	    $$ = _dxf_ExPCreatePacket (PK_MACRO, $2, $6, $9);
	}

	| T_BAR int T_BAR P_FOREGROUND T_BAR int
	{
	    _dxf_ExUIPacketActive ($2, PK_FOREGROUND, $6);
	}
	T_BAR foreground_data T_BAR
	{
	    $$ = _dxf_ExPCreatePacket (PK_FOREGROUND, $2, $6, $9);
	}

	| T_BAR int T_BAR P_BACKGROUND T_BAR int
	{
	    _dxf_ExUIPacketActive ($2, PK_BACKGROUND, $6);
	}
	T_BAR background_data T_BAR
	{
	    $$ = _dxf_ExPCreatePacket (PK_BACKGROUND, $2, $6, $9);
	}

	| T_BAR int T_BAR P_ERROR      T_BAR int
	{
	    _dxf_ExUIPacketActive ($2, PK_ERROR, $6);
	    data_len = $6;
	}
	T_BAR error_data      T_BAR
	{
	    $$ = NULL;
	}

	| T_BAR int T_BAR P_MESSAGE    T_BAR int
	{
	    _dxf_ExUIPacketActive ($2, PK_MESSAGE, $6);
	}
	T_BAR message_data    T_BAR
	{
	    $$ = NULL;
	}

	| T_BAR int T_BAR P_INFO       T_BAR int
	{
	    _dxf_ExUIPacketActive ($2, PK_INFO, $6);
	}
	T_BAR info_data       T_BAR
	{
	    $$ = NULL;
	}

	| T_BAR int T_BAR P_LINQ       T_BAR int
	{
	    _dxf_ExUIPacketActive ($2, PK_LINQ, $6);
	}
	T_BAR l_inquiry_data  T_BAR
	{
	    $$ = NULL;
	}

	| T_BAR int T_BAR P_SINQ       T_BAR int
	{
	    _dxf_ExUIPacketActive ($2, PK_SINQ, $6);
	}
	T_BAR s_inquiry_data  T_BAR
	{
	    $$ = NULL;
	}

	| T_BAR int T_BAR P_VINQ       T_BAR int
	{
	    _dxf_ExUIPacketActive ($2, PK_VINQ, $6);
	}
	T_BAR v_inquiry_data  T_BAR
	{
	    $$ = NULL;
	}

	| T_BAR int T_BAR P_LRESP      T_BAR int
	{
	    _dxf_ExUIPacketActive ($2, PK_LRESP, $6);
	}
	T_BAR l_response_data T_BAR
	{
	    $$ = NULL;
	}

	| T_BAR int T_BAR P_SRESP      T_BAR int
	{
	    _dxf_ExUIPacketActive ($2, PK_SRESP, $6);
	}
	T_BAR s_response_data T_BAR
	{
	    $$ = NULL;
	}

	| T_BAR int T_BAR P_VRESP      T_BAR int
	{
	    _dxf_ExUIPacketActive ($2, PK_VRESP, $6);
	}
	T_BAR v_response_data T_BAR
	{
	    $$ = NULL;
	}

	| T_BAR int T_BAR P_DATA       T_BAR int
	{
	    _dxf_ExUIPacketActive ($2, PK_DATA, $6);
	}
	T_BAR data_data       T_BAR
	{
	    $$ = NULL;
	}

	| T_BAR int T_BAR P_IMPORT     T_BAR int
	{
	    _dxf_ExUIPacketActive ($2, PK_IMPORT, $6);
	    data_len = $6;
	}
	T_BAR import_data T_BAR
	{
	    $$ = _dxf_ExPCreatePacket (PK_IMPORT, $2, $6, $9);
	}
	;

/*
 * Interrupt Data
 */

interrupt_data	: int
		;

/*
 * System Data
 */

system_data	: system_s
		;

system_s	: system
		| system_s T_COMMA system
		;

system		: id T_ASSIGN constant
		;

/*
 * Ack Data
 */

ack_data	: message_id T_COLON data
		;

/*
 * Macro Definition Data
 */

macro_data	: macro
		;

/*
 * Foreground Data
 */

foreground_data	: statement
		| vcr
		;

/*
 * Background Command Data
 */

background_data	: statement
		{
		    _dxf_ExBackgroundCommand (BG_STATEMENT, $1);
		    $$ = NULL;
		}
		| K_CANCEL
		{
		    _dxf_ExExecCommandStr ("kill");
		    _dxf_ExVCRCommand (VCR_C_STOP, 0, 0);
		    _dxf_ExBackgroundCommand (BG_CANCEL, NULL);
		    $$ = NULL;
		}
		;

/*
 * DXMessage Data
 */

message_data	: data
		;

/*
 * Information Data
 */

info_data	: data
		;

/*
 * Inquiries Data
 */

l_inquiry_data	: handle T_COLON ex_id_s
		;

s_inquiry_data	: handle T_COLON expression_s
		| handle T_COLON ex_id_s
		;

v_inquiry_data	: handle T_COLON expression_s
		| handle T_COLON ex_id_s
		;

/*
 * Response Data
 */

l_response_data	: handle T_COLON id_s0
		;

s_response_data	: handle T_COLON data
		;

v_response_data	: handle T_COLON s_assignment_0
		;

/*
 * Data Data
 */

data_data	: handle T_COLON s_assignment_0
		;

import_data	: data
                ;

/*
 * Definitions
 *
 * Rule 2 allow the '-> ()' to be omitted of there are no return values.
 */

macro		: K_MACRO   id T_LPAR formal_s0 rightparen T_RA
		               T_LPAR id_s0     rightparen
			       attributes_0 block
		{
		    $$ = _dxf_ExPCreateMacro ($2, $4, $8, $11);
		    $$->attr = $10;
		}
		| K_MACRO   id T_LPAR formal_s0 rightparen 
			       attributes_0 block
		{
		    $$ = _dxf_ExPCreateMacro ($2, $4, NULL, $7);
		    $$->attr = $6;
		}
		;

formal_s0	: empty
		| formal_s
		;

formal_s	: formal attributes_0
		{
		    $1->attr = $2;
		    LIST_CREATE ($1);
		}
		| formal_s T_COMMA formal attributes_0
		{
		    $3->attr = $4;
		    LIST_APPEND_CHECK ($1, $3);
		    if (! _dxd_exUIPacket)
			yyerrok;
		}
		;

formal		: id
		| id T_ASSIGN constant
		{
		    $1->v.id.dflt = $3;
		}
		| id T_ASSIGN A_MINUS constant %prec U_MINUS
		{
		    $1->v.id.dflt = _dxf_ExPNegateConst ($4);
		}
		;


/*
 * Block
 */

block		: T_LBRA  statement_s0 rightbracket
		{
		    $$ = $2;
		}
		;

/*
 * Statements
 */

statement_s0	: empty
		| statement_s
		;

statement_s	: statement
		{
		    LIST_CREATE ($1);
		}
		| statement_s statement
		{
		    LIST_APPEND_CHECK ($1, $2);
		    if (! _dxd_exUIPacket)
			yyerrok;
		}
		;

/*
 * Put the LIST_CREATE here for the top level (for adding loop increments).
 */

statement	: block
		| assignment    semicolon
		{
		    LIST_CREATE ($1);
		}
		| function_call semicolon
		{
		    LIST_CREATE ($1);
		}
		;


/*
 * Assignment
 */

assignment	: f_assignment
		| s_assignment
		;

f_assignment	: id_s T_ASSIGN function_call
		{
		    $$ = _dxf_ExPCreateAssign ($1, $3);
		}
		;

s_assignment	: id_s T_ASSIGN expression_s
		{
		    $$ = _dxf_ExPCreateAssign ($1, $3);
		}
		| id   T_PP
		{
		    node	*mm;
		    int		val = 1;

		    mm = _dxf_ExPCreateConst (TYPE_INT, CATEGORY_REAL,
				       1, (Pointer) &val);
		    mm = _dxf_ExPCreateArith (AO_PLUS, $1, mm);
		    EXO_reference ((EXO_Object) $1);
		    $$ = _dxf_ExPCreateAssign ($1, mm);
		}
		| id   T_MM
		{
		    node	*mm;
		    int		val = 1;

		    mm = _dxf_ExPCreateConst (TYPE_INT, CATEGORY_REAL,
				       1, (Pointer) &val);
		    mm = _dxf_ExPCreateArith (AO_MINUS, $1, mm);
		    EXO_reference ((EXO_Object) $1);
		    $$ = _dxf_ExPCreateAssign ($1, mm);
		}
		;

s_assignment_0	: empty
		| s_assignment
		;


/*
 * Attribute Structure
 */

attributes_0	: empty
		| attributes
		;

attributes	: T_LSQB attribute_s0 T_RSQB
		{
		    $$ = $2;
		}
		;

attribute_s0	: empty
		| attribute_s
		;

attribute_s	: attribute
		{
		    LIST_CREATE ($1);
		}
		| attribute_s T_COMMA attribute
		{
		    LIST_APPEND_CHECK ($1, $3);
		}
		;

attribute	: id T_COLON constant
		{
		    $$ = _dxf_ExPCreateAttribute ($1, $3);
		}
		;

/*
 * Function Call
 */

function_call	: id T_LPAR argument_s0 rightparen attributes_0
		{
		    $$ = _dxf_ExPCreateCall ($1, $3);
		    $$->attr = $5;
		}
		;

/*
 * Argument Structure
 */

argument_s0	: empty
		| argument_s
		;

argument_s	: argument
		{
		    LIST_CREATE ($1);
		}
		| argument_s T_COMMA argument
		{
		    LIST_APPEND_CHECK ($1, $3);
		    if (! _dxd_exUIPacket)
			yyerrok;
		}
		;

argument	: value
		{
		    $$ = _dxf_ExPCreateArgument (NULL, $1);
		}
		| id T_ASSIGN value
		{
		    $$ = _dxf_ExPCreateArgument ($1, $3);
		}
		;

value		: expression
		;

/*
 * Arithmetic Expressions
 */

expression_s	: expression
		{
		    LIST_CREATE ($1);
		}
		| expression_s T_COMMA expression
		{
		    LIST_APPEND_CHECK ($1, $3);
		    if (! _dxd_exUIPacket)
			yyerrok;
		}
		;

expression	: constant
		| id
		| T_LPAR expression rightparen
		{
		    $$ = $2;
		}
		| arithmetic
		;

arithmetic	: expression A_EXP   expression
		{
		    $$ = _dxf_ExPCreateArith (AO_EXP, $1, $3);
		}
		| expression A_TIMES expression
		{
		    $$ = _dxf_ExPCreateArith (AO_TIMES, $1, $3);
		}
		| expression A_DIV   expression
		{
		    $$ = _dxf_ExPCreateArith (AO_DIV, $1, $3);
		}
		| expression A_IDIV  expression
		{
		    $$ = _dxf_ExPCreateArith (AO_IDIV, $1, $3);
		}
		| expression A_MOD   expression
		{
		    $$ = _dxf_ExPCreateArith (AO_MOD, $1, $3);
		}
		| expression A_PLUS  expression
		{
		    $$ = _dxf_ExPCreateArith (AO_PLUS, $1, $3);
		}
		| expression A_MINUS expression
		{
		    $$ = _dxf_ExPCreateArith (AO_MINUS, $1, $3);
		}
		|            A_MINUS expression %prec U_MINUS
		{
		    if ($2->type == NT_CONSTANT)
			$$ = _dxf_ExPNegateConst ($2);
		    else
			$$ = _dxf_ExPCreateArith (AO_NEGATE, $2, NULL);
		}
		;

/*
 * Definitions for constant data types
 */

constant	: scalar
		| tensor
		| list
		| string
		;

list		: T_LBRA scalar_s rightbracket
		{
		    $$ = $2;
		}
		| T_LBRA tensor_s rightbracket
		{
		    $$ = $2;
		}
		| T_LBRA string_s rightbracket
		{
		    $$ = $2;
		}
		| T_LBRA nreal T_DOTDOT nreal rightbracket
		{
		    $$ = _dxf_ExPDotDotList ($2, $4, NULL);
		    _dxf_ExPDestroyNode ($2);
		    _dxf_ExPDestroyNode ($4);
		}
		| T_LBRA nreal T_DOTDOT nreal T_COLON nreal rightbracket
		{
		    $$ = _dxf_ExPDotDotList ($2, $4, $6);
		    _dxf_ExPDestroyNode ($2);
		    _dxf_ExPDestroyNode ($4);
		    _dxf_ExPDestroyNode ($6);
		}
		;

tensor_s	: tensor
		| tensor_s tensor
		{
		    $$ = _dxf_ExAppendConst ($1, $2);
		    _dxf_ExPDestroyNode ($2);
		}
		| A_MINUS tensor %prec U_MINUS
		{
		    $$ = _dxf_ExPNegateConst ($2);
		}
		| tensor_s A_MINUS tensor %prec U_MINUS
		{
		    $3 = _dxf_ExPNegateConst ($3);
		    $$ = _dxf_ExAppendConst ($1, $3);
		    _dxf_ExPDestroyNode ($3);
		}
		| tensor_s T_COMMA tensor
		{
		    $$ = _dxf_ExAppendConst ($1, $3);
		    _dxf_ExPDestroyNode ($3);
		}
		| tensor_s T_COMMA A_MINUS tensor %prec U_MINUS
		{
		    $4 = _dxf_ExPNegateConst ($4);
		    $$ = _dxf_ExAppendConst ($1, $4);
		    _dxf_ExPDestroyNode ($4);
		}
		;

tensor		: T_LSQB scalar_s T_RSQB
		{
		    $$ = _dxf_ExPExtendConst ($2);
		}
		| T_LSQB tensor_s T_RSQB
		{
		    $$ = _dxf_ExPExtendConst ($2);
		}
		;

/* Rules 3 and 4 allow negative values inside of vectors and lists */
/* Rules 5 and 6 allow commas between list and vector elements */

scalar_s	: scalar
		| scalar_s scalar
		{
		    $$ = _dxf_ExAppendConst ($1, $2);
		    _dxf_ExPDestroyNode ($2);
		}
		| A_MINUS scalar %prec U_MINUS
		{
		    $$ = _dxf_ExPNegateConst ($2);
		}
		| scalar_s A_MINUS scalar %prec U_MINUS
		{
		    $3 = _dxf_ExPNegateConst ($3);
		    $$ = _dxf_ExAppendConst ($1, $3);
		    _dxf_ExPDestroyNode ($3);
		}
		| scalar_s T_COMMA scalar
		{
		    $$ = _dxf_ExAppendConst ($1, $3);
		    _dxf_ExPDestroyNode ($3);
		}
		| scalar_s T_COMMA A_MINUS scalar %prec U_MINUS
		{
		    $4 = _dxf_ExPNegateConst ($4);
		    $$ = _dxf_ExAppendConst ($1, $4);
		    _dxf_ExPDestroyNode ($4);
		}
		;

string_s	: string
		| string_s string
		{
		    $$ = _dxf_ExAppendConst ($1, $2);
		    _dxf_ExPDestroyNode ($2);
		}
		| string_s T_COMMA string
		{
		    $$ = _dxf_ExAppendConst ($1, $3);
		    _dxf_ExPDestroyNode ($3);
		}
		;

scalar		: real
		| complex
		| quaternion
		;

nreal		: real
		| A_MINUS real
		{
		    $$ = _dxf_ExPNegateConst ($2);
		}
		;

real		: int
		{
		    $$ = _dxf_ExPCreateConst (TYPE_INT,   CATEGORY_REAL,
					1, (Pointer) &($1));
		}
		| float
		{
		    $$ = _dxf_ExPCreateConst (TYPE_FLOAT, CATEGORY_REAL,
					1, (Pointer) &($1));
		}
		;

complex		: T_LPAR nint   T_COMMA nint   rightparen
		{
		    int		c[2];

		    c[0] = $2;
		    c[1] = $4;
		    $$ = _dxf_ExPCreateConst (TYPE_INT,   CATEGORY_COMPLEX,
					1, (Pointer) c);
		}
		| T_LPAR nint   T_COMMA nfloat rightparen
		{
		    float	c[2];

		    c[0] = (float) $2;
		    c[1] = $4;
		    $$ = _dxf_ExPCreateConst (TYPE_FLOAT, CATEGORY_COMPLEX,
					1, (Pointer) c);
		}
		| T_LPAR nfloat T_COMMA nint   rightparen
		{
		    float	c[2];

		    c[0] = $2;
		    c[1] = (float) $4;
		    $$ = _dxf_ExPCreateConst (TYPE_FLOAT, CATEGORY_COMPLEX,
					1, (Pointer) c);
		}
		| T_LPAR nfloat T_COMMA nfloat rightparen
		{
		    float	c[2];

		    c[0] = $2;
		    c[1] = $4;
		    $$ = _dxf_ExPCreateConst (TYPE_FLOAT, CATEGORY_COMPLEX,
					1, (Pointer) c);
		}
		;

quaternion	: T_LPAR nint T_COMMA nint T_COMMA nint T_COMMA nint rightparen
		{
		    int		c[4];

		    c[0] = $2;
		    c[1] = $4;
		    c[2] = $6;
		    c[3] = $8;
		    $$ = _dxf_ExPCreateConst (TYPE_INT,   CATEGORY_QUATERNION,
				       1, (Pointer) c);
		}
		| T_LPAR nfloat T_COMMA nfloat T_COMMA nfloat T_COMMA nfloat rightparen
		{
		    float	c[4];

		    c[0] = $2;
		    c[1] = $4;
		    c[2] = $6;
		    c[3] = $8;
		    $$ = _dxf_ExPCreateConst (TYPE_FLOAT, CATEGORY_QUATERNION,
				       1, (Pointer) c);
		}
		;

nint		: int
		| A_MINUS int %prec U_MINUS
		{
		    $$ = - $2;
		}
		;

int		: T_INT
		;

nfloat		: float
		| A_MINUS float %prec U_MINUS
		{
		    $$ = - $2;
		}
		;

float		: T_FLOAT
		;

string		: T_STRING
		{
                    /* should this be TYPE_STRING eventually? */
		    $$ = _dxf_ExPCreateConst (TYPE_UBYTE, CATEGORY_REAL,
				       yyLeng + 1, (Pointer) $1);
		    DXFree ((Pointer) $1);
		}
		;


semicolon	: T_SEMI
		{
		    if (! _dxd_exUIPacket)
			yyerrok;
		}
		;

rightparen	: T_RPAR
		{
		    if (! _dxd_exUIPacket)
			yyerrok;
		}
		;

rightbracket	: T_RBRA
		{
		    if (! _dxd_exUIPacket)
			yyerrok;
		}
		;

id		: T_ID
		{
		    $$ = _dxf_ExPCreateId ($1);
		}
		;

ex_id		: T_EXID
		{
		    $$ = _dxf_ExPCreateExid ($1);
		}
		;

empty		:
		{
		    $$ = NULL;
		}
		;

/*
 *
 */

id_s0		: empty
		| id_s
		;

id_s		: id attributes_0
		{
		    $1->attr = $2;
		    LIST_CREATE ($1);
		}
		| id_s T_COMMA id attributes_0
		{
		    $3->attr = $4;
		    LIST_APPEND_CHECK ($1, $3);
		}
		;

ex_id_s		: ex_id
		| ex_id_s T_COMMA ex_id
		;

message_id	: int
		;

handle		: int
		;

/*
 * $$$$$ needs a function to read in the remaining bytes
 */
error_data	:
                {
		    Pointer buffer;

		    if (data_len)
		    {
		        buffer = DXAllocate (data_len + 1);
			yygrabdata (buffer, data_len);
			DXUIMessage("ERROR", buffer);
			DXFree(buffer);
		    }
		    else
		    {
			_dxd_exParseError = TRUE;
		    }
		    $$ = NULL;
		}
		;

data		:
                {
		    Pointer buffer;

		    buffer = DXAllocate (data_len + 1);
		    if (buffer)
		    {
			yygrabdata (buffer, data_len);
			$$ = _dxf_ExPCreateData (buffer, data_len);
		    }
		    else
		    {
			_dxd_exParseError = TRUE;
			$$ = NULL;
		    }
		}
		;

%%

int
yyerror (char *s)
{
    static char prevfile[256];
    static int	prevline	= -1;
    int		new_line	= FALSE;
    char	*name;
    char	buf[8192];

    if (s == NULL)
    {
	prevline    = -1;
	prevfile[0] = '\000';
	return ERROR;
    }

    if (prevline == -1)
	prevfile[0] = '\000';

    name = fname[*fnum];
    _dxd_exParseError = TRUE;

    /*
     * ALWAYS suppress multiple messages about the same line.
     */

    if (prevline != yylineno || strcmp (prevfile, name))
    {
	strncpy (prevfile, name, 255);
	prevfile[255] = '\000';
	prevline = yylineno;
	yyText[yycharno] = '\000';
	new_line = TRUE;
    }

    /*
     * Send a 1 line message to the UI with column number, actually
     * draw out an arrow when talking directly to the user.
     */


    if (new_line)
    {
	if (! isprint (yyText[yycharno - 1]))
	{
	    sprintf (buf, "%s (non-printable character 0x%x)",
		     s, yyText[yycharno - 1]);
	    s = buf;
	}

	if (_dxd_exRemote)
	{
	    DXUIMessage ("ERROR", "%s[%d,%d]:  %s:  %s",
		       name, yylineno, yycharno, s, yyText);
	}
	else
	{
	    DXUIMessage ("ERROR", "%s[%d]: %s", name, yylineno, s);
	    _dxf_ExLexError ();
	}
    }

    /* in script mode running MP you will get 2 prompts on error
     * unless you flush out the newline after the error.
     */
    if (_dxd_exUIPacket)
	_dxf_ExUIFlushPacket ();
    else if(! _dxd_exRemote)
        _dxf_ExFlushNewLine();

    return ERROR;
}
