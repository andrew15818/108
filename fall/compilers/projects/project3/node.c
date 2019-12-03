#include<stdio.h>
#include<stdlib.h>
#include"node.h"
struct Node* newNode( int NodeType)
{
	struct Node* new = (struct Node*)malloc(sizeof(struct Node));
	//printf("holis %d\n", NodeType);
	new->type = NodeType;
	new->parent = NULL;
	new->leftMostChild = NULL;
	new->rightSibling = NULL;
	new->parent = NULL;
	new->op = NULL;
	return new;

}
struct Node* makeSiblings(struct Node* x, struct Node* y)
{
	//find the rightMost sibling of y to merge with the 
	//other leftmost sibling
	
	//tmp values we will use for joining the lists
	struct Node* xsibs = x;
	struct Node* ysibs = y->leftMostSibling;

	while(x->rightSibling != NULL){
		x = x->rightSibling;
	}
	//joining the two lists
	/* Basically doing:
	 * 	1. setting xsibs to the rightmost pointer on the x side, other way around  for y
	 * 	2. setting the right side of x to left side of y, joining the two lists
	 *	3. Taking care of their parents, leftMostSiblings for every node in y's list. 
	 * */
	x->rightSibling = ysibs;
	ysibs->leftMostSibling = xsibs->leftMostSibling; 
	ysibs->parent = xsibs->parent;

	while(ysibs->rightSibling != NULL){
		ysibs = ysibs->rightSibling;
		ysibs->leftMostSibling = xsibs->leftMostSibling;
		ysibs->parent = xsibs->parent;	
	}
	free(xsibs);
}
/*add new node as the child of the parent node, will be added to the 
 * rightmost side of the parents' children nodes.*/
void addNewChild(struct Node* parent, struct Node* child)
{
			
		child->parent = parent;
		if(parent->leftMostChild == NULL){
			parent->leftMostChild = child;		

			return;
		}	

		child->leftMostSibling = parent->leftMostChild;
		struct Node* tmp = parent->leftMostChild;
		
		//setting the previous rightmost child of parent to point to child node.
		while(tmp->rightSibling != NULL){
			tmp = tmp->rightSibling;	
		}
		tmp->rightSibling = child;
		//lousyPrint(child->leftMostSibling);
}

void deleteNode(struct Node* node)
{
	//if we have allocated memory 
	//for a node containing a string
	if(node->name != NULL){
		free(node->name);
	}
	free(node);	
}
void printTree(struct Node* node)
{
	if(node == NULL) return;

	struct Node* tmp = node;
	lousyPrint(tmp);
	printTree(tmp->leftMostChild);



}
void traverse(struct Node* node)
{
	if(node == NULL) return;
	switch(node->type){
		case PROG:
			printf("prog\n");	
			break;
		case ID_name:
			printf(" %s\n", node->name);
			break;
		case declarations:
			printf("declarations\n");
			break;
		case subprogram_declarations:
			printf("subprogram_declarations\n");
			break;
		case compound_statement:
			printf("compound statment\n");
			break;
		case id_value:
			printf("id_value :%d \n",node->value);
			break;
		case type:
			printf("type\n");
			break;
		case standard_type:
			printf("standard_type\n");
			break;
		case INTEGER_VALUE:
			printf("INTEEGER_VALUE: %d\n", node->value);
			break;
		case REAL_VALUE:
			printf("real value: %d\n", node->value);
			break;
		case subprogram_declaration:
			printf("subprogram_declarations\n");
			break;
		case subprogram_head:
			printf("subprogram_head\n");
			break;
		case arguments:
			printf("arguments\n");
			break;
		case parameter_list:
			printf("parameter_list\n");
			break;
		case optional_var:
			printf("optional_var\n");
			break;
		case begin:
			printf("begin\n");
			break;
		case end:
			printf("end\n");
			break;
		case optional_statements:
			printf("optional_statements\n");
			break;
		case statement_list:
			printf("statement_list\n");
			break;
		case procedure_statement:
			printf("procedure_statement\n");
			break;
		case statement:
			printf("statement\n");
			break;
		case variable:
			printf("variable\n");
			break;
		case expression:
			printf("expression\n");
			break;
		case integer_type:
			printf("TYPE_INT\n");
			break;
		case real_type:
			printf("TYPE_REAL\n");
			break;
		case string_type:
			printf("TYPE_STRING\n");
			break;
		default:
			//printf("unwirtten type, ytpe: %d\n", node->type);
			break;
		/*
		case :
			printf("\n");
			break;
		case :
			printf();
			break;
		case :
			printf();
			break;
		case :
			printf();
			break;
	*/	

	}
	struct Node* tmp = node->leftMostChild;
	while( tmp != NULL){
		traverse(tmp);
		tmp = tmp->rightSibling;
		//raverse(node->leftMostChild);
	}

}
void lousyPrint(struct Node* node)
{
	if(node  == NULL)return;
	struct Node* tmp = node;
	while(tmp != NULL){
		fprintf(stdout, "node of type: %d %s\n", tmp->type, tmp->name);
		tmp = tmp->rightSibling;
	}
}
