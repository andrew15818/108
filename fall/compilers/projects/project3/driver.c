#include<stdio.h>
#include"node.h"
void traversal(struct Node* node);
void sillyPrint(struct Node* root);
static counter = 0;
int main(){
	struct Node* root = newNode(INTEGER_VALUE);
	root->value = 0;
	for(int i = 1; i < 10; i ++)
	{
		struct Node* currNode = newNode(INTEGER_VALUE);
		currNode->value = i;
		addNewChild(root, currNode);
	}
	
	//printf("%d\n", );
	//
	//sillyPrint(root);
	traversal(root);
	printTree(root);
	return 0;
}
void sillyPrint(struct Node* root)
{
	struct Node* tmp = root->leftMostChild;
	while(tmp != NULL)
	{
		printf("%d -> ", tmp->value);
		tmp = tmp->rightSibling;
	}
}
void traversal(struct Node* node)
{
	if(node == NULL){return;}	
	struct Node* tmp = node;	

	while(tmp != NULL){

		traversal(tmp->leftMostChild);	

		tmp = tmp->rightSibling;
		printf("traversing %d-th node\n", counter++);
	}

}

