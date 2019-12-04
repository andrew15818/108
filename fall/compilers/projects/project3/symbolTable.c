#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "node.h"
#include "symbolTable.h"
void openScope(struct symbolTable* sym);
struct symbolTable* newTable()
{
	struct symbolTable *new = (struct symbolTable*)malloc(sizeof(struct symbolTable));
	return new;
}
//create a new entry to insert
struct Entry* getEntry(struct symbolTable* sym, struct Node* node)
{
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

	newEntry->node = node;
	return newEntry;
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
			printf("found element with name %s\n", hola);
		}	
	}
	return NULL;
}

void processNode(struct symbolTable* sym, struct Node* node)
{
		if(node == NULL) return;
		printf("prcessing node of type: %d\n", node->type);
		switch(node->type)
		{
			case prog: 
					printf("program node\n");
					processNode(sym, nthChild(node, 0));
					break;
			case declarations:
					printf("declarations");
					break;
			case ID_name:
					enterSymbol(sym, node, node->type);
					break;
		}
}
struct Node* nthChild( struct Node* node, int n)
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
void openScope(struct symbolTable* sym)
{
	//should we just open an entirely new symbol table?
}
