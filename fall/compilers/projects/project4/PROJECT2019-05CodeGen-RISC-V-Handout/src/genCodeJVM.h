#ifndef _CODEGEN_JVM_H_
#define _CODEGEN_JVM_H_
#include<stdio.h>
#include"symtab.h"
#include"node.h"
//create the file pointer to the output file
void initFile(const char* Filename);
//entry point to the code generation
void genCode(struct nodeType* node);
#endif
