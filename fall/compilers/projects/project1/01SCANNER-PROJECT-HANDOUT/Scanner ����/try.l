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
	/*Next we define the character classes*/
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

%%
	/* make the code more readable when you're sure it works*/
 /*(" ")+			return BLANK; */ /* does this effectively delete whitespaces? */
"("				return LPAR;
")"				return RPAR;
";"				return SEMICOLON;
"."				return PERIOD;
","				return COMMA;

{V}{A}{R}		return VAR;
":"				return COLON;
{A}{R}{R}{A}{Y} return ARRAY;
"["				return LBRACKET;
"]"				return RBRACKET;
"\"" { 			/*defining the string constant*/
				/*still incomplete*/
	register int c;
	while( (c=input()) )
	{
		if(c=='0'){
			fprintf(stderr,"Unexpected EOF in line %d\n", line_no);
		}
		else if(c=='\n'){

		}
		else if(c=='\"'){
			break; /*succcessfully closed quote*/
		}
	}
}			
[0-9]+			return INTEGER; /*I'm trying two overlapping re's for ints and floats, 
								 * if it doesn't work remember to change */
[0-9]+"."[0-9]+|(E?[0-9]+) return REAL; /*seems sketchy. Reasoning: the 'E' char is optional,
									 * if not present just consider all the other numbers.*/
":=" 			return ASSIGNOP;
{I}{F} 			return IF;
{T}{H}{E}{N} 	return THEN;
{E}{L}{S}{E}	return ELSE;
{W}{H}{I}{L}{E} return WHILE;
{D}{O}			return DO;

"<"				return LESSTHAN;
">" 			return GREATERTHAN;
"<="			return LEQ;
">="			return GEQ;
"="				return EQUAL;
"!="			return NOTEQUAL;
"+" 			return PLUS;
"-"				return MINUS;
"*"				return MULTIPLY;
"//".*\n		return COMMENT; /*This is a single- line comment, ends in either \n or EOF*/
"/"				return DIVIDE;		
{N}{O}{T}		return NOT;
".."			return RANGE;

"/*" {
	register int c;

	while( (c = input()) ){
		
		if(c == '*'){
			c=input();
			if(c == '/'){	 /*If the end of the comment is closed correctly*/
				break;
			}
			else{
				unput(c);
			}
		}		
		else if( c == '\n'){
			line_no++;
		}
		else if(c == 0){
			fprintf(stderr,"Unexpected EOF inside comment at line %d\n",line_no);
		}
	}
}


\n				line_no++;
.				{fprintf(stderr,"Lexical analyzer error at line %d\n",line_no);} /*catchall term*/
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
