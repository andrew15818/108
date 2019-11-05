/*Here we define the tokens of our language*/
%{

	#include<stdio.h>
	#include "y.tab.h"
	int line_no = 1;
/*
	#define PROGRAM 1
	#define ID 2

	#define LPAR 3
	#define RPAR 4
	#define SEMICOLON 5
	#define PERIOD 6
	#define COMMA 7
	#define VAR 8
	#define COLON 9
	#define ARRAY 10
	#define LBRACKET 11
	#define RBRACKET 12

	#define NUM 13
	#define STRINGCONST 14
	#define OF 15
	#define INTEGER 16
	#define REAL 17

	#define FUNCTION 18
	#define PROCEDURE 19
	#define PBEGIN 20
	#define END 21
	#define ASSIGNOP 22


	#define IF 23
	#define THEN 24
	#define ELSE 25
	#define WHILE 26
	#define DO 27


	#define LESSTHAN 28
	#define GREATERTHAN 29
	#define LEQ 30
	#define GEQ 31
	#define EQUAL 32
	#define NOTEQUAL 33
	#define PLUS 34
	#define MINUS 35
	#define MULTIPLY 36
	#define DIVIDE 37
	#define NOT 38
	#define RANGE 39
	#define BLANK 40

	#define COMMENT 41
	#define IDENTIFIER 42

	char* code;
	char buferino[1000];
	*/
%} 

A [aA]
B [bB]
C [cC] 
D [dD]
E [eE]
F [fF]
G [gG]
H [hH]
I [iI]
J [jJ]
K [kK]
L [lL]
M [mM]
N [nN]
O [oO]
P [pP]
Q [qQ]
R [rR]
S [sS]
T [tT]
U [uU]
V [vV]
W [wW]
X [xX]
Y [yY]
Z [zZ]

%x parse_comment
%x parse_string

%%
{P}{R}{O}{G}{R}{A}{M} return PROGRAM;
{V}{A}{R}		return VAR;
{A}{R}{R}{A}{Y} return ARRAY;
{I}{F}			return IF;
{O}{F}			return OF;
{T}{H}{E}{N}	return THEN;
{E}{L}{S}{E}	return ELSE;
{W}{H}{I}{L}{E} return WHILE;
{D}{O}			return DO;
{N}{O}{T}		return NOT;
{B}{E}{G}{I}{N}	return PBEGIN;
{I}{N}{T}{E}{G}{E}{R} return INTEGER;
{R}{E}{A}{L}	return REAL;
{E}{N}{D}		return END;
{P}{R}{O}{C}{E}{D}{U}{R}{E} return PROCEDURE;
{F}{U}{N}{C}{T}{I}{O}{N} return FUNCTION;
{S}{T}{R}{I}{N}{G}  return STRING;
{A}{N}{D}		return AND;
{O}{R} 			return OR;



":=" 			return ASSIGNOP;
"<"				return LESSTHAN;
">" 			return GREATERTHAN;
"<="			return LEQ;
">="			return GEQ;
"="				return EQUAL;
"!="			return NOTEQUAL;
"+" 			return PLUS;
"-"				return MINUS;
"*"				return MULTIPLY;
"/"				return DIVIDE;		

".."			return RANGE;
" "								//deleting all the blanks	
"("				return LPAR;
")"				return RPAR;
";"				return SEMICOLON;
"."				return PERIOD;
","				return COMMA;
":"				return COLON;
"["				return LBRACKET;
"]"				return RBRACKET;
 

([a-zA-Z]|_)[a-zA-Z0-9_]*	return ID; 
[0-9]+"."?[0-9]?+(E("+"|"-")?)?[0-9]+ return NUM;
[0-9]+			return NUM;  

["][^"]*["]		return STRINGCONST; 
 
"//".*			;	
 
"/*"[^"*/"]*"*/" ;

\n				line_no++;
[\r\t]			;
.				{fprintf(stderr,"Lexical analyzer error at line %d : %s\n",line_no, yytext);} /*catchall term*/
%%

yywrap(){
/*
	fclose(yyin);
	exit(1);
	*/
	return 1;
}