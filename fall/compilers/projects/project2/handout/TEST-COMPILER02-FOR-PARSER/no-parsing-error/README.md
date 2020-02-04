# Introduction to Compiler Design Assignment 2

For this assignment, building off of where the first assignment left off,
we construct a parser which receives the tokens from the lex file and
checks whether it is a valid construction. We have to make some changes
to our .lex file so that it returns the correct values to the parser. Then,
we can check whether the program contains grammar errors.

Similar to the last assignment, we first compile the yacc file:

`yacc -d first.y`

Then, we compile our lex file too.

`lex 0616110.l`

Finally, we compile y.tab.h, which is the file made by yacc, and lex.yy.c, which is the 
one returned by lex. We compile them together and run the final executable.

`cc lex.yy.c y.tab.h -lfl`

To test the end, we redirect the testcase file  into the executable

`./a.out < sample_name.p`
