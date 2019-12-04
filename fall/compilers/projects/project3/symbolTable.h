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
	procedure
};
struct Attributes{
	
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
	struct Entry *entries[MAX_SIZE];
	int currSize, scopeCounter;
};

struct Entry* newEntry(struct symbolTable* sym,struct Node* node);
void enterSymbol(struct symbolTable* sym, struct Node* node, int type);
struct Node* nthChild(int count, struct Node* node);
struct Entry* retrieveEntry(struct symbolTable* sym, struct Node* node);
void processNode(struct Node* node);
void openScope(struct symbolTable* sym);
int declaredLocally(struct symbolTable* sym, struct Node* node);
#endif
