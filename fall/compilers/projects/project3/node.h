#ifndef NODE_H
#define NODE_H

//here we do macros for the types of nodes
#define PROGRAM_NODE 1
#define ID_NODE 2
#define NUM_NODE 3
#define	STRINGCONST_NODE 4
#define STRING_NODE  5
#define INTEGER_NODE  6
#define REAL_NODE 7
#define	GT_NODE  8
#define LEQ_NODE  9
#define GEQ_NODE 10
#define EQUAL_NODE 11
#define NOT_EQUAL_NODE 12
#define PLUS_NODE 13
#define MINUS_NODE 14
#define MULTIPLY_NODE 15
#define DIVIDE_NODE 16



//more general types for the node decalrations
#define DECLARATION_NODE 17
#define VAR_NAME_NODE 18	//have to distinguish these in order to print them
#define VAR_NODE 19
#define IF_NODE 20
#define OF_NODE 21
#define THEN_NODE 22
#define ELSE_NODE 23
#define WHILE_NODE 24 
#define DO_NODE 25
#define NOT_NODE 26
#define BEGIN_NODE 27


#define END_NODE 30
#define PROCEDURE_NODE 31
#define FUNCTION_NODE 32

#define AND_NODE 34
#define OR_NODE 35
#define ARRAY_NODE 37
//for the actual integer number type
#define INTEGER_CONSTANT_NODE 38
#define LBRACKET_NODE 39
#define RBRACKET_NODE 40
#define LPAREN_NODE 41
#define RPAREN_NODE 42
#define COLON_NODE 43
#define PERIOD_NODE 44

// remember to add all the types to the enum;
enum Nodetype{
	type_program,
	type_identifier_list,
	type_declarations,
	type_type,
	type_standard_type,
	type_subprogram_declarations,
	type_subprogram_declaration,
	type_subprogram_head,
	type_arguments,
	type_parameter_list,
	type_optional_var,
	type_compound_statement,
	type_optional_statements,
	type_statement_list,
	type_statement,
	type_variable,
	type_tail,
	type_procedure_statement,
	type_expression_list,
	type_expression,
	type_boolexpression,
	type_simple_expression,
	type_term,
	type_factor,
	type_addop,
	type_mulop,
	type_relop,
};
struct Node{
	//pointer info to related nodes
	struct Node* parent;
	struct Node* leftMostChild;
	struct Node* leftMostSibling;
	struct Node* rightSibling;
	struct Node* leftSibling;

	//different node values depending on the type of node this is
	int type;
	int specificType; //once we know if it's not a node for a single symbol, we can assign 
					  // to it one of the names of the productions


	//in case of int 
	int value;

	//in case of string-related type, id name for example...
	char* name;
	
	//in case of operator symbol
	char op;
};

struct Node* newNode(int NodeType);
struct Node* makeSibling(struct Node* x, struct Node* node);
void deleteNode(struct Node* node);
void addNewChild(struct Node* parent, struct Node* child);
void printTree(struct Node* node);

#endif
