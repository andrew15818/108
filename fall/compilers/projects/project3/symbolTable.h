#ifndef SYMB_TABLE_H
#define SYMB_TABLE_H
#define MAX_SIZE 10000

#include"node.h"
//types which we would have to print out 
enum Type{
	array,
	integer,
	real,
	function,
	procedure,

	
	j
};
struct Entry{
	char* name;
	enum Type entryType;
	int scope;

	//for arrays? 
	int lowerBound, upperBound;
	int scopeDeclaredIn;  //scope where we were originally declared

	struct Node* attributes;
	struct Node* node;
};
struct symbolTable{
	struct Entry **entries[MAX_SIZE];
	int currSize, scopeCount;
};

struct Entry* newEntry(struct Node* node);
void enterSymbol(struct Node* node, int type);
struct Entry* retrieveEntry(char* name);
void processNode(struct Node* node);
#endif
