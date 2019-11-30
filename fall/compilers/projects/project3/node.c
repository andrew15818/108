#include<stdio.h>
#include<stdlib.h>
#include"node.h"
struct Node* newNode( int NodeType)
{
	struct Node* new = (struct Node*)malloc(sizeof(struct Node));
	new->type = NodeType;
	new->parent = NULL;
	new->leftMostChild = NULL;
	new->rightSibling = NULL;
	new->parent = NULL;
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
}

void printTree(struct Node* node)
{
	if(node == NULL){return;}

	switch(node->type){
			//TODO: probably have to change this later
			case DECLARATION_NODE:
					fprintf(stdout, "%s" node->name);
					break;
			case
	}
}
