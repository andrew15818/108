#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "node.h"
#include "symbolTable.h"
//create a new entry to insert
struct Entry* getEntry(struct symbolTable* sym, struct Node* node){
	//placeholder 
	struct Entry* tmp;
	return tmp;
}
void initSymbolTable(struct symbolTable* sym){
	sym->scopeCounter = 0;
	sym->currSize = 0;
}
struct Entry* newEntry(struct symbolTable* sym, struct Node* node)
{
	struct Entry* newEntry = (struct Entry*)malloc(sizeof(struct Entry));
	newEntry->name = NULL;

	//maybe set it equal to the current scope when this entry is created?
	newEntry->scopeDeclaredIn = sym->scopeCounter;
}

//insert element into the table
void enterSymbol(struct symbolTable* sym, struct Node* node, int type)
{	
	if(retrieveEntry(sym, node) != NULL){
		printf("redeclaration of %s.\n",node->name);
	}
	struct Entry* tmp = newEntry(sym, node);	
	sym->entries[sym->currSize] = tmp;
	sym->currSize++;
}
//retrieve element into table, have to check for scope rules
struct Entry* retrieveEntry(struct symbolTable* sym, struct Node* node)
{
	for(int i = sym->currSize; i>=0 /*&& sym->entries[i]->scopeDeclaredIn == node->scope*/; i--)	
	{
		if(strcmp(sym->entries[i]->node->name, node->name)){
			return sym->entries[i];
		}	
	}
	return NULL;
}

void processNode(struct Node* node)
{
		switch(node->type)
		{
			case function: 
					printf("function node\n");
					break;
		}
}
struct Node* nthChild(int n, struct Node* node)
{
	struct Node* tmp = node->leftMostChild;
	for(int i = 0; i< n && tmp != NULL; i++){
		tmp = tmp->rightSibling;
	}
	if(tmp != NULL){
		return tmp;
	}
	return NULL;

}
