/*Here we define the tokens of our language*/
%{

	#include<stdio.h>
	#include<y.tab.h>
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
	#define BEGIN 20
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
	#define SLASH 37
	#define NOT 38
	#define RANGE 39

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
"("				return LPAR;
")"				return RPAR;
";"				return SEMICOLON;
"."				return PERIOD;
","				return COMMA;

{V}{A}{R}		return VAR:
":"				return COLON:
{A}{R}{R}{A}{Y} return ARRAY;
"["				return LBRACKET;
"]"				return RBRACKET;
[0-9]+			return NUM;


%%
