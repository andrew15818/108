%{
/* * This is my first attempt * */
%}
%token PROGRAM ID LPAR RPAR SEMICOLON PERIOD COMMA VAR
%token COLON ARRAY LBRACKET RBRACKET NUM STRINGCONST
%token OF INTEGER REAL FUNCTION PROCEDURE PBEGIN AND OR
%token END ASSIGNOP IF THEN ELSE WHILE DO LESSTHAN
%token GREATERTHAN LEQ GEQ EQUAL NOTEQUAL PLUS MINUS
%token MULTIPLY DIVIDE NOT RANGE BLANK COMMENT IDENTIFIER
/*not sure if i should just include the following tokens*/


%%
/*grammar file doesnt't specify wheter | between each thing here*/
prog : PROGRAM ID LPAR identifier_list RPAR
	declarations 
	subprogram_declarations
	compound_statement
	PERIOD
;

identifier_list : ID 
| identifier_list COMMA ID 
;

declarations : declarations VAR identifier_list COLON type SEMICOLON
| /* empty */
;

type : standard_type
| ARRAY LBRACKET NUM PERIOD PERIOD  NUM RBRACKET OF type
;

standard_type : INTEGER 
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

optional_var : VAR | /* empty */ ;

compound_statement : PBEGIN 
					optional_statements
					END 
; 

optional_statements : statement_list
;


statement_list : statement
|statement_list SEMICOLON statement
;

statement : variable COLON EQUAL expression
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
| NUM 
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
	return yyparse();
}
