#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"symbolTable.h"
#include"node.h"
#define HASH_SIZE 131 //kinda priime hash size?

int hash(struct Node* node)
{
	long long int sum = 0;		
	for(int i =0; i < strlen(node->name); i++)
	{
		sum += (node->name[i] && HASH_SIZE);	
	}
	return sum%HASH_SIZE;
}
struct symbolTable* newTable()
{
	struct symbolTable* new = (struct symbolTable*)malloc(sizeof(struct symbolTable));
	new->currSize = 0;
	new->scopeCounter = 0; //global scope
	new->nextTable = NULL;
	return new;
}
void setFunctionParams(struct Entry* entry, struct Node* arguments)
{
	return;	
}
struct Entry* newEntry(struct symbolTable* sym, struct Node* node)
{
	struct Entry* new = (struct Entry*)malloc(sizeof(struct Entry));
	
	if(node->name != NULL)
	{
		//not sure about this one
		new->name = (char*)malloc(sizeof(node->name+1));	
		strcpy(new->name, node->name);
		new->node = node;
		//printf("new Entry name: %s\n", new->name);
	}
	
	new->scopeDeclaredIn = sym->scopeCounter;	
}

struct Node* nthChild(struct Node* node, int count)
{
	struct Node* tmp = node->leftMostChild;
	int i = 0;
	while( i < count)
	{
		tmp = tmp->rightSibling;	
		i++;
	}
	return tmp;
}

//when we see a {, maybe open a new scope and declare a new table
void openScope(struct symbolTable* sym)
{
	struct symbolTable* new = newTable();
	sym->nextTable = new;
	sym->scopeCounter++;
}

//check to see if the symbol is already in the table
struct Entry* retrieveEntry(struct symbolTable* sym, struct Node* node, int scope)
{		
		int index = 0;
		while(index  < sym->currSize){
			struct Entry* tmp  = sym->entries[index];
			if(strcmp(tmp->name, node->name) == 0 && tmp->scopeDeclaredIn == scope){
				return sym->entries[index];
			}
			index--;
		}
		return NULL;
}
void enterSymbol(struct symbolTable* sym, struct Node* node, int type)
{
	printf("trying to insert: %s\n", node->name);
	struct Entry* tmpEntry = retrieveEntry(sym, node, sym->scopeCounter);
	if(tmpEntry != NULL){
		printf("redeclaration of %s\n",tmpEntry->name );	
		return;
	}
	struct Entry* new = newEntry(sym, node);
	sym->entries[sym->currSize] = new;
	sym->currSize++;

}
void processNode(struct symbolTable* sym, struct Node* node)
{
	switch(node->type){
		case prog:
			printf("processing root node rn\n");	
			for(int i = 0; i < 5; i++){
				processNode(sym, nthChild(node, i));	
			}
			break;
		case ID_name:			
			printf("prcessing id node with name: %s\n", node->name);
			;
			struct Entry* dummy = newEntry(sym, node);
			//enterSymbol(sym, node, node->type);
			break;
		case function:
			printf("function node in symbol table ");
			struct Node* id = nthChild(node, 0);
			struct Node* type = nthChild(node, 1);
			processNode(sym, id);	
			processNode(sym, type);
			node->name = (char*)malloc(sizeof(id->name) +1);
			strcpy(node->name, id->name);
			printf(" with name %s\n", node->name);
			enterSymbol(sym, node, node->type);

			processNode(sym, nthChild(node,2));
			break;
		case arguments:
			printf("ST: analyzing arguments\n");
			struct Node* tmporino = nthChild(node, 0);
			break;
		case parameter_list:
			printf("ST: analyzing parameter_list\n");
			break;
		case statement:
			;
			printf("statement\n");
			struct Node* target = nthChild(node, 0);
			printf("assign target: %d\n", target->type);
			//processNode(sym, target);
			//processNode(sym, nthChild(node, 0));
			//processNode(sym, target);
			//struct Node* value = nthChild(node, 1);
			break;
		case optional_statements:
			processNode(sym, nthChild(node, 0));
			break;
		case statement_list:
			processNode(sym, nthChild(node, 0));
			break;
		default: ;
			//printf("analyzing %d\n", node->type);	
			struct Node* tmp = node->leftMostChild;
			while(tmp != NULL){
				processNode(sym, tmp);	
				tmp = tmp->rightSibling;
			}
		
			break;
	}
}

void printSymbolTable(struct symbolTable* sym)
{
	printf("\n+-------------------------------------+\n");
	printf("name\t scope \ttype \treturn \tparameter \tDim \t Array Range\n");
	for(int i=0; i < MAX_SIZE; i++ ){
		if(sym->entries[i] != NULL){
			struct Entry* tmp = sym->entries[i];

			while(tmp != NULL){
				printf("%s\t %d\t %d\n", tmp->name, tmp->scopeDeclaredIn, tmp->node->type);
				tmp = tmp->nextEntry;
			}
		}
	}
}
