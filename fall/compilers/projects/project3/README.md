# Project 3: AST and parser

This project was rough. Just builing the AST took several days, 
and by the time that was done, there was too little time to try
and implement the symbol table itself. If you still want to try 
and run the program, the commands are: 

`yacc -d first.y`

followed by 

`flex 0616110-v2.l`

,

`cc symbolTable.c node.c lex.yy.c y.tab.c -ly`

, and lastly

`./a.out < input.p`. 

The ast values should at least be printed on the screen (with minimal indentation).
It should detect at least redeclarations, although scopes were not really 
implemented. 

