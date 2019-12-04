%{
/* * This is my first attempt * */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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

%token <node> PROGRAM ID LPAR RPAR SEMICOLON PERIOD COMMA VAR
%token <node> COLON ARRAY LBRACKET RBRACKET NUM STRINGCONST STRING
%token <node> OF INTEGER REAL FUNCTION PROCEDURE PBEGIN AND OR
%token <node> END ASSIGNOP IF THEN ELSE WHILE DO LESSTHAN
%token <node> GREATERTHAN LEQ GEQ EQUAL NOTEQUAL PLUS MINUS
%token <node> MULTIPLY DIVIDE NOT RANGE BLANK COMMENT IDENTIFIER LPAREN RPAREN

%type <node> prog identifier_list declarations subprogram_declarations
%type <node> compound_statement type standard_type subprogram_declaration
%type <node> subprogram_head arguments parameter_list optional_var
%type <node> optional_statements statement_list statement variable expression
%type <node> procedure_statement tail expression_list boolexpression simple_expression
%type <node> term factor addop mulop relop

%%
/*$$ is the left side of the equation, $1,$i,... are the following items in each production*/
/*grammar file doesnt't specify wheter | between each thing here*/
/*I hope I am getting these declarations right at least :'(*/
prog : PROGRAM ID LPAR identifier_list RPAR SEMICOLON declarations 
	subprogram_declarations
	compound_statement
	PERIOD{
		root = $$  = newNode(PROG);	
		//$$ = $$ = newNode(S);
		addNewChild($$, $2);
		addNewChild($$, $4);
		addNewChild($$, $7);
		addNewChild($$, $8);
		addNewChild($$, $9);
		deleteNode($1);
		deleteNode($3);
		deleteNode($5);
		deleteNode($6);
		deleteNode($10);
	  }

;

identifier_list : ID {
		$$ = newNode(identifier_list);		
		addNewChild($$, $1);
	  }
| identifier_list COMMA ID{
		$$ = $1;			
		addNewChild($$, $3);
	  }
;
declarations : declarations VAR identifier_list COLON type SEMICOLON{
		$$ = $1;		
		addNewChild($$, $2);	
		addNewChild($$, $3);	
		addNewChild($$, $5);

		deleteNode($4);
		deleteNode($6);
	  }
| /* empty */{
		$$ = newNode(declarations);	
	  }
;

type : standard_type{
		//$$ = newNode(type);	
		$$ = $1;	
		//addNewChild($$, $1);
		//fprintf(stdout, "%d\n",$1->type);
	  }

| ARRAY LBRACKET NUM RANGE NUM RBRACKET OF type{
		$$ = $8;
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
		$$ = newNode(integer_type);
		$$->value = $1->value;
		//$$->specificType = INTEGER_VALUE; 
		//addNewChild($$, $1);
	  }
| REAL{
		$$ = newNode(real_type);
		$$->specificType= REAL_VALUE;
		addNewChild($$, $1);
	  }
	  
| STRINGCONST {
		$$ = newNode(string_type);	
		$$->specificType = STRING_VALUE;
		addNewChild($$, $1);
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
		$$ = newNode(subprogram_declarations);
	  }
;

subprogram_declaration : subprogram_head
					   declarations
					   subprogram_declarations
					   compound_statement{
		$$ = newNode(subprogram_declaration);		
		addNewChild($$, $1);
		addNewChild($$, $2);
		addNewChild($$, $3);
		addNewChild($$, $4);
	  }
;

subprogram_head : FUNCTION ID arguments COLON  standard_type SEMICOLON{
			//fprintf(stdout, "function type is : %d\n", $$->type);
			//fprintf(stdout, "reached a function call\n");
			$$ = newNode(function);	
			$$->specificType = function;
			addNewChild($$, $2);
			addNewChild($$, $3);
			addNewChild($$, $5);
	  }
| PROCEDURE ID arguments SEMICOLON{
		$$ = newNode(procedure);
		printf("procedure type is : %d\n", $$->type);
		$$->name = (char*)malloc(strlen($2->name+1));
		strcpy($$->name, $2->name);
		printf("new procedure definition: %s\n", $$->name);	
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
		$$ = newNode(arguments);
	  } 
;

/*still not super clear on this one either*/
/*cnoflict here*/
parameter_list : optional_var identifier_list COLON  type{
		$$ = newNode(parameter_list);
		addNewChild($$, $1);
		addNewChild($$, $2);
		addNewChild($$, $4);
		deleteNode($3);
	  }
| optional_var identifier_list COLON  type SEMICOLON  parameter_list{
		$$ = newNode(parameter_list);
		addNewChild($$, $1);
		addNewChild($$, $2);
		addNewChild($$, $4);
		addNewChild($$, $6);
		deleteNode($3);
		deleteNode($5);
	  }
;



optional_var : VAR{
		//$$ = $1;
		addNewChild($$, $1);
	  }
| /* empty */{
		$$ = newNode(optional_var);
	  } 
;

compound_statement : PBEGIN 
					optional_statements
					END{
		 $$ = newNode(compound_statement);	
		 addNewChild($$, $2);
		 deleteNode($1);
		 deleteNode($3);
	  }
; 
//when should I just pass $$ = $1 or do
//I create a unique node type for everything?
optional_statements : statement_list{
		$$ = newNode(optional_statements);
		addNewChild($$, $1);
	  }
;
statement_list: statement{
		$$ = newNode(statement);			  
	}
|statement_list COLON statement{
		$$ = $1;
		addNewChild($1, $3);
	}
;
statement : variable ASSIGNOP expression{
		$$ = newNode(ASSIGNOP);		  
		addNewChild($$, $1);
		addNewChild($$, $3);
	}
| procedure_statement{
		$$ = $1;
	}
| compound_statement{
		$$ = $1;	
	}
|	IF expression THEN statement ELSE statement{
		$$ = newNode(IF);
		addNewChild($$, $2);
		addNewChild($$, $4);
		addNewChild($$, $6);
	}
| WHILE expression DO statement{
		$$ = newNode(WHILE);
		addNewChild($$, $2);
		addNewChild($$, $4);
	}
| /* empty */{
		$$ = newNode(statement);
		}
;
variable : ID tail{
		 $$ = newNode(variable);
		printf("in variable prod\n");
		 addNewChild($$, $1);
		 addNewChild($$, $2);
	  }
;

tail : LBRACKET expression RBRACKET tail{
		addNewChild($$, $2);
		addNewChild($$, $4);
		deleteNode($1);
		deleteNode($3);
	  }
| /* empty */ {
		$$ = newNode(tail);	
	  }
;
procedure_statement :  ID{
		$$ = newNode(procedure_statement);
		printf("in procedure statement\n");
		addNewChild($$, $1);
	  }
| ID LPAR expression_list RPAR{
		printf("hello from procedure statement\n\n\n");
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
		$$ = newNode(expression); 
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
		$$ = newNode(boolexpression);
		addNewChild($$, $1);
	  }
| simple_expression relop simple_expression{
		addNewChild($$, $1);
		addNewChild($$, $2);
		addNewChild($$, $3);
	  }
;

simple_expression : term{
		$$ = newNode(simple_expression);
		addNewChild($$, $1);
	  }
| simple_expression addop term{
		$$ = $1;	
		addNewChild($$, $2);
		addNewChild($$, $3);
	  }
;

term : factor{
	 	$$ = newNode(term);
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
		$$ = newNode(factor);
		printf("in factor prod\n");
		addNewChild($$, $1);
		addNewChild($$, $2);
	  }
| ID LPAR expression_list RPAR{
		$$ = newNode(factor);
		printf("in factor prod\n");
		addNewChild($$, $1);
		addNewChild($$, $3);
		deleteNode($2);
		deleteNode($4);
	  }
|  NUM{	
		$$ = newNode(factor);
		addNewChild($$, $1);
	  }
| addop NUM{
		$$ = newNode(factor);
		addNewChild($$, $1);
	}
| STRINGCONST{

		$$ = newNode(factor);
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
		$$ = newNode(addop);
		addNewChild($$, $1);	
	  }
| MINUS{	
		$$ = newNode(addop);
		addNewChild($$, $1);	
	  }
;

mulop : MULTIPLY {
		$$ = newNode(mulop);
		addNewChild($$, $1);
	  }

| DIVIDE{	
		$$ = newNode(mulop);
		addNewChild($$, $1);
	  }
;

relop : LESSTHAN{
		$$ = newNode(relop);
		addNewChild($$, $1);
	  }
| GREATERTHAN {
		$$ = newNode(relop);
		addNewChild($$, $1);
	  }
| EQUAL{
		$$ = newNode(relop);
		addNewChild($$, $1);
	  }
| LEQ{
		$$ = newNode(relop);
		addNewChild($$, $1);
	  }
| GEQ{
		$$ = newNode(relop);
		addNewChild($$, $1);
	  }
| NOTEQUAL{
		$$ = newNode(relop);
		addNewChild($$, $1);
}
;
/*end of grammerino*/
%%
struct Node* root;
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
	//printf("hola\n");
	//struct Node* tmp = root;
	//traverse(tmp);
	//printf("bout to print the tree boi\n");
	traverse(root);
	if(hola==0){
		printf("Ok.\n");
	}
	return hola;
}
