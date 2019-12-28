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
	new->scopeCounter = 1;
	new->nextTable = NULL;
	return new;
}

struct Entry* newEntry(struct symbolTable* sym, struct Node* node)
{
	struct Entry* new = (struct Entry*)malloc(sizeof(struct Entry));
	
	if(node->name != NULL)
	{
		//not sure about this one
		new->name = (char*)malloc(sizeof(node->name+1));	
		strcpy(new->name, node->name);
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
struct Entry* retrieveEntry(struct symbolTable* sym, struct Node* node)
{		
	int hashIndex = hash(node);	
	
	struct Entry* new= sym->entries[hashIndex];
	while(new!= NULL){
		//struct Entry* tmpEntry = sym->entries[hashIndex];
		if(!strcmp(node->name, new->name)){
			//printf("found %s already in our table\n", node->name);		
			return sym->entries[hashIndex];	
		}
		new= new->nextEntry;
	}
	return NULL;	
}
void enterSymbol(struct symbolTable* sym, struct Node* node, int type)
{
	struct Entry* tmpEntry = retrieveEntry(sym, node);

	//checking if the symbol is already declared
	if(tmpEntry != NULL){
			//how to get  the correct index? 
		printf("Error: redeclaration of: %s\n", node->name);
		return;
	}
	struct Entry* new ;//= newEntry(node);
	//new->type = node->type;
	new->node = node;	
	//new->scopeDeclaredIn = sym->scopeCounter;
	int hashIndex = hash(node);	
	if(sym->entries[hashIndex] == NULL){
		sym->entries[hashIndex] = new;	
		//sym->entries[hashIndex]->name = (char*)malloc(strlen(node->name));
		new->name = (char*)malloc(strlen(node->name));
		strcpy(new->name,node->name);
		//printf("undeclared variable %s\n", node->name);
	}
	else{
		struct Entry* tmp = sym->entries[hashIndex];
		while(tmp != NULL){
			tmp = tmp->nextEntry;	
		}
		tmp = new;
	}	
	
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
			//printf("prcessing id node with name: %s\n", node->name);
			;
			struct Entry* dummy = newEntry(sym, node);
			enterSymbol(sym, node, node->type);
			break;
		default: ;
			struct Node* tmp = node->leftMostChild;
			while(tmp != NULL){
				processNode(sym, tmp);	
				tmp = tmp->rightSibling;
			}
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
