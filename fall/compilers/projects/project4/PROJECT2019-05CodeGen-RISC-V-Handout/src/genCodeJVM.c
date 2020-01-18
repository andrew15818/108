#include<stdio.h>
#include "genCode.h"
#include "symtab.h"
char* fileName = "output.s";
char* progName;
struct SymTable* symbolTable;
struct SymTableEntry tmpEntry; //since we iterate multiple times through symbol table
struct nodeType* tmpNode;
FILE* fp;
void initFile(const char* Filename)
{
	fp = fopen("output.j", "w");
}
void emitFunctionHeader(struct nodeType* funcNode);
void  getFunctionArgs(struct nodeType* paramListNode, char* args);
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
					tmpEntry = symbolTable->entries[i];	
					if(tmpEntry.dtype == Function){continue;}
					if(tmpEntry.type == TypeInt){
						fprintf(fp,".field public static %s I\n", tmpEntry.name);
					}
					else if(tmpEntry.type == TypeReal){
						fprintf(fp,".field public static %s F\n", tmpEntry.name);
					}
					//need to fix these arrays :(
					else if(tmpEntry.type == TypeArray){
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
					fprintf(fp, ".end method\n\n");
				}

				//standard init?
				fprintf(fp, "\n.method public static <init>()V\n");
				fprintf(fp, "\taload_0\n");
				fprintf(fp, "\tinvokenonvirtual java/lang/Object/<init>()V\n");
				fprintf(fp, "\treturn\n");
				fprintf(fp, ".end method\n\n");

				//subprogram declarations
				genCode(subprogram_declNode);

				fprintf(fp, "\n.method public static main([Ljava/lang/String;)V\n");
				fprintf(fp, "\t.limit locals 100\n");
				fprintf(fp, "\t.limit stack 100\n");
				//if there is a global variable, we have to call the init function first
				int isGlobalVar = 0;
				for(int i =0;i< symbolTable->size;i++){
					tmpEntry = symbolTable->entries[i];
					isGlobalVar = (tmpEntry.dtype == Variable || tmpEntry.dtype == Array)?1:0;
				}
				if(isGlobalVar){
					fprintf(fp, "\tinvokestatic %s/vinit()V\n", progName);
				}
				//compound statement code
				//genCode(compoundStatementNode);
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
					tmpEntry = symbolTable->entries[i];
					if(tmpEntry.dtype != Function){
						
						if(tmpEntry.type == TypeInt){
							fprintf(fp, "\tldc 0\n");
							fprintf(fp, "\tputstatic %s/%s I\n", progName, tmpEntry.name);
						}
						else if(tmpEntry.type == TypeReal){
							fprintf(fp, "\tldc 0.0\n");
							fprintf(fp, "\tputstatic %s/%s F\n", progName, tmpEntry.name);
						}
						/*fix arrays*/
						else if(tmpEntry.dtype ==Array){
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
				//genCode(nthChild(2,node));
				genCode(nthChild(3,node));

				break;
			case NODE_subprogram_head:
				printf("NODE_subprogram_head\n");
				char returnType;
				char* functionArgs;
				struct nodeType* funcNode= nthChild(1, node);
				struct nodeType* funcArgsNode = nthChild(2, node);
				struct nodeType* funcReturnType = nthChild(3,node);
				returnType = (funcReturnType->nodeType == NODE_TYPE_INT)?'I':'F';

				if(funcArgsNode->nodeType == NODE_arguments){
					funcArgsNode = nthChild(1,funcArgsNode);	
					if(funcArgsNode->nodeType == NODE_parameter_list){
						getFunctionArgs(funcArgsNode, functionArgs);							
						printf("\t\tfunction args so far: %s\n",functionArgs);
					}
				}

				//searching for the function in the symbol table

				for(int i=0; i<symbolTable->size; i++){
					tmpEntry = symbolTable->entries[i];	
					if(!strcmp(tmpEntry.name, funcNode->string)){
						fprintf(fp, ".method public static %s(%s)%c\n",funcNode->string,functionArgs,returnType);
						break;
					}
					
				}
				fprintf(fp,"\t.limit locals 100\n");
				fprintf(fp,"\t.limit stack 100\n");
				fprintf(fp,"\treturn\n");
				fprintf(fp,".end method\n");
				break;//sub_head_case
			case NODE_compound_statement:
				printf("NODE_compound_statement\n");
				break;
			case NODE_if:
				printf("NODE_if\n");
				break;
			case NODE_while:
				printf("NODE_while\n");
				break;
			default:
				printf("defaulterino\n");
				break;
	}
}
void  getFunctionArgs(struct nodeType* paramListNode, char* args)
{

		struct nodeType* tmpTypeNode = nthChild(2 , paramListNode);
		if(tmpTypeNode->nodeType == NODE_TYPE_INT){
			strcat(args, "I");	
		}
		else if(tmpTypeNode->nodeType == NODE_TYPE_REAL){
			strcat(args,"F");	
		}

		//checking for extra params
		for(int i = 0; i<paramListNode->numChildren; i++){
			tmpNode = nthChild(1, paramListNode);
			if(tmpNode->nodeType == NODE_parameter_list){
				getFunctionArgs(paramListNode, args);
			}
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
