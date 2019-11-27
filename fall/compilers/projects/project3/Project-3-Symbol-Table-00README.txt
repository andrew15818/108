README for the symbol table and semantics routines.



In the 3rd project, you need first to build an abstract syntax tree or translate the parse tree into an abstract syntax tree.  The file ast-node-for-project.pdf contains sample AST nodes. You should show me your abstract syntax tree on the computer screen.

For the 3rd part of the project, you also need to write code to process declarations and to build symbol tables. You code must print a message in the following occassions:

  1.  every time a new symbol is entered into the symbol table
  2.  every time a new scope is generated
  3.  every time a scope is closed
  4.  every time when a symbol table is created
  5.  every time when a symbol table is destroyed 
  6.  dump a symbol table when the symbol table is destroyed
  7.  dump all symbol tables at the end of the program

Appropriate information in each of the above occassions can also be printed.
For this 3rd project, you may assume the parser always succeeds. However, there could be errors in declarations. You need to print a message for each error. 

The directory testcases contains several test cases. Your program probably cannot find all errors in the test cases. However, your program should try to find as many errors as possible.


Here is a check list for your symbol-table implementation:

  1.  Declare two variables with identical names in two scopes.
      Can you find the appropriate variable when that name is 
      used in an expression?
  2.  Declare two variables with identical names in the same scope.
      Can you catch the duplicate declarations?
  3.  Declare a variable and a function with identical names in
      the same scope.
      Can you catch the duplicate declarations?
  3.  Declare a variable and a function with identical names in
      the differnt scopes.
      Can you find the appropriate usage when that name is 
      used?

There is no additional software tool for the third part of the project.


You compiler should check semantic errors. Common semantic errors include

1. undeclared variables
2. undeclared types  (not in this mini-pascal project)
3. undeclared functions  (not in this mini-pascal project)
4. undeclared classes  (not in this mini-pascal project)
5. arguments' types and numbers are wrong.
6. type errors in arithmetic expressions
7. redeclared variables
8. redeclared types  (not in this mini-pascal project)
9. redeclared functions
10. redeclared classes  (not in this mini-pascal project)
11. cycles in inheritance hierarchy  (not in this mini-pascal project)
12. cycles in structure containment  (not in this mini-pascal project)



For the 3rd (symbol table) project, you need to turn in your lex files, yacc files, semantic routine files, test cases, and the executable code. You also need to write a readme.txt file for the project, telling the TA how to run your program. You also need to turn in a file output.txt showing the output of your program. For the output, you can also show the screen dump (as a jpg file) when running your program.

Put all of the above files in a single zip file which will be named "DDDDDDD-symtab.zip", where
DDDDDDD is your student id. Upload the zip to the new e3 platform.

Deadline of the 3rd project is December 4, 2019, 23:55 pm.
--