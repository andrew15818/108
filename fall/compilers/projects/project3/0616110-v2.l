/*Here we define the tokens of our language*/
%{

	#include<stdio.h>
	#include "y.tab.h"
	//#include "node.c"
	#include "symbolTable.h"
	int line_no = 1;
	extern struct Node* node(int type);

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
{P}{R}{O}{G}{R}{A}{M} {
	yylval.node  = newNode(PROGRAM_NODE);	
	return PROGRAM;
}
{V}{A}{R} {
	yylval.node = newNode(VAR_NODE);
	return VAR;
}
{A}{R}{R}{A}{Y} {
		yylval.node = newNode(ARRAY_NODE);
		return ARRAY;
}
{I}{F}	{
	yylval.node = newNode(IF_NODE);
	return IF;
}
{O}{F}	{
		yylval.node = newNode(OF_NODE);
		return OF;
}
{T}{H}{E}{N} {
	yylval.node = newNode(THEN_NODE);
	return THEN;
}
{E}{L}{S}{E} {
	yylval.node = newNode(ELSE_NODE);
	return ELSE;
}
{W}{H}{I}{L}{E} {
	yylval.node = newNode(WHILE_NODE);
	return WHILE;
}
{D}{O} {			
	yylval.node = newNode(DO_NODE);
	return DO;
}
{N}{O}{T} {
	yylval.node = newNode(NOT_NODE);		
	return NOT;
}
{B}{E}{G}{I}{N}	{
	yylval.node = newNode(BEGIN_NODE);
	return PBEGIN;
}
{I}{N}{T}{E}{G}{E}{R} {
	yylval.node = newNode(INTEGER_NODE);
	return INTEGER;
}
{R}{E}{A}{L}	{
	yylval.node = newNode(REAL_NODE);
	return REAL;
}
{E}{N}{D} {
	yylval.node = newNode(END_NODE);
	return END;
}
{P}{R}{O}{C}{E}{D}{U}{R}{E} {
	yylval.node = newNode(PROCEDURE_NODE);
	return PROCEDURE;
}
{F}{U}{N}{C}{T}{I}{O}{N} {
	yylval.node = newNode(FUNCTION_NODE);
	return FUNCTION;
}
{S}{T}{R}{I}{N}{G}  {
	yylval.node = newNode(STRING_NODE);
	return STRING;
}
{A}{N}{D} {
	yylval.node = newNode(AND_NODE);
	yylval.node->type = AND_NODE;
	return AND;
}
{O}{R} 	{
	yylval.node = newNode(OR_NODE);
	yylval.node->type = OR_NODE;
	return OR;
}



":=" {
	yylval.node = newNode(ASSIGNOP);
	yylval.node->type = ASSIGNOP;
	return ASSIGNOP;
	}
"<"	{
	yylval.node = newNode(LESS_THAN_NODE);		
	yylval.node->type =  LESS_THAN_NODE;
	return LESSTHAN;
}
">" {
	yylval.node = newNode(GREATER_THAN_NODE);
	yylval.node->type =  GREATER_THAN_NODE;
	return GREATERTHAN;
}
"<=" {
	yylval.node = newNode(LEQ_NODE);	
	yylval.node->type =  LEQ_NODE;
	return LEQ;
}
">=" {			
	yylval.node = newNode(GEQ_NODE);
	yylval.node->type =  GEQ_NODE;
	return GEQ;
}
"="	{
	yylval.node = newNode(EQUAL_NODE);
	yylval.node->type =  EQUAL_NODE;
	return EQUAL;
}
"!=" {
	yylval.node = newNode(NOT_EQUAL_NODE);	
	yylval.node->type =  NOT_EQUAL_NODE;
	return NOTEQUAL;
}
"+" {
	yylval.node = newNode(PLUS_NODE);
	yylval.node->type =  PLUS_NODE;
	return PLUS;
}
"-"	{
	yylval.node = newNode(MINUS_NODE);
	yylval.node->type = MINUS_NODE;
	return MINUS;
}
"*" { 				
	yylval.node = newNode(MULTIPLY_NODE);
	yylval.node->type = MULTIPLICATION_NODE;
	return MULTIPLY;
}
"/" {				
	yylval.node = newNode(DIVIDE_NODE);
	yylval.node->type = DIVIDE_NODE;
	return DIVIDE;
}

".." {
	yylval.node = newNode(RANGE_NODE);

	return RANGE;
}
" "								//deleting all the blanks	
"(" {				
	yylval.node = newNode(LPAREN_NODE);	
	yylval.node->type = 
	return LPAR;
}
")"	{
	yylval.node = newNode(RPAREN_NODE);

	return RPAR;
}
";" {				
	yylval.node = newNode(SEMICOLON_NODE);
	return SEMICOLON;
}

"."	{
	yylval.node = newNode(PERIOD_NODE);
	return PERIOD;
}
"," {
	yylval.node = newNode(COMMA_NODE);
	return COMMA;
}
":"	{
	yylval.node = newNode(COLON_NODE);
	return COLON;
}
"["	{
	yylval.node = newNode(LBRACKET_NODE);	
	return LBRACKET;
}
"]" {
	yylval.node = newNode(RBRACKET_NODE);
	return RBRACKET;
}

 

([a-zA-Z]|_)[a-zA-Z0-9_]*	{
	yylval.node = newNode(ID_NODE);
	yylval.node->name = (char*)malloc(yyleng + 1);
	strcpy(yylval.node->name, yytext);
	return ID;
}
[0-9]+"."?[0-9]?+(E("+"|"-")?)?[0-9]+ {
	yylval.node = newNode(NUM_NODE);
	yylval.node->specificType = REAL_NODE;
	return NUM;
}
[0-9]+ {
	yylval.node = newNode(NUM_NODE);	
	yylval.node->value = atoi(yytext);
	yylval.node->specificType = INTEGER_CONSTANT_NODE; 
	return NUM; 
}

["][^"]*["]		{
	yylval.node = newNode(STRINGCONST_NODE);
	yylval.node->name = (char*)malloc(yyleng + 1);
	strcpy(yylval.node->name, yytext);
	return STRINGCONST;
}
 
"//".*			;	
 
"/*"[^"*/"]*"*/" ;

\n				line_no++;
[\r\t]			;
.				{fprintf(stderr,"Lexical analyzer error at line %d : %s\n",line_no, yytext);} /*catchall term*/
%%

int yywrap(){
	return 1;
}
