#include<stdio.h>
#include "genCode.h"
FILE *fp;
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
	fprintf(fp, function_Prepare_Main);
}
/*call this before every function*/
void emitFunction(const char* function_Name)
{
	fprintf(fp,"%s\n"
			"\t.text\n"
			"\t.align 1\n"
			"\t.globl %s\n"
			"\t.type %s, @function\n",function_Name ,function_Name, function_Name
	);
	//fprintf(fp, function_Name);
	//fprintf(fp, "\n");
	//fprintf(fp, function_prepare);
}
void genCode(struct nodeType* node)
{
	switch(node->nodeType){
			case NODE_prog:
				printf("GC: NODE_prog\n");
				openFile();
				emitPrepareMain();
				emitFunction(node->string);
				genCode(nthChild(1, node));		
				genCode(nthChild(2, node));
				genCode(nthChild(3, node));

				break;	
			case NODE_declarations:
				printf("GC: NODE_delcarations\n");
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
				break;
			case NODE_subprogram_declaration:
				printf("GC: NODE_subprogram_declaration\n");
				break;
			case NODE_subprogram_head:
				printf("GC: NODE_subprogram_head\n");
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
				printf("GC: NODE_identifier_list\n");
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
				break;
			case NODE_statement_list:
				printf("GC: NODE_statement_list\n");
				break;
			default:
				printf("Cannot generate code for for type : %d\n", node->nodeType);	
				break;
	}
}
