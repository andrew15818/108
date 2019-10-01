/*Here we define the tokens of our language*/
%{

	#include<stdio.h>
	//#include<y.tab.h>
	int line_no = 1;

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
	/*Next we define the character classes*/
       int comment_nesting = 0; /*the intorino we are going to use when stacking comments*/
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
{V}{A}{R}		return VAR;
{A}{R}{R}{A}{Y} return ARRAY;
{I}{F}			return IF;
{T}{H}{E}{N}	return THEN;
{E}{L}{S}{E}	return ELSE;
{W}{H}{I}{L}{E} return WHILE;
{D}{O}			return DO;
{N}{O}{T}		return NOT;
([a-zA-Z]|_)[a-zA-Z0-9_]*	return IDENTIFIER;
 /*("+"|"-")?[0-9]+"."[0-9]+|(E?[0-9]+) return REAL; Maybe need to find a better way to define REALs :(*/
("+"|"-")?[0-9]+(".")?[0-9]+(E[0-9]+)	return REAL; /*<=Start again here*/
("+"|"-")?[0-9]+			return INTEGER; 
 
 ["][^"]*["]		return STRINGCONST;
  /*
  In case the other way of parsing strings is incorrect, try this one
 "\"" {           
    BEGIN(parse_string);
 }
 
<parse_string>{
    "\"" {       
        //return STRINGCONST;
        BEGIN(INITIAL);
     }

    "\n" {         
        line_no++;
     }
}
 */


 /*Checking for comments, including multiple lines*/
"//".*			return COMMENT;
 
"/*"			{BEGIN(parse_comment);}
<parse_comment>"*/ " {BEGIN(INITIAL);}
<parse_comment>(.|%n)*;
  /* 

    comment_nesting++;
	BEGIN(parse_comment);
 }
*/
 /*		 //printf("finding nested comment at line %d\n", line_no);

*/

	/*
	"*/
	/* {
		//printf("Comment content: %s\n",yytext);
        comment_nesting--;
        if(comment_nesting<=0){
			comment_nesting=0;
            BEGIN (INITIAL);
        }
	}
	\n	line_no++;
	 /*.}	;*/


	/* Still need TODO:
	 * X1. handle stringorinos properly,allowing for properly escaped sequences
	 * 2. allo for integer decalrations as well as the values, i.e. int x = 2
	 * X3. Do mutli-line comments need to print the comment? README not clear
	*/	
 /*Regular operators*/
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
" "			/*return BLANK;   does this effectively delete whitespaces? */
"("				return LPAR;
")"				return RPAR;
";"				return SEMICOLON;
"."				return PERIOD;
","				return COMMA;
":"				return COLON;
"["				return LBRACKET;
"]"				return RBRACKET;
 
\n				line_no++;
.				{fprintf(stderr,"Lexical analyzer error at line %d : %s\n",line_no, yytext);} /*catchall term*/
%%

int main(int argc, char ** argv[]){
	int i,tok;	
	yyin = fopen("test.txt", "r");
	for(i = 0;1==1; i ++){
		tok = yylex();
		fprintf(stderr,"%3d-th token(type:%d) on line %d: %s\n", i, tok, line_no, yytext);
	}
	return(0);
}
yywrap(){
	fclose(yyin);
	exit(1);
}
