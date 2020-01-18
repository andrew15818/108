#include<stdio.h>
#include "genCode.h"
#include "symtab.h"
char* fileName = "output.s";
char* progName;
struct SymTable* symbolTable;
struct SymTableEntry tmp; //since we iterate multiple times through symbol table
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
				;//empty statement
				progName = node->string;
				struct nodeType* declNode = nthChild(1, node);//node declarations
				struct nodeType* subprogram_declNode = nthChild(2, node); //subprogram_declarations
				struct nodeType* compoundStatementNode = nthChild(3, node); //compoundStatements

				printf("entering node program\n");		
				initFile(fileName); //creating output file
				//writing bytecode file header
				fprintf(fp, ".class public %s\n", node->string);//creating a public class
				fprintf(fp, ".super java/lang/Object\n\n");//initting empty object? 

				
				symbolTable = ScopeStack[0];
				 
				//declaring global variables	
				for(int i=0; i< symbolTable->size; i++){
					tmp = symbolTable->entries[i];	
					if(tmp.dtype == Function){continue;}
					if(tmp.type == TypeInt){
						fprintf(fp,".field public static %s I\n", tmp.name);
					}
					else if(tmp.type == TypeReal){
						fprintf(fp,".field public static %s F\n", tmp.name);
					}
					//need to fix these arrays :(
					else if(tmp.type == TypeArray){
						printf("there is an array\n");
					}
				}

				//we have to init a separate method to init the variables
				if(symbolTable->size != 0){
					fprintf(fp, "\n.method public static vinit()V\n");
					fprintf(fp, "\t.limit locals 100\n"); //max amount of local variables
					fprintf(fp, "\t.limit stack 100\n"); //max amount of stack space
					genCode(declNode);
					fprintf(fp,"\treturn\n");
					fprintf(fp, ".end method\n");
				}

				//standard init?
				fprintf(fp, "\n.method public static <init>()V\n");
				fprintf(fp, "\taload_0\n");
				fprintf(fp, "\tinvokenonvirtual java/lang/Object/<init>()V\n");
				fprintf(fp, "\treturn\n");
				fprintf(fp, ".end method\n");

				//subprogram declarations
				genCode(subprogram_declNode);

				fprintf(fp, "\n.method public static main([Ljava/lang/String;)V\n");
				fprintf(fp, "\t.limit locals 100\n");
				fprintf(fp, "\t.limit stack 100\n");
				//if there is a global variable, we have to call the init function first
				int isGlobalVar = 0;
				for(int i =0;i< symbolTable->size;i++){
					tmp = symbolTable->entries[i];
					isGlobalVar = (tmp.dtype == Variable || tmp.dtype == Array)?1:0;
				}
				if(isGlobalVar){
					fprintf(fp, "\tinvokestatic %s/vinit()V\n", progName);
				}
				//compound statement code
				genCode(compoundStatementNode);
				fprintf(fp, "\treturn\n");
				fprintf(fp, ".end method");
			break;

			case NODE_identifier_list:
				printf("identifier list\n");
				//struct nodeType* listNode = nthChild(1, node); 
				//struct nodeType* listTypeNode = nthChild(2, node); 	
				printf("next one\n");

				break;
			//handle global variables
			case NODE_declarations:
				printf("NODE_declarations\n");
				for(int i=0; i<symbolTable->size; i++)
				{
					tmp = symbolTable->entries[i];
					if(tmp.dtype != Function){
						
						if(tmp.type == TypeInt){
							fprintf(fp, "\tldc 0\n");
							fprintf(fp, "\tputstatic %s/%s I\n", progName, tmp.name);
						}
						else if(tmp.type == TypeReal){
							fprintf(fp, "\tldc 0.0\n");
							fprintf(fp, "\tputstatic %s/%s F\n", progName, tmp.name);
						}
						/*fix arrays*/
						else if(tmp.dtype ==Array){
							printf("\tArray\n");
						}
					}
				}	
				printf(fp, "\n");
				break;
			case NODE_subprogram_declarations:
				printf("NODE_subprogram_declarations\n");
				genCode(nthChild(1, node));

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

				//function name
				fprintf(fp, ".method public static method %s\n", testNode->string);

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
