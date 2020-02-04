#include <stdio.h>
#include <stdlib.h>
#include "symtab.h"
#include <string.h>

FILE* pFile;
char* progName;
int branch=0;
int levelCount=0;
int curLevel=0;
int c0=0;
int countStrings=1;
char** strings;
void codeGen(struct nodeType* node, int scope);
int strC=1;
void codeStart (struct nodeType *node, FILE*ptr)
{
    pFile=ptr;
    codeGen(node,0);
}

void codeGen(struct nodeType *node,int scope) {
    printf("--------------------------Code GEN-----------------------------------\n");
    //printf("test:%d\n", node->nodeType);
    switch(node->nodeType) {
    	case NODE_prog:{
			progName=node->string;
			fprintf(pFile,".class public %s\n",progName);
			fprintf(pFile,".super java/lang/Object\n");
			fprintf(pFile,"\n");
			struct SymTable* Table=ScopeStack[scope];
			//.field public static a I
			for(int i=0;i<Table->size;i++){
				if(Table->entries[i].dtype == Array || Table->entries[i].dtype == Variable){
					fprintf(pFile, ".field public static %s ",Table->entries[i].name );
	                for(int j=0;j<Table->entries[i].Arraydim;j++) fprintf(pFile, "[" );  
	            	if(Table->entries[i].type == TypeInt ) fprintf(pFile, "I" );
	            	else fprintf(pFile, "F" );
	            	fprintf(pFile, "\n");
				}
			}
			//goto NODE_declarations
			struct nodeType *child=nthChild(1,node);
			if(Table->size != 0){
				fprintf(pFile, ".method public static vinit()V\n");
				fprintf(pFile, "\t.limit locals 100\n");
				fprintf(pFile, "\t.limit stack 100\n");
				codeGen(child,0);
				fprintf(pFile, "\treturn\n");
	        	fprintf(pFile, ".end method\n");
			}
			//std initializer
			//fprintf(pFile, "; standard initializer\n");
			fprintf(pFile, ".method public <init>()V\n");
			fprintf(pFile, "\taload_0\n");
			fprintf(pFile, "\tinvokenonvirtual java/lang/Object/<init>()V\n");
			fprintf(pFile, "\treturn\n");
			fprintf(pFile, ".end method\n");
			//goto NODE_subprogram_declarations
			child=nthChild(2,node);
			codeGen(child,scope);
			//goto NODE_compound_statement
			fprintf(pFile, ".method public static main([Ljava/lang/String;)V\n");
			fprintf(pFile, "\t.limit locals 100\n");
			fprintf(pFile, "\t.limit stack 100\n");
			int flag=0;
			//if There is global variable
			if(Table->size != 0){
				for(int i=0;i<Table->size;i++){
					if(Table->entries[i].dtype == Variable || Table->entries[i].dtype == Array) {
						flag=1;
						break;
					}
				}
				//invokestatic foo/vinit()V
				if(flag) fprintf(pFile, "\tinvokestatic %s/vinit()V\n",progName);
			}
			child=nthChild(3,node);
			printf("type:%d\n",child->nodeType );
		 	printf("going where?\n");
			codeGen(child,scope);
			fprintf(pFile,"\treturn\n");
			fprintf(pFile,".end method");
			//break;
			return;
		}	
        //Variables and Array appear here
        case NODE_declarations: {
        	struct SymTable* Table=ScopeStack[scope];
        	if(Table->size != 0){
        		for(int i=0;i<Table->size;i++){
        			if(!(Table->entries[i].dtype == Function || Table->entries[i].dtype == Procedure)&& !Table->entries[i].par_flag){
        				if(Table->entries[i].dtype != Array){
		        			if(Table->entries[i].type == TypeInt){
		        				
		        				fprintf(pFile, "\tldc 0\n");
		        				if(scope == 0) fprintf(pFile, "\tputstatic %s/%s I\n",progName,Table->entries[i].name );
		        				else fprintf(pFile, "\tistore %d\n",Table->entries[i].Seq);
		        			}
		        			else{
		        				
		        				fprintf(pFile, "\tldc 0.0\n");
		        				if(scope == 0) fprintf(pFile, "\tputstatic %s/%s F\n",progName,Table->entries[i].name );
		        				else fprintf(pFile, "\tfstore %d\n",Table->entries[i].Seq);
		        			}
		        		}
		        		else if (Table->entries[i].dtype == Array){
		        			char tail[20]={};
		        			for(int j=0;j<Table->entries[i].Arraydim;j++) fprintf(pFile,"\tbipush %d\n",Table->entries[i].Arraysize[j]-Table->entries[i].Arrayinit[j]+1);
		        			//multianewarray [I 1

		        			fprintf(pFile, "\tmultianewarray ");
		        			for(int j=0;j<Table->entries[i].Arraydim;j++){
		        				fprintf(pFile, "[");
		        				strcat(tail,"[");
		        			}
		        			if(Table->entries[i].type == TypeInt) {
		        				fprintf(pFile, "I ");
		        				strcat(tail, "I");
		        			}
		        			else {
		        				fprintf(pFile, "F ");
		        				strcat(tail, "F");
		        			}
		        			fprintf(pFile, "%d\n",Table->entries[i].Arraydim);
		        			//putstatic foo/d [I
		        			if(scope == 0 ){
		        				fprintf(pFile, "\tputstatic %s/%s %s\n",progName,Table->entries[i].name,tail );
			        		
		        			}
		        			else fprintf(pFile, "\tastore %d\n",Table->entries[i].Seq);
							strcpy(Table->entries[i].funtail,tail);
		        		}
        			}	
	        	}
	        	
        	}
        	return;
            //break;
        }
        //Function and Procedure appear here
        case NODE_subprogram_declaration:{
            //OpenScope();

            levelCount ++;
            curLevel++;
            scope = levelCount ;
            ScopeStack[scope]->status=1;
            printf("levlecnt:%d\n",levelCount  );
            break;
        }
        case NODE_subprogram_head:{
        	//level++;//enter a new scope
        	//assume funtions/procedures can only be declared in global scope
            struct SymTable* Table=ScopeStack[0];
            //get funtcion name
            struct nodeType *idNode = nthChild(1, node);
            for(int i=0;i<Table->size;i++){
            	//if((Table->entries[i].dtype==Function || Table->entries[i].dtype==Procedure)&&(strcmp(Table->entries[i].name,"writeln")) ){
            		if(!strcmp(idNode->string,Table->entries[i].name)){
            		//.method public static ggyy(FF)F
					char tail[20]={};
            		fprintf(pFile, ".method public static %s(",Table->entries[i].name);
            		struct Parameters* Pptr=Table->entries[i].Pptr;
            		while(Pptr != NULL){
            			//fprintf(pFile,"loop1\n");
            			for(int j=0;j<Pptr->Parnum;j++){
            				//fprintf(pFile, "parnum:%d\n",Pptr->Parnum);
            				if(Pptr->Aptr != NULL) {
            					for(int j=0;j<Pptr->Aptr->Arraydim;j++) {
            						fprintf(pFile,"[");
            						strcat(tail,"[");
            					}
            				}
            				if(Pptr->type == TypeInt ){
            					fprintf(pFile,"I");
            					strcat(tail,"I");
            				}
            				else {
            					fprintf(pFile,"F");
            					strcat(tail,"F");
            				}
            				printf("end\n");
            			}
            			Pptr=Pptr->next;
            		}
            		fprintf(pFile, ")");
            		strcat(tail,")");
            		if(Table->entries[i].type == TypeInt) {
            			fprintf(pFile, "I\n");
            			strcat(tail,"I");
            		}
            		else if(Table->entries[i].type == TypeNull) {
            			fprintf(pFile, "V\n");
            			strcat(tail,"V");
            		}
            		else {
            			fprintf(pFile, "F\n");
            			strcat(tail,"F");
            		}
            		strcpy(Table->entries[i].funtail,tail);
            		//Table->entries[i].funtail=tail;
            		//fprintf(pFile, "funtail:%s\n",tail );
					fprintf(pFile, ".limit locals 100\n");
					fprintf(pFile, ".limit stack 100\n");
            	}	
            }
            //scope = level;
            //break;
            return;
        }
        case NODE_END:{
        	//fprintf(pFile, "END here\n");
            //Do things only for Procedure/Function
            //fload 2
			//freturn
			//.end method
			struct SymTable* Table=ScopeStack[scope];
			for(int i=0;i<ScopeStack[0]->size;i++){
				if(!strcmp(Table->name,ScopeStack[0]->entries[i].name)){
					if(!(ScopeStack[0]->entries[i].dtype == Function || ScopeStack[0]->entries[i].dtype == Procedure)) return;
					if(ScopeStack[0]->entries[i].type != TypeNull){//Procedure has no return type
						char head='\0';
						for(int j=0;j<Table->size;j++){
							if(!strcmp(Table->name,Table->entries[j].name)){
								if(Table->entries[j].type == TypeInt) head='i';
								else head='f';
								fprintf(pFile, "\t%cload %d\n",head,Table->entries[j].Seq );
								break;
							}
						}
						 printf("-------%c\n",head);
						if(head!='\0')fprintf(pFile, "\t%creturn\n",head);
						else  fprintf(pFile, "\treturn\n");
						
					}
					else {
						fprintf(pFile, "\treturn\n");
						printf("-------return");
					}
					fprintf(pFile, ".end method\n");
				}
				
			}
			if(scope != 0) ScopeStack[scope]->status=0;
			curLevel--;
            return;
        }
        //lots of statements
        case NODE_compound_statement:{
        	
        	//return;
        	break;
        }
        //Nullstmt
        case NODE_statement:{
        	
        	//return;
        	break;
        }
        //If...else... 
        case NODE_if:{
        	//NODE_expression
        	struct nodeType *expNode = nthChild(1, node);
        	codeGen(expNode,scope);
        	//ELSEstmt
        	struct nodeType *stmtNode = nthChild(2, node);
        	codeGen(stmtNode,scope);
        	fprintf(pFile, "\tgoto L%d\n",expNode->branch+1);
        	//IFstmt
        	fprintf(pFile, "L%d:\n",expNode->branch );
        	stmtNode = nthChild(3, node);
        	codeGen(stmtNode,scope);
        	fprintf(pFile, "L%d:\n",branch);
        	branch++;

        	return;
        }
        //whild..do.
        case NODE_while:{
        	int mybranch=branch;
        	fprintf(pFile, "L%d:\n",branch );
        	branch++;
        	//NODE_expression
        	struct nodeType *expNode = nthChild(1, node);
        	codeGen(expNode,scope);
        	//Dostmt
        	struct nodeType *stmtNode = nthChild(2, node);
        	codeGen(stmtNode,scope);
        	fprintf(pFile, "\tgoto L%d\n",mybranch);
        	//Notdostmt
        	fprintf(pFile, "L%d:\n",expNode->branch );

        	return;
        }
        //ID or ID(....)
        case NODE_procedure_statement:{
        	struct nodeType *idNode = nthChild(1, node);
			struct nodeType *argNode = nthChild(2, node);
        	//For writeln
        	if(!strcmp(idNode->string,"writeln")){
        		//invokestatic java/lang/String/valueOf(I)Ljava/lang/String;
        		//getstatic foo/a I
        		fprintf(pFile, "\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n");
        		if(argNode->valueType == TypeChar ||argNode->valueType == TypeString){
        			fprintf(pFile, "\tldc %s\n",argNode->string );
        		}
        		else{
        			if(argNode->valueType == TypeInt){
        				fprintf(pFile,"\tgetstatic %s/%s I\n",progName,argNode->string);
        				fprintf(pFile,"\tinvokestatic java/lang/String/valueOf(I)Ljava/lang/String;\n");
        			}
        			else {
        				fprintf(pFile,"\tgetstatic %s/%s F\n",progName,argNode->string);
        				fprintf(pFile,"\tinvokestatic java/lang/String/valueOf(F)Ljava/lang/String;\n");
        			}
        			
        		}
        		fprintf(pFile,"\tinvokevirtual java/io/PrintStream/println(Ljava/lang/String;)V\n");
        		return;
        	}
        	//for normal function 
			//recursive search for arguments
			while(argNode != NULL  && argNode != node->child) {
				codeGen(argNode,scope);
			 	argNode=argNode->child;
			}
			char tail[20]={};
			for(int i=0;i<ScopeStack[0]->size;i++){
			 	if(!strcmp(idNode->string,ScopeStack[0]->entries[i].name)){
			 		//tail=ScopeStack[0]->entries[i].funtail;
			 		strcpy(tail,ScopeStack[0]->entries[i].funtail);
			 	}
			}
			//fprintf(pFile, "IN procedures\n" );
            fprintf(pFile, "\tinvokestatic %s/%s(%s\n",progName,idNode->string,tail);
            return;
        }

        case NODE_parameter_list:{
            
            break;
        }
        case NODE_ID: {//Identifier appear at right hand_side        	
            struct SymTableEntry *entry = findSymbol(node->string);
            //haven't consider array
            printf("in id node\n");
            //If ID is a Function
            if(entry->dtype == Function || entry->dtype == Procedure ){
            	//invokestatic foo/addition(II)I
				struct nodeType *argNode = nthChild(1, node);
            	//while(argNode != NULL) {
            	for(int i=0;i<entry->Par_set;i++){
            		if(argNode->dtype == Function){
            			printf("loop1\n");
            			int set;
            			for(int j=0;j<ScopeStack[0]->size;j++){
							printf("loop3---%d--%d\n",j,ScopeStack[0]->size);
            				if(!strcmp(argNode->string,ScopeStack[0]->entries[j].name)){
            					set=ScopeStack[0]->entries[j].Par_set;
            				}
            			}
            			//not finished
						printf("%s\n",argNode->string);
            			codeGen(argNode,scope);
            			i+=set;
            			for(int j=set;j>=0;j--) {
							if(argNode->child==NULL) break;
            				argNode=argNode->child;
							
							printf("%d\n",argNode->nodeType);
							
            				printf("loop2 %d\n",j);
            			}
            		}
	            	printf("going to argnode %s %d\n",argNode->string,argNode->nodeType);
					codeGen(argNode,scope);
				 	argNode=argNode->child;
				}
				printf("came back from argnode\n");
				char tail[20]={};
				strcpy(tail,entry->funtail);

				/*for(int i=0;i<ScopeStack[0]->size;i++){
				 	if(!strcmp(idNode->string,ScopeStack[0]->entries[i].name)){
				 		tail=ScopeStack[0]->entries[i].funtail;
				 	}
				}*/
				//fprintf(pFile, "IN iD\n" );
	            fprintf(pFile, "\tinvokestatic %s/%s(%s\n",progName,entry->name,tail);
	            return;
            }
            if(entry->dtype != Array){
            	if(entry->scope !=0){
            		//If it is a recursive function
            		if(!strcmp(entry->name,ScopeStack[entry->scope]->name)){
            			char tail[20]={};
            			for(int i=0;i<ScopeStack[0]->size;i++){
            				if(!strcmp(ScopeStack[0]->entries[i].name,entry->name)){
            					entry = &ScopeStack[0]->entries[i];
            					//entry->type = ScopeStack[0]->entries[i].type;
		                        //entry->dtype = ScopeStack[0]->entries[i].dtype;
		                        //entry->Pptr = ScopeStack[0]->entries[i].Pptr;
		                        node->dtype = ScopeStack[0]->entries[i].dtype;
		                        node->valueType = ScopeStack[0]->entries[i].type;
		                        //fprintf(pFile, "Valuetype:%d\n",node->valueType );
		                        strcpy(tail,ScopeStack[0]->entries[i].funtail);
            				}
            			}
            			struct nodeType *argNode = nthChild(1, node);
		            	//while(argNode != NULL) {
		            	for(int i=0;i<entry->Par_set;i++){
		            		if(argNode->dtype == Function){
		            			//fprintf(pFile, "is Function\n");
		            			int set;
		            			for(int j=0;j<ScopeStack[0]->size;i++){
		            				if(!strcmp(argNode->string,ScopeStack[0]->entries[j].name)){
		            					set=ScopeStack[0]->entries[j].Par_set;
		            				}
		            			}
		            			//not finished
		            			codeGen(argNode,scope);
		            			i+=set;
		            			for(int j=set;j>=0;j--) argNode=argNode->child;
		            		}
							codeGen(argNode,scope);
						 	argNode=argNode->child;
						}
						
						//strcpy(tail,entry->funtail);

			            fprintf(pFile, "\tinvokestatic %s/%s(%s\n",progName,entry->name,tail);
			            return;
            		}
					if(entry->type == TypeInt) fprintf(pFile, "\tiload %d\n",entry->Seq);
					else fprintf(pFile, "\tfload %d\n",entry->Seq);
				}
				else{
					if(entry->type == TypeInt) fprintf(pFile, "\tgetstatic %s/%s I\n",progName,entry->name );
					else fprintf(pFile, "\tgetstatic %s/%s F\n",progName,entry->name );
				}
            }
            //else if ID is an Array
           	if(entry->dtype == Array){
            	if(entry->scope !=0){
					//if(entry->type == TypeInt) fprintf(pFile, "\tiload %d\n",entry->Seq);
					//else fprintf(pFile, "\tfload %d\n",entry->Seq);
					fprintf(pFile, "\taload %d\n",entry->Seq);
				}
				else fprintf(pFile, "\tgetstatic %s/%s %s\n",progName,entry->name,entry->funtail );
           		struct nodeType *argNode = nthChild(1, node);
           		
           		struct nodeType *tailNode = nthChild(2, argNode);
           		argNode = nthChild(1,argNode);
            	int count=0;
				//while(argNode->nodeType != NODE_tail){
				while(tailNode != NULL){
					//for(int i=0;i<entry->Arraydim;i++){
					codeGen(argNode,scope);
					fprintf(pFile,"\tldc %d\n",entry->Arrayinit[count]);
					fprintf(pFile, "\tisub\n");
					if(count != entry->Arraydim-1) fprintf(pFile, "\taaload\n");
					//}
					argNode = nthChild(1, tailNode);
					tailNode = nthChild(2,tailNode);
					count++;
				}	
           		if(entry->type == TypeInt) fprintf(pFile, "\tiaload\n");
           		else fprintf(pFile, "\tfaload\n");
            }   
                 
            		
            return;
        }    
        case NODE_SYM_REF:{
			//haven't consider array
			struct SymTableEntry *entry = findSymbol(node->string);

			if(entry->dtype == Array){
				if(entry->type == TypeInt) fprintf(pFile, "\tiastore\n");
				else fprintf(pFile, "\tfastore\n");
				return;
			}
			if(entry->scope !=0){
				if(entry->type == TypeInt) fprintf(pFile, "\tistore %d\n",entry->Seq);
				else fprintf(pFile, "\tfstore %d\n",entry->Seq);
			}
			else{
				fprintf(pFile, "\tputstatic %s/%s ",progName,entry->name );
				if(entry->dtype == Array){
					fprintf(pFile, "%s\n",entry->funtail );
				}
				else{
					if(entry->type == TypeInt) fprintf(pFile, "I\n");
					else fprintf(pFile, "F\n");
				}	
			}
				
			return;
		}
        case NODE_NUM: {
			printf("in node NUM\n");
            if(node->valueValid == VALUE_I_VALID) fprintf(pFile, "\tldc %d\n",node->iValue );      
            else fprintf(pFile, "\tldc %f\n",node->rValue ); 

            return;
        }
        case NODE_String: {
            fprintf(pFile, "\tldc %s\n",node->string );         
            return;
        }
        case NODE_Char: {
            fprintf(pFile, "\tldc %s\n",node->string );        
            return;
        }
        case NODE_OP:{
			char head;
			//goto OP1
			struct nodeType* child=nthChild(1,node);
			codeGen(child, scope);
			//goto OP2
			child=nthChild(2,node);
			codeGen(child, scope);

			if(node->valueType == TypeInt) head = 'i';
			else head = 'f';
				
			switch(node->op){
				case OP_PLUS:
					fprintf(pFile, "\t%cadd\n",head);
				break;
				case OP_MINUS:
					fprintf(pFile, "\t%csub\n",head);
				break;
				case OP_MUL:
					fprintf(pFile, "\t%cmul\n",head);
				break;
				case OP_SLASH:
					fprintf(pFile, "\t%cdiv\n",head);
				break;
				case OP_LT://<
					if(child->valueType == TypeInt) {
						fprintf(pFile, "\tif_icmpge L%d\n",branch );
					}
					else {
						fprintf(pFile, "\tfcmpl\n");
						fprintf(pFile, "\tifge L%d\n",branch);
					}
					node->branch=branch;
					branch++;
				break;
				case OP_GT://>
					if(child->valueType == TypeInt) {
						fprintf(pFile, "\tif_icmple L%d\n",branch);
					}
					else {
						fprintf(pFile, "\tfcmpl\n");
						fprintf(pFile, "\tifle L%d\n",branch);
					}
					node->branch=branch;
					branch++;
				break;
				case OP_LE://<=
					if(child->valueType == TypeInt) {
						fprintf(pFile, "\tif_icmpgt L%d\n",branch );
					}
					else {
						fprintf(pFile, "\tfcmpl\n");
						fprintf(pFile, "\tifgt L%d\n",branch);
					}
					node->branch=branch;
					branch++;
				break;
				case OP_GE://>=
					if(child->valueType == TypeInt) {
						fprintf(pFile, "\tif_icmplt L%d\n",branch);
					}
					else {
						fprintf(pFile, "\tfcmpl\n");
						fprintf(pFile, "\tiflt L%d\n",branch);
					}
					node->branch=branch;
					branch++;
				break;
				case OP_EQUAL://=
					if(child->valueType == TypeInt) {
						fprintf(pFile, "\tif_icmpne L%d\n",branch);
					}
					else {
						fprintf(pFile, "\tfcmpl\n");
						fprintf(pFile, "\tifne L%d\n",branch);
					}
					node->branch=branch;
					branch++;
				break;
				case OP_notEQUAL://!=
					if(child->valueType == TypeInt) {
						fprintf(pFile, "\tif_icmpeq L%d\n",branch);
					}
					else {
						fprintf(pFile, "\tfcmpl\n");
						fprintf(pFile, "\tifeq L%d\n",branch);
					}
					node->branch=branch;
					branch++;
				break;

			}
			//break;
			return;
		}

        /* You should check the LHS of assign stmt is assignable
           You should also report error if LHS is a function with no parameter 
           (function is not implemented in this sample, you should implement it) */ 
        case NODE_ASSIGNMENT: {
        	printf("assignment node\n");
			struct nodeType *child2 = nthChild(2, node);
            struct nodeType *child1 = nthChild(1, node);
            if(child1->dtype == Array){
            	struct SymTableEntry *entry = findSymbol(child1->string);
            	struct nodeType *argNode = nthChild(1, child1);
            	
            	struct nodeType *tailNode = nthChild(2, argNode);
            	argNode= nthChild(1,argNode);
            	//getstatic foo/d [I
            	//fprintf(pFile, "entry:%s funtail:%s\n",entry->name,entry->funtail );
            	if(entry->scope == 0) fprintf(pFile,"\tgetstatic %s/%s %s\n",progName,child1->string,entry->funtail );
            	else {
            		if(entry->dtype == Array) fprintf(pFile, "\taload %d\n",entry->Seq);
					else{
						if(entry->type == TypeInt) fprintf(pFile, "\tiload %d\n",entry->Seq);
						else fprintf(pFile, "\tfload %d\n",entry->Seq);	
					}
					
            	}
            	//Array
				int count=0;
				//while(argNode->nodeType != NODE_tail){
				while(tailNode != NULL){
					//for(int i=0;i<entry->Arraydim;i++){
					codeGen(argNode,scope);
					fprintf(pFile,"\tldc %d\n",entry->Arrayinit[count]);
					fprintf(pFile, "\tisub\n");
					if(count != entry->Arraydim-1) fprintf(pFile, "\taaload\n");
					//}

					argNode = nthChild(1, tailNode);
					tailNode= nthChild(2,tailNode);
					count++;
				}	
            }
            //goto NODE_expression
            codeGen(child2,scope);
            //goto NODE_SYM_REF   
            codeGen(child1,scope);
            
            
            //break;
            return;
        }
        default:{
            //printf("unknown node:%d\n",node->nodeType );
        }
    }

    /* Default action for other nodes not listed in the switch-case */
    struct nodeType *child = node->child;
    if(child != 0) {
        do {
        	//fprintf(pFile,"now:%d\n",child->nodeType );
            codeGen(child,scope);
            child = child->rsibling;
            //fprintf(pFile,"right sibling:%d\n",child->nodeType);
        } while(child != node->child);
    }
}
