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

struct Node{
	struct Node* parent;
	struct Node* leftmostChild;
	struct Node* rightSibling;
	struct Node* leftSibling;

	int type;

	char* name;
	
	char op;
};

struct Node* newNode();

#endif
