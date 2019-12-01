#include<stdio.h>
#include<stdlib.h>
#include "node.h"
#include "symbolTable.h"
//create a new entry to insert
struct Entry* newEntry(struct Node* node)
{
	Entry* newEntry = (Entry*)malloc(sizeof(Entry));
	newEntry->name = NULL;

	//maybe set it equal to the current scope when this entry is created?
	newEntry->scope = -1;
}

//insert element into the table
void enterSymbol(struct Node* node, int type)
{
}
//retrieve element into table, have to check for scope rules
struct Entry* retrieveEntry(char* name)
{
}


void processNode(struct Node* node)
{
}
