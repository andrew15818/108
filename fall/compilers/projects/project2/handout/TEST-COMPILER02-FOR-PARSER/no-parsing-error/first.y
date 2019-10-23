%{
/*
* This is my first attempt
*
*/
%}
%token PROGRAM ID LPAR RPAR SEMICOLON PERIOD COMMA VAR
%token COLON ARRAY LBRACKET RBRACKET NUM STRINGCONST
%token OF INTEGER REAL FUNCTION PROCEDURE PBEGIN
%token END ASSIGNOP IF THEN ELSE WHILE DO LESSTHAN
%token GREATERTHAN LEQ GEQ EQUAL NOTEQUAL PLUS MINUS
%token MULTIPLY DIVIDE NOT RANGE BLANK COMMENT IDENTIFIER

%%
/*grammar file doesnt't specify wheter | between each thing here*/
prog : program id(identifier_list)
	declarations 
	subprogram_declarations
	compound_statement
	.
;

identifier_list : id
| identifier_list , id 
;

delcarations : declarations var identifier_list : type 
| lambda
;

type : standart_type
| ARRAY [num .. num] OF type
;

standard_type : integer
|real
| string
;

subprogram_declarations : subprogram_declarations  
						subprogram_declaration
;

subprogram_declaration : subprogram_head
					   declarations
					   compound_statement
;

subprogram_head : function id arguments : standard_type
| procedure id arguments
;

arguments : (pararmeter_list)
| lambda
;

/*still not super clear on this one either*/
parameter_list : optional_var identifier_list : type
| optional_var identifier_list : type  parameter_list
;

optional_var : var
| lambda
;

compound_statement : begin
				   optional_statements
				   end
; 

optional_statements : statement_list
| lambda
;

/*not really sure what ; means inside a declaration*/
statement_list : statement
|statement_list statement;

statement : variable := expression
| procedure_statement
| compound_statement
| if expression then statement else statement
| while expression do statement
| lambda
;

variable : id tail
;

tail : [ expression ] tail
| lambda	
;

procedure_statement : id
| id (expression list)
;

expression_list : expression
| expression_list , expression
;

expression : simple_expression
| simple_expression relop simple_expression
;

simple_expression : term
| simple_expression relop simple_expression
;

term : factor
| term mulop factor
;

factor : id tail
| id (expression_list)
| num
| stringconstant
| ( expression )
| not factor
;

addop : + | -
;

mulop : * | /
;

relop : < 
| > 
| = 
| <=
| >=
| !=
;
/*end of grammerino*/
