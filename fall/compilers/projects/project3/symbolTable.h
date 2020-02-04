#ifndef SYMB_TABLE_H
#define SYMB_TABLE_H
#define MAX_SIZE 131

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

	struct Entry* nextEntry; //in the case of collisions
};
struct symbolTable{
	struct Entry *entries[MAX_SIZE];
	int currSize, scopeCounter;
	struct symbolTable *nextTable;
};
struct symbolTable* newTable();
struct Entry* newEntry(struct symbolTable* sym, struct Node* node);
void enterSymbol(struct symbolTable* sym, struct Node* node, int type);
struct Node* nthChild(struct Node* node, int count);
struct Entry* retrieveEntry(struct symbolTable* sym, struct Node* node);
void processNode(struct symbolTable* sym, struct Node* node);
void openScope(struct symbolTable* sym);
void printSymbolTable(struct symbolTable *sym);
#endif
