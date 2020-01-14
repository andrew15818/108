#include<stdio.h>
#include "genCode.h"
#include "symtab.h"
FILE *fp;
struct SymTable* symbolTable;
const char* filename = "./output.s";
/*opening output file*/
void openFile()
{
	fp = fopen(filename, "w");
}
/*This code goes before the main function*/

void emitPrepareMain()
{
	const char* function_Prepare_Main=
			" #pre main code\n"
			".text \n"
			".section .rodata \n"
			".align 3 \n";
	fprintf(fp,"%s\n" ,function_Prepare_Main);
}

/*call this before every function*/
void emitFunctionPrelude(const char* function_Name, struct SymTable* symTable)
{
	fprintf(fp,
			"\t.text\n"
			"\t.align 1\n"
			"\t.globl %s\n"
			"\t.type %s, @function\n",function_Name, function_Name
	);
<<<<<<< HEAD



}
void emitAdd()
{
	fprintf(fp,
	"lw al, 0(s0) #pop from TOS\n"
	"addi s0, s0, -4 #making space for an integer\n"
	"lw, a2, 0(s0)\n"
	"addi s0, s0, -4\n"
	"add a3, a1, a2\n"
	"sw a3, 0(s0)\n"
	"addi s0, 4\n"
	);
=======
	fprintf(fp,"%s:\n", function_Name);
	int frameSize = 1024;
	int wordSize = 4;//the standard unit is fo size 4 bits
	fprintf(fp,
		"\taddi sp, sp, -%d\n" //size of the stack
		"\tsd ra, %d(sp)\n" // storing return address
		"\tsd s0, %d(sp)\n" //in mem after s0 we store local variables
		"\tsd s1, %d(sp)\n" //
		"\taddi s0, sp, %d\n"
		"\taddi s1,sp,0\n"
		,frameSize
		,frameSize -(frameSize-2*wordSize)
		,frameSize -(frameSize-4*wordSize)
		,frameSize -(frameSize - 6*wordSize)
		,40 /*change this*/);
>>>>>>> 6e996d97d17399b17c45186a53457b3f53f1de26
}
void genCode(struct nodeType* node)
{
	switch(node->nodeType){
			case NODE_prog:
			;
				symbolTable = ScopeStack[0];
				printf("GC: NODE_prog\n");
				openFile();
				emitPrepareMain();
<<<<<<< HEAD
				printf("\emitting code\n");
				emitFunction(node->string);
=======
				emitFunctionPrelude(node->string, symbolTable);
>>>>>>> 6e996d97d17399b17c45186a53457b3f53f1de26
				genCode(nthChild(1, node));		
				genCode(nthChild(2, node));
				genCode(nthChild(3, node));
				//printf("name of main program: %s\n", node->string);
				break;	
			case NODE_declarations:
				printf("GC: NODE_delcarations\n");
<<<<<<< HEAD
				//genCode(nthChild(1, node));
				genCode(nthChild(2, node));
				genCode(nthChild(3, node));
=======
				struct NodeType* declarationsNode = nthChild(1, node);
				struct NodeType* IDListNode = nthChild(2, node);
				struct NodeType* typeNode = nthChild(3, node);
				genCode(IDListNode);
>>>>>>> 6e996d97d17399b17c45186a53457b3f53f1de26
				break;
			case NODE_NUM:
				printf("GC: NODE_NUM\n");
				break;
			case NODE_String:
				printf("GC: NODE_String\n");
				break;
			case NODE_Char:
				printf("GC: NODE_CHAR\n");
				break;
			case NODE_TYPE_ARRAY:
				printf("GC: NODE_TYPE_Array\n");
				break;
			case NODE_TYPE_INT:
				printf("GC: NODE_TYPE_INT\n");
				break;
			case NODE_TYPE_REAL:
				printf("GC: NODE_TYPE_REAL\n");
				break;
			case NODE_TYPE_STRING:
				printf("GC: NODE_TYPE_STRING\n");
				break;
			case NODE_TYPE_CHAR:
				printf("GC: NODE_TYPE_CHAR\n");
				break;
			case NODE_subprogram_declarations:
				printf("GC: NODE_subprogram_declarations\n");

<<<<<<< HEAD
=======
				struct nodeType* child1 =nthChild(1, node);
				
				struct nodeType* child2 =nthChild(2, node);
				if(child1 != NULL){
					printf("\t genning code for child 1");
					genCode(child1);
				}
				else if(child2 !=NULL){
					printf("\tgenne3ing code for child 2\n ");
					genCode(child2);
				}
>>>>>>> 6e996d97d17399b17c45186a53457b3f53f1de26
				break;
			case NODE_subprogram_declaration:
				printf("GC: NODE_subprogram_declaration\n");
				genCode(nthChild(0, node));
				genCode(nthChild(2, node));
				genCode(nthChild(3, node));
				break;
			case NODE_subprogram_head:
				;
				printf("GC: NODE_subprogram_head\n");
				struct nodeType* nameNode = nthChild(0, nameNode);
				struct SymTableEntry* tmpEntry = findSymbol(nameNode->string);
				if(tmpEntry != NULL)printf("\t found the name: %s\n", tmpEntry->name);
				else{printf("\t name of method not found yet\n");}
				break;
			case NODE_ASSIGNMENT:
				printf("GC: NODE_ASSIGNMENT\n");
				break;
			case NODE_SYM_REF:
				printf("GC: NODE_SYM_REF\n");
				break;
			case NODE_statement:
				printf("GC: NODE_statement\n");
				break;
			case NODE_variable:
				printf("GC: NODE_variable\n");
				break;
			case NODE_tail:
				printf("GC: NODE_tail\n");
				break;
			case NODE_procedure_statement:
				printf("GC: NODE_procedure_statement\n");
				break;
			case NODE_expression:
				printf("GC: NODE_expresion\n");
				break;
			case NODE_factor:
				printf("GC: NODE_factor\n");
				break;
			case NODE_OP:
				printf("GC: NODE_OP\n");
				break;

			case NODE_TOKEN:
				printf("GC: NODE_TOKEN\n");
				break;
			case NODE_parameter_list:
				printf("GC: NODE_parameter_list\n");
				break;
			case NODE_identifier_list:
<<<<<<< HEAD
			;
				struct NodeType* IdNode = nthChild(1, node);
				if(IdNode == NULL){
					printf("child of ID node is NULL\n");
				}
				
				printf("GC: NODE_identifier_list\n");
=======
				printf("GC: NODE_IDidentifier_list\n");

>>>>>>> 6e996d97d17399b17c45186a53457b3f53f1de26
				break;
			case NODE_ID:
				printf("GC: NODE_ID\n");
				break;
			case NODE_FUNCTION:
				printf("GC: NODE_FUNCTION\n");
				break;
			case NODE_PROCEDURE:
				printf("GC: NODE_PROCEDURE\n");
				break;
			case NODE_END:
				printf("GC: NODE_END\n");
				break;
			case NODE_arguments:
				printf("GC: Node_arguments\n");
				break;
			case NODE_if:
				printf("GC: NODE_if\n");
				break;
			case NODE_while:
				printf("GC: NODE_while\n");
				break;
			case NODE_compound_statement:
				printf("GC: NODE_compound_statement\n");
				genCode(nthChild(1, node));
				break;
			case NODE_statement_list:
				printf("GC: NODE_statement_list\n");
				struct nodeType* firstChild = node->child;
				while(firstChild->nodeType != firstChild->rsibling->nodeType){
						genCode(firstChild);
						firstChild = firstChild->rsibling;
				}
				break;
			case OP_PLUS:
				printf("GC: plus op\n");
				break;
			default:
				printf("Cannot generate code for for type : %d\n", node->nodeType);	
				break;
	}
}
