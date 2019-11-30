#ifndef SYMB_TABLE_H
#define SYMB_TABLE_H
#define MAX_SIZE 10000
#include"node.h"
struct Entry{
	char* name;
	struct Type* type;	
	int scope;

	struct Node* attributes;
};
struct symbolTable{
	struct Entry **entries[MAX_SIZE];
	int currSize;
};

struct Entry* newEntry(struct Node* node);
void enterSymbol(struct Node* node, int type);
struct Entry* retrieveEntry(char* name);
void processNode(struct Node* node);
#endif
