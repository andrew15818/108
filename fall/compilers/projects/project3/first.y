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
	struct Node* node;
}

%token <Node> PROGRAM ID LPAR RPAR SEMICOLON PERIOD COMMA VAR
%token <Node> COLON ARRAY LBRACKET RBRACKET NUM STRINGCONST STRING
%token <node> OF INTEGER REAL FUNCTION PROCEDURE PBEGIN AND OR
%token <node> END ASSIGNOP IF THEN ELSE WHILE DO LESSTHAN
%token <node> GREATERTHAN LEQ GEQ EQUAL NOTEQUAL PLUS MINUS
%token <node> MULTIPLY DIVIDE NOT RANGE BLANK COMMENT IDENTIFIER

%type <node> prog identifier_list declarations subprogram_declarations
%type <node> compound_statement type standard_type subprogram_declaration
%type <node> subprogram_head arguments parameter_list optional_var
%type <node> optional_statements statement_list statement variable expression
%type <node> procedure_statement tail expression_list boolexpression simple_expression
%type <node> term factor addop mulop relop

%%
//$$ is the left side of the equation, $1,$i,... are the following items in each production
/*grammar file doesnt't specify wheter | between each thing here*/
/*I hope I am getting these declarations right at least :'(*/
prog : PROGRAM ID LPAR identifier_list RPAR SEMICOLON declarations 
	subprogram_declarations
	compound_statement
	PERIOD{
		root  = newNode(PROGRAM_NODE);	
		addNewChild(root, $2);
		addNewChild(root, $4);
		addNewChild(root, $7);
		addNewChild(root, $8);
		addNewChild(root, $9);
		deleteNode($1);
		deleteNode($3);
		deleteNode($5);
		deleteNode($6);
		deleteNode($10);
	  }
;

identifier_list : ID {
		$$ = newNode(ID_NODE);	
		addNewChild($$, $1);
	  }
| identifier_list COMMA ID{
		$$ = $1;			
		addChild($$, $3);
		deleteNode($2);	
	  }
;

declarations : declarations VAR identifier_list COLON type SEMICOLON{
		//$$ = $1;
		addNewChild($$, $2);
		addNewChild($$, $3);
		addNewChild($$, $5);
		deleteNode($4);
		deleteNode($6);
	  }
| /* empty */{
		$$ = newNode(SUBPROGRAM_NODE);	
	  }
;

type : standard_type{
		$$ = newNode(TYPE_NODE);
		addNewChild($$, $1);
	  }
		//not so sure about setting $$ to $8
| ARRAY LBRACKET NUM RANGE NUM RBRACKET OF type{
		$$ = $8	 			
		addNewChild($$, $1);	
		addNewChild($$, $3);
		addNewChild($$, $5);
		deleteNode($2);
		deleteNode($4);
		deleteNode($6);
		deleteNode($7);
	  }
;

standard_type : INTEGER{
		$$ = newNode(TYPE_DECLARATION_NODE); 
		$$->type = INTEGER_NODE; 
	  }
| REAL{
		$$ = newNode(TYPE_DECLARATION_NODE);
		$$->type = REAL_NODE;
	  }
	  
| STRINGCONST {
		$$ = newNode(TYPE_DECLARATION_NODE);	
		$$->type = STRINGCONST_NODE;
	  }
;
/*also not to sure about this one*/
subprogram_declarations : subprogram_declarations
						subprogram_declaration SEMICOLON{
		$$ = $1;		
		addNewChild($$, $2);
		deleteNode($3);
	  }
| /* empty */ {
	//am I even sure I exist? :'(
		$$ = newNode(SUBPROGRAM_DECLARATIONS_NODE);
	  }
;

subprogram_declaration : subprogram_head
					   declarations
					   subprogram_declarations
					   compound_statement{
		$$ = newNode(SUBPROGRAM_DECLARATION_NODE);		
		addNewChild($$, $1);
		addNewChild($$, $2);
		addNewChild($$, $3);
		addNewChild($$, $4);
	  }
;

subprogram_head : FUNCTION ID arguments COLON  standard_type SEMICOLON{

	  }
| PROCEDURE ID arguments SEMICOLON{
		$$ = newNode(FUNCTION_NODE);
		addNewChild($$, $2);
		addNewChild($$, $3);
		deleteNode($1);
		deleteNode($4);
	  }
;

arguments : LPAR parameter_list RPAR{

		addNewChild($$, $2);
		deleteNode($1);
		deleteNode($3);
	  }
|/* empty */{
		$$ = newNode(ARGUMENTS_NODE);
	  } 
;

/*still not super clear on this one either*/
/*cnoflict here*/
parameter_list : optional_var identifier_list COLON  type{
		$$ = newNode(PARAMETER_LIST_NODE);
		addNewChild($$, $1);
		addNewChild($$, $2);
		addNewChild($$, $4);
		deleteNode($3);
	  }
| optional_var identifier_list COLON  type SEMICOLON  parameter_list{
		$$ = newNode(PARAMETER_LIST_NODE);
		addNewChild($$, $1);
		addNewChild($$, $2);
		addNewChild($$, $4);
		addNewChild($$, $6);
		deleteChild($3);
		deleteChild($5);
	  }
;
//will this give me trouble?
//doubt to see how it can give me any more problems
//than I already have with this assignment :'(
optional_var : VAR{
		//$$ = $1;
		addNewChild($$, $1);
	  }
| /* empty */{
		$$ = newNode(OPTIONAL_VAR_NODE);
	  } 
;

compound_statement : PBEGIN 
					optional_statements
					END{
		 $$ = newNode(COMPOUND_STATEMENT_NODE);	
		 addNewChild($2);
		 deleteNode($1);
		 deleteNode($3);
	  }
; 
//when should I just pass $$ = $1 or do
//I create a unique node type for everything?
optional_statements : statement_list{
		$$ = newNode(OPTIONAL_STATEMENT_NODE);
		addNewChild($1);
	  }
;


statement_list : statement{
		addNewChild($$, $1);
	  }

|statement_list SEMICOLON statement{
 		$$ = $1;
		addNewChild($$, $3);
		deleteNode($2);
	  }
;

statement : variable ASSIGNOP expression{
		 //$$ = newNode(STATEMENT_NODE);	
		 addNewChild($$, $1);
		 addNewChild($$, $2);
		 addNewChild($$, $3);
	  }
| procedure_statement{
		//$$ = newNode(STATEMENT_NODE);
		addNewChild($$, $1);
	  }
| compound_statement{
		//$$ = newNode(STATEMENT_NODE);
		addNewChild($$, $1);	
	  }
//do we only have an assignment with repeated non-terminals?
| IF expression THEN statement ELSE statement{
		//$$ = newNode(STATEMENT_NODE); 
		$$ = $6;
		addNewChild($$, $1);
		addNewChild($$, $2);
		addNewChild($$, $3);
		addNewChild($$, $4);
		addNewChild($$, $5);
		//addNewChild
	  }
| WHILE expression DO statement{
		//$$ = addNewChild(STATEMENT_NODE);
		$$ = $4;
		addNewChild($$, $1);
		addNewChild($$, $2);
		addNewChild($$, $3);
		//addNewChild($$, $4);
	  }
| /* empty */ {
		$$ = newNode(STATEMENT_NODE);
	  }
;

variable : ID tail{
		 $$ = newNode(VARIABLE_NODE);
		 addNewChild($$, $1);
		 addNewChild($$, $2);
	  }
;

tail : LBRACKET expression RBRACKET tail{
		addNewNChild($$, $2);
		addNewChild($$, $4);
		deleteNode($1);
		deleteNode($3);
	  }
| /* empty */ {
		$$ = newNode(TAIL_NODE);	
	  }
;
procedure_statement :  ID{
		$$ = newNode(PROCEDURE_STATEMENT_NODE);
		addNewChild($$, $1);
	  }
| ID LPAR expression_list RPAR{
		addNewChild($$, $1);
		addNewChild($$, $3);
		deleteNode($2);
		deleteNode($4);
	  }
;

expression_list : expression{
		addNewChild($$, $1);
	  }
| expression_list COMMA  expression{
		$$ = $1;
		addNewChild($$, $3);
		deleteNode($2);
	  }
;


expression : boolexpression{
		$$ = newNode(EXPRESSION_NODE); 
	  } 
| boolexpression AND boolexpression{
		addNewChild($$, $1);
		addNewChild($$, $2);
		addNewChild($$, $3);
	  }
| boolexpression OR boolexpression{
		addNewChild($$, $1);
		addNewChild($$, $2);
		addNewChild($$, $3);
	  }
;


boolexpression : simple_expression{
		$$ = newNode(BOOLEXPRESSION_NODe);
		addNewChild($$, $1);
	  }
| simple_expression relop simple_expression{
		addNewChild($$, $1);
		addNewChild($$, $2);
		addNewChild($$, $3);
	  }
;

simple_expression : term{
		$$ = newNode(SIMPLE_EXPRESSION_NODE);
		addNewChild($$, $1);
	  }
| simple_expression addop term{
		$$ = $1;	
		addNewChild($$, $2);
		addNewChild($$, $3);
	  }
;

term : factor{
	 	$$ = newNode(TERM_NODE);
		addNewChild($$, $1);
  	  }
| term mulop factor{
		$$ = $1;
		addNewChild($$, $2);	
		addNewChild($$, $3);	
	  }
;

/*and another one*/
factor : ID tail{
		$$ = newNode(FACTOR_NODE);
		addNewChild($$, $1);
		addNewChild($$, $2);
	  }
| ID LPAR expression_list RPAR{
		$$ = newNode(FACTOR_NODE);
		addNewChild($$, $1);
		addNewChild($$, $3);
		deleteNode($2);
		deleteNode($4);
	  }
|  NUM{	
		$$ = newNode(FACTOR_NODE);
		addNewChild($$, $1);
	  }
| addop NUM{
		$$ = newNode(FACTOR_NODE);
		addNewChild($$, $1);
	}
| STRINGCONST{

		$$ = newNode(FACTOR_NODE);
		addNewChild($$, $1);
	} 
| LPAR expression RPAR{
		addNewChild($$,$2);
		deleteNode($1);
		deleteNode($3);
	  }
| NOT factor{
		$$ = $2;
		addNewChild($$, $1);
	  }
;

addop : PLUS {
		$$ = newNode(ADDOP_NODE);
		addNewChild($$, $1);	
	  }
| MINUS{	
		$$ = newNode(ADDOP_NODE);
		addNewChild($$, $1);	
	  }
;

mulop : MULTIPLY {
		$$ = newNode(MULOP_NODE);
		addNewNode($$, $1);
	  }

| DIVIDE{	
		$$ = newNode(MULOP_NODE);
		addNewNode($$, $1);
	  }
;

relop : LESSTHAN{
		$$ = newNode(RELOP_NODE);
		addNewNode($$, $1);
	  }
| GREATERTHAN {
		$$ = newNode(RELOP_NODE);
		addNewNode($$, $1);
	  }
| EQUAL{
		$$ = newNode(RELOP_NODE);
		addNewNode($$, $1);
	  }
| LEQ{
		$$ = newNode(RELOP_NODE);
		addNewNode($$, $1);
	  }
| GEQ{
		$$ = newNode(RELOP_NODE);
		addNewNode($$, $1);
	  }
| NOTEQUAL{
		$$ = newNode(RELOP_NODE);
		addNewNode($$, $1);
}
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
