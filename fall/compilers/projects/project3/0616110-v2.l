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
	yylval.node  = newNode(PROG);	
	return PROGRAM;
}
{V}{A}{R} {
	yylval.node = newNode(VAR);
	return VAR;
}
{A}{R}{R}{A}{Y} {
		yylval.node = newNode(ARRAY);
		return ARRAY;
}
{I}{F}	{
	yylval.node = newNode(IF);
	return IF;
}
{O}{F}	{
		yylval.node = newNode(OF);
		return OF;
}
{T}{H}{E}{N} {
	yylval.node = newNode(THEN);
	return THEN;
}
{E}{L}{S}{E} {
	yylval.node = newNode(ELSE);
	return ELSE;
}
{W}{H}{I}{L}{E} {
	yylval.node = newNode(WHILE);
	return WHILE;
}
{D}{O} {			
	yylval.node = newNode(DO);
	return DO;
}
{N}{O}{T} {
	yylval.node = newNode(NOT);		
	return NOT;
}
{B}{E}{G}{I}{N}	{
	yylval.node = newNode(PBEGIN);
	return PBEGIN;
}
{I}{N}{T}{E}{G}{E}{R} {
	yylval.node = newNode(integer_type);
	return INTEGER;
}
{R}{E}{A}{L}	{
	yylval.node = newNode(real_type);
	return REAL;
}
{E}{N}{D} {
	yylval.node = newNode(END);
	return END;
}
{P}{R}{O}{C}{E}{D}{U}{R}{E} {
	//yylval.node = newNode(PROCEDURE);
	//yylval.node->name = (char*)malloc(yyleng+1);
	//strcpy(yylval.node->name, yytext);
	return PROCEDURE;
}
{F}{U}{N}{C}{T}{I}{O}{N} {
	yylval.node = newNode(FUNCTION);
	return FUNCTION;
}
{S}{T}{R}{I}{N}{G}  {
	yylval.node = newNode(string_type);
	return STRINGCONST;
}
{A}{N}{D} {
	yylval.node = newNode(AND);
	yylval.node->specificType = AND;
	return AND;
}
{O}{R} 	{
	yylval.node = newNode(OR);
	yylval.node->specificType = OR;
	return OR;
}



":=" {
	yylval.node = newNode(ASSIGNOP);
	yylval.node->specificType = op_assign;
	return ASSIGNOP;
	}
"<"	{
	yylval.node = newNode(LESSTHAN);		
	yylval.node->specificType =  op_lt;
	return LESSTHAN;
}
">" {
	yylval.node = newNode(GREATERTHAN);
	yylval.node->specificType =  op_gt;
	return GREATERTHAN;
}
"<=" {
	yylval.node = newNode(LEQ);	
	yylval.node->specificType =  op_leq;
	return LEQ;
}
">=" {			
	yylval.node = newNode(GEQ);
	yylval.node->specificType =  op_geq;
	return GEQ;
}
"="	{
	yylval.node = newNode(EQUAL);
	yylval.node->specificType =  op_equal;
	return EQUAL;
}
"!=" {
	yylval.node = newNode(NOT);	
	yylval.node->specificType =  op_nequal;
	return NOTEQUAL;
}
"+" {
	yylval.node = newNode(PLUS);
	yylval.node->specificType =  op_plus;
	return PLUS;
}
"-"	{
	yylval.node = newNode(MINUS);
	yylval.node->specificType = op_minus;
	return MINUS;
}
"*" { 				
	yylval.node = newNode(MULTIPLY);
	yylval.node->specificType = op_multiply;
	return MULTIPLY;
}
"/" {				
	yylval.node = newNode(DIVIDE);
	yylval.node->specificType = op_divide;
	return DIVIDE;
}

".." {
	yylval.node = newNode(RANGE);

	return RANGE;
}
" "								//deleting all the blanks	
"(" {				
	yylval.node = newNode(LPAREN);	
	//yylval.node->specificType = LPAR
	return LPAR;
}
")"	{
	yylval.node = newNode(RPAREN);

	return RPAR;
}
";" {				
	yylval.node = newNode(SEMICOLON);
	return SEMICOLON;
}

"."	{
	yylval.node = newNode(PERIOD);
	return PERIOD;
}
"," {
	yylval.node = newNode(COMMA);
	return COMMA;
}
":"	{
	yylval.node = newNode(COLON);
	return COLON;
}
"["	{
	yylval.node = newNode(LBRACKET);	
	return LBRACKET;
}
"]" {
	yylval.node = newNode(RBRACKET);
	return RBRACKET;
}

 

([a-zA-Z]|_)[a-zA-Z0-9_]*	{
	yylval.node = newNode(ID_name);
	yylval.node->name = (char*)malloc(yyleng + 1);
	strcpy(yylval.node->name, yytext);
	//fprintf(stdout, " name of id_node: %s\n ", yylval.node->name);
	return ID;
}
[0-9]+"."?[0-9]?+(E("+"|"-")?)?[0-9]+ {
	yylval.node = newNode(NUM);
	yylval.node->specificType = REAL_VALUE;
	return NUM;
}
[0-9]+ {
	yylval.node = newNode(NUM);	
	yylval.node->value = atoi(yytext);
	yylval.node->specificType = INTEGER_VALUE; 
	return NUM; 
}

["][^"]*["]		{
	yylval.node = newNode(STRING_VALUE);
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
