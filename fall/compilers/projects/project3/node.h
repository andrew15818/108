#ifndef NODE_H
#define NODE_H

//define the types of operators here
#include"y.tab.h"
#define op_plus 101
#define op_minus 102 
#define op_gt 103 
#define op_lt 104
#define op_equal 105
#define op_nequal 106
#define op_geq 107
#define op_leq 108
#define op_and 109
#define op_or 110
#define op_assign 111
#define op_multiply 12
#define op_divide 13
// remember to add all the types to the enum;
// here we place all the types of the symbols,
// is this more right?
enum Nodetype{
		PROG,
		ID_name,
		identifier_list,
		declarations,
		subprogram_declarations,
		compound_statement,
		id_value,
		type,
		standard_type,
		INTEGER_VALUE,
		REAL_VALUE,
		STRING_VALUE,
		integer_type,
		real_type,
		string_type,
		subprogram_declaration,
		subprogram_head,
		arguments, 
		parameter_list,
		optional_var,
		begin,
		end,
		optional_statements,
		statement_list,
		statement, 
		variable, 
		expression,
		procedure_statement,
		tail,
		expression_list,	
		simple_expression,
		boolexpression,
		term,
		factor,
		relop,
		addop,
		mulop,
		other
};
struct Node{
	//pointer info to related nodes
	struct Node* parent;
	struct Node* leftMostChild;
	struct Node* leftMostSibling;
	struct Node* rightSibling;
	struct Node* leftSibling;

	//if an array, the beginning and end with range operator
	int lowerBound, upperBound;
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
void lousyPrint(struct Node* node);
void traverse(struct Node* node);
#endif
