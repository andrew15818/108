#ifndef NODE_H
#define NODE_H

//here we do macros for the types of nodes
#define PROGRAM_NODEj 1
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

	int value;

	char* name;
	
	char op;
};

struct Node* newNode(int NodeType);
struct Node* makeSibling(struct Node* x, struct Node* node);
void addNewChild(struct Node* child);
#endif
