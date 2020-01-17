#include<stdio.h>
#include "genCode.h"
#include "symtab.h"
char* fileName = "output.s";
FILE* fp;
void initFile(const char* Filename)
{
	fp = fopen("output.j", "w");
}
void emitFunctionHeader(struct nodeType* funcNode);
void genCode(struct nodeType* node)
{
	if(node == NULL)return;
	switch(node->nodeType){
			case NODE_prog:
				printf("entering node program\n");		
				initFile(fileName); //creating output file
				//writing bytecode file header
				fprintf(fp, ".class public %s\n", node->string);//creating a public class
				fprintf(fp, ".super java/lang/Object\n\n");//initting empty object? 

				genCode(nthChild(1, node)); //declarations
				genCode(nthChild(2, node)); //subprogram declarations
				genCode(nthChild(3, node)); //compound statement
				break;
			case NODE_identifier_list:
				printf("identifier list\n");
				//struct nodeType* listNode = nthChild(1, node); 
				//struct nodeType* listTypeNode = nthChild(2, node); 	
				printf("next one\n");

				break;
			//handle global variables
			case NODE_declarations:
				printf("declarations\n");
				struct nodeType* IDs = (nthChild(2, node));
				struct nodeType* declType = (nthChild(3, node));

				if(declType == NULL) return;
				switch(declType->nodeType)
				{
						case NODE_TYPE_INT:	
							;

							//printf("number of IDs per children: %d\n", IDs->numChildren);	
							for(int i=0; i< IDs->numChildren; i++){
								fprintf(fp, ".field public static %s I\n", nthChild(i+1, IDs)->string);	
							}	
							break;
						case NODE_TYPE_REAL:
							printf("\tdeclarations of reals\n");
							for(int i=0; i<IDs->numChildren; i++){
								fprintf(fp,".field public static %s F\n", nthChild(i+1, IDs)->string);	
							}
							break;
						case NODE_TYPE_STRING:	
							printf("\tdeclarations of strings\n");
							for(int i=0; i< IDs->numChildren; i++){
								fprintf(fp,".field public static %s S\n", nthChild(i+1,IDs)->string);		
							}
							break;
				}
				genCode(nthChild(1, node));
				break;
			case NODE_subprogram_declarations:
				printf("NODE_subprogram_declarations\n");
				//genCode(nthChild(1, node));
				genCode(nthChild(2, node));
				break;
			case NODE_subprogram_declaration:
				printf("NODE_subprogram_declaration\n");
				genCode(nthChild(1,node));
				genCode(nthChild(2,node));
				genCode(nthChild(3,node));

				break;
			case NODE_subprogram_head:
				printf("NODE_subprogram_head\n");
				struct nodeType* testNode = nthChild(1, node);

				if(testNode->nodeType == NODE_FUNCTION){
					emitFunctionHeader(node);	
				}

				break;
						case NODE_compound_statement:
				printf("compound_statement\n");
				break;
			default:
				printf("defaulterino\n");
				break;
	}
}
void emitFunctionHeader(struct nodeType* funcNode)
{
		printf("EMMITTING FUNCTION HEADER\n");
		struct nodeType* functionIdNode = nthChild(1, funcNode);
		struct nodeType* functionArgsNode = nthChild(2, funcNode);
		struct nodeType* functionTypeNode = nthChild(3, funcNode);

		char returnType;
		if(functionTypeNode->nodeType == NODE_TYPE_INT){
			returnType = 'I';	
			printf("\tfunction returns INT\n");
		}
		else if(functionTypeNode->nodeType == NODE_TYPE_REAL){
			printf("\tfunction returns STRING\n");	
			returnType = 'F';
		}
		
}
