/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/


%{
#include <math.h>
#include <string.h>
#include <dx/dx.h>
#include "_compute.h"
#include "_compputils.h"
#include "_compoper.h"


int _dxdparseError = 0;		/* Only shared with _compputils.c */
PTreeNode * _dxfMakeFunCall(char *func, PTreeNode *args);


%}

%start top

%union {
#define MAX_PARSE_STRING_SIZE 512
    char s[MAX_PARSE_STRING_SIZE];
    int i;
    float f;
    double d;
    PTreeNode *a;
}

/* terminal symbols */

%pure_parser
%name-prefix="_dxfcc"

%token <s> T_NAME
%token <f> T_FLOAT
%token <d> T_DOUBLE
%token <i> T_INT
%token <i> T_INPUT
%token <s> T_ID
%token <s> T_STRING

%token T_EOF
%token T_LPAR	/* '(' */
%token T_RPAR	/* ')' */
%token T_LBRA	/* '{' */
%token T_RBRA	/* '}' */
%token T_LSQB	/* '[' */
%token T_RSQB	/* ']' */
%token T_COMMA	/* ',' */
%token T_PERIOD	/* '.' */
%token T_COLON	/* ':' */

%token T_LOR    /* '||' */
%token T_LAND	/* '&&' */
%token T_LNOT	/* '!' */

%token T_LT	/* '<' */
%token T_LE	/* '<=' */
%token T_GT	/* '>' */
%token T_GE	/* '>=' */
%token T_EQ	/* '!' */
%token T_NE	/* '!=' */

%token T_QUEST	/* '?' */
%token T_COLON	/* ':' */

%token T_CROSS	/* cross */
%token T_DOT	/* dot */
%token T_PLUS	/* '+' */
%token T_MINUS	/* '-' */
%token T_EXP	/* '**' */
%token T_TIMES	/* '*' */
%token T_DIV	/* '/' */
%token T_MOD	/* '%' */

%token T_ASSIGN /* '=' */
%token T_SEMI   /* ';' */
/*
 * typed non-terminal symbols
 */
%type <a> top
%type <a> expr
%type <a> statement_list
%type <a> constant real
%type <a> list
%type <a> optional_argument_list argument_list

/*
 * precedence table
 */

%right T_ASSIGN
%right T_QUEST T_COLON
%left T_LOR
%left T_LAND
%left T_LNOT
%left T_EQ T_NE
%left T_LT T_GT T_LE T_GE
%left T_PLUS T_MINUS
%left T_CROSS
%left T_TIMES T_DIV T_MOD
%left T_DOT
%left T_EXP
%right T_PERIOD
%right U_MINUS U_PLUS 		/* unary minus, plus */
%right U_LNOT 			/* logical not (!) */

%%

top
	: { _dxdparseError = 0; }
	  statement_list T_EOF
	{
	    if (_dxdparseError)
	    {
		if ($2) {
		    _dxfComputeFreeTree($2);
		}
		_dxdcomputeTree = NULL;
		YYABORT;
	    }

	    _dxdcomputeTree = _dxfMakeList(NT_TOP, $2);
	    YYACCEPT;
	}
	;

statement_list
	: expr
	{
	    $$->next = NULL;
	}
	| T_SEMI statement_list
	{
	    $$ = $2;
	}
	| statement_list T_SEMI expr
	{
	    PTreeNode *t = $1;
	    while (t->next != NULL)
		t = t->next;
	    t->next = $3;
	    $$ = $1;
	}
	| statement_list T_SEMI 
	{
	    PTreeNode *t = $1;
	    while (t->next != NULL)
		t = t->next;
	    t->next = NULL;
	    $$ = $1;
	}
	;

expr
	: T_INPUT
	{
	    $$ = _dxfMakeInput($1);
	}
	| expr T_PERIOD constant
	{
	    $$ = _dxfMakeBinOp(OPER_PERIOD, $1, $3);
	}
	| expr T_PERIOD T_NAME
	{
	    PTreeNode *pt;
	    pt = _dxfMakeArg(NT_CONSTANT);
	    pt->metaType.items = 1;
	    pt->metaType.type = TYPE_INT;
	    pt->metaType.category = CATEGORY_REAL;
	    if (strcmp ($3, "x") == 0) {
		pt->u.i = 0;
	    }
	    else if (strcmp ($3, "y") == 0) {
		pt->u.i = 1;
	    }
	    else if (strcmp ($3, "z") == 0) {
		pt->u.i = 2;
	    }
	    else {
		DXSetError(ERROR_BAD_PARAMETER, "#12100",
		    "syntax error");
		_dxdparseError++;
		YYERROR;
	    }
	    $$ = _dxfMakeBinOp(OPER_PERIOD, $1, pt);
	}
	| constant
	| T_LPAR expr T_RPAR
	{
	    $$ = $2;
	}
	| T_LSQB list T_RSQB
	{
	    $$ = _dxfMakeList (NT_CONSTRUCT, $2);
	}
	| T_NAME T_LPAR
	  optional_argument_list T_RPAR
	{
	    /* It must be a function id */
	    if (_dxfComputeLookupFunction ($1) == NT_ERROR) {
		DXSetError(ERROR_BAD_PARAMETER, "#12090", $1);
		_dxdparseError++;
		YYERROR;
	    }
	    else
	    {
		$$ = _dxfMakeFunCall($1, $3);
		if ($$ == NULL) {
		    _dxdparseError++;
		    YYERROR;
		}
	    }
	}
	| T_MOD T_LPAR
	  optional_argument_list T_RPAR
	{
	    $$ = _dxfMakeFunCall("mod", $3);
	    if ($$ == NULL) {
		_dxdparseError++;
		YYERROR;
	    }
	}
	| T_DOT T_LPAR
	  optional_argument_list T_RPAR
	{
	    $$ = _dxfMakeFunCall("dot", $3);
	    if ($$ == NULL) {
		_dxdparseError++;
		YYERROR;
	    }
	}
	| T_CROSS T_LPAR
	  optional_argument_list T_RPAR
	{
	    $$ = _dxfMakeFunCall("cross", $3);
	    if ($$ == NULL) {
		_dxdparseError++;
		YYERROR;
	    }
	}
        | expr T_QUEST expr T_COLON expr
        {
            $$ = _dxfMakeConditional($1, $3, $5);
        }
	| expr T_LAND expr
        {
            $$ = _dxfMakeBinOp(OPER_AND, $1, $3);
        }
        | expr T_LOR expr
        {
            $$ = _dxfMakeBinOp(OPER_OR, $1, $3);
        }
        | expr T_GT expr
        {
            $$ = _dxfMakeBinOp(OPER_GT, $1, $3);
        }
        | expr T_GE expr
        {
            $$ = _dxfMakeBinOp(OPER_GE, $1, $3);
        }
        | expr T_LT expr
        {
            $$ = _dxfMakeBinOp(OPER_LT, $1, $3);
        }
        | expr T_LE expr
        {
            $$ = _dxfMakeBinOp(OPER_LE, $1, $3);
        }
        | expr T_EQ expr
        {
            $$ = _dxfMakeBinOp(OPER_EQ, $1, $3);
        }
        | expr T_NE expr
        {
            $$ = _dxfMakeBinOp(OPER_NE, $1, $3);
        }
	| expr T_PLUS expr
	{
	    $$ = _dxfMakeBinOp(OPER_PLUS, $1, $3);
	}
	| expr T_MINUS expr
	{
	    $$ = _dxfMakeBinOp(OPER_MINUS, $1, $3);
	}
	| expr T_TIMES expr
	{
	    $$ = _dxfMakeBinOp(OPER_MUL, $1, $3);
	}
	| expr T_DIV expr
	{
	    $$ = _dxfMakeBinOp(OPER_DIV, $1, $3);
	}
	| expr T_MOD expr
	{
	    $$ = _dxfMakeBinOp(OPER_MOD, $1, $3);
	}
	| expr T_DOT expr
	{
	    $$ = _dxfMakeBinOp(OPER_DOT, $1, $3);
	}
	| expr T_CROSS expr
	{
	    $$ = _dxfMakeBinOp(OPER_CROSS, $1, $3);
	}
	| expr T_EXP expr
	{
	    $$ = _dxfMakeBinOp(OPER_EXP, $1, $3);
	}
	| T_MINUS expr %prec U_MINUS
	{
	    $$ = _dxfMakeUnOp(OPER_MINUS, $2);
	}
	| T_PLUS expr %prec U_PLUS
	{
	    $$ = $2;
	}
	| T_LNOT expr %prec U_LNOT
	{
	    $$ = _dxfMakeUnOp (OPER_NOT, $2);
	}
	| T_NAME T_ASSIGN expr
	{
	    $$ = _dxfMakeAssignment ($1, $3);
	}
	| T_NAME
	{
	    $$ = _dxfMakeVariable ($1);
	}
	;

optional_argument_list
	: /* no actual arguments */
	{
	    $$ = NULL;
	}
	| argument_list
	;

argument_list
	: expr
	{
	    $$->next = NULL;
	}
	| argument_list T_COMMA expr
	{
	    PTreeNode *t = $1;
	    while (t->next != NULL)
		t = t->next;
	    t->next = $3;
	    $$ = $1;
	}
	;


list
	: expr
	{ 
	    $$->next = NULL;
	}
	| list T_COMMA expr
	{
	    PTreeNode *t = $1;
	    while (t->next != NULL)
		t = t->next;
	    t->next = $3;
	    $$ = $1;
	}
	/*
	 * This adds shift/reduce conflicts caused by: [a + b] being
	 * either [ a (+b) ] or [ (a+b) ], therefore commas are
	 * required.
	 * | list expr
	 * {
	 *    OPRL_APPEND ($1->oper, $2);
	 * }
	 */
	;
constant
	: real
	;

real
	: T_INT
	{
	    $$ = _dxfMakeArg(NT_CONSTANT);
	    $$->metaType.items = 1;
	    $$->metaType.type = TYPE_INT;
	    $$->metaType.category = CATEGORY_REAL;
	    $$->u.i = $1;
	}
	| T_FLOAT
	{
	    $$ = _dxfMakeArg(NT_CONSTANT);
	    $$->metaType.items = 1;
	    $$->metaType.type = TYPE_FLOAT;
	    $$->metaType.category = CATEGORY_REAL;
	    $$->u.f = $1;
	}
	| T_DOUBLE
	{
	    $$ = _dxfMakeArg(NT_CONSTANT);
	    $$->metaType.items = 1;
	    $$->metaType.type = TYPE_DOUBLE;
	    $$->metaType.category = CATEGORY_REAL;
	    $$->u.d = $1;
	}
	| T_STRING
	{
	    $$ = _dxfMakeArg(NT_CONSTANT);
	    $$->metaType.items = 1;
	    $$->metaType.type = TYPE_STRING;
	    $$->metaType.category = CATEGORY_REAL;
	    $$->metaType.rank = 1;
	    $$->metaType.shape[0] = strlen($1)+1;
	    strcpy($$->u.s, $1);
	}
	;

%%

int yyerror(char *s)
{
    if (DXGetError() == ERROR_NONE) {
	DXSetError(ERROR_BAD_PARAMETER, "#12100", s, _dxfcclexerror());
    }
    _dxdparseError++;
    return 0;            /*  Return a value to keep the compiler happy  */
}
