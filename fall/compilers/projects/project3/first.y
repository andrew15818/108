%{
/* * This is my first attempt * */
#include<stdio.h>
#include<stdlib.h>
//still to define this one
#include "symbolTable.h"
#include "node.h"

extern char* yytext;
extern int line_no;
void yyerror(){
	printf("Error here %d: %s\n", line_no, yytext);
}

//creating the root node from the other header files
extern struct Node* root;
%}

%union{
	//here we're supposed to add the node info from our other files
	struct Node* node;
	//int value;
	//char* symbol;
}
%token <node> PROGRAM ID LPAR RPAR SEMICOLON PERIOD COMMA VAR
%token <node> COLON ARRAY LBRACKET RBRACKET NUM STRINGCONST STRING
%token <node> OF INTEGER REAL FUNCTION PROCEDURE PBEGIN AND OR
%token <node> END ASSIGNOP IF THEN ELSE WHILE DO LESSTHAN
%token <node> GREATERTHAN LEQ GEQ EQUAL NOTEQUAL PLUS MINUS
%token <node> MULTIPLY DIVIDE NOT RANGE BLANK COMMENT IDENTIFIER
/*not sure if i should just include the following tokens*/


%%
//$$ is the left side of the equation, $1,$i,... are the following items in each production
/*grammar file doesnt't specify wheter | between each thing here*/
prog : PROGRAM {
		//struct Node* root = newNode(PROGRAM_NODE);
		//nodito->parent = node;

	}
	ID LPAR identifier_list RPAR SEMICOLON
	declarations 
	subprogram_declarations
	compound_statement
	PERIOD{fprintf(stdout, "doneso \n");}
;

identifier_list : ID 

| identifier_list COMMA ID
;

declarations : declarations VAR identifier_list COLON type SEMICOLON
| /* empty */
;

type : standard_type
| ARRAY LBRACKET NUM RANGE NUM RBRACKET OF type
;

standard_type : INTEGER 
			  {fprintf(stdout, "declaring an integer %d\n", yylval);}
| REAL
| STRINGCONST 
;

subprogram_declarations : subprogram_declarations
						subprogram_declaration SEMICOLON
| /* empty */ 
;

subprogram_declaration : subprogram_head
					   declarations
					   subprogram_declarations
					   compound_statement
;

subprogram_head : FUNCTION ID arguments COLON  standard_type SEMICOLON
| PROCEDURE ID arguments SEMICOLON
;

arguments : LPAR parameter_list RPAR
|/* empty */ 
;

/*still not super clear on this one either*/
/*cnoflict here*/
parameter_list : optional_var identifier_list COLON  type
| optional_var identifier_list COLON  type SEMICOLON  parameter_list
;

optional_var : VAR
| /* empty */ 
;

compound_statement : PBEGIN 
					optional_statements
					END 
; 

optional_statements : statement_list
;


statement_list : statement
|statement_list SEMICOLON statement
;

statement : variable ASSIGNOP expression
| procedure_statement
| compound_statement
| IF expression THEN statement ELSE statement
| WHILE expression DO statement
| /* empty */ 
;

variable : ID tail
;

tail : LBRACKET expression RBRACKET tail
| /* empty */ 
;

/*another shift-reduce conflict*/
procedure_statement :  ID
| ID LPAR expression_list RPAR
;

expression_list : expression
| expression_list COMMA  expression
;


expression : boolexpression 
| boolexpression AND boolexpression
| boolexpression OR boolexpression
;


boolexpression : simple_expression
| simple_expression relop simple_expression
;

simple_expression : term
| simple_expression addop term
;

term : factor
| term mulop factor
;

/*and another one*/
factor : ID tail
| ID LPAR expression_list RPAR
|  NUM 
| addop NUM
| STRINGCONST 
| LPAR expression RPAR
| NOT factor
;

addop : PLUS | MINUS
;

mulop : MULTIPLY | DIVIDE
;

relop : LESSTHAN
| GREATERTHAN 
| EQUAL
| LEQ 
| GEQ
| NOTEQUAL
;
/*end of grammerino*/
%%
/*
void yyeror(const char* str){
	fpritnf(stderr, "error: %s\n", str);
}

int yywrap(){
	return 1;
}
*/
int main(){
	int hola = yyparse();
	if(hola==0){
		printf("Ok.\n");
	}
	return hola;
}
