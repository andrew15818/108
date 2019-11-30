#include<stdio.h>
#include"node.h"
int main(){
	struct Node* nodito = newNode(1);
	nodito->value = 4;
	printf("%s\n", nodito->value);
	return 0;
}
