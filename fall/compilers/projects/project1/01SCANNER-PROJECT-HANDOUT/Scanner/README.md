# Compiler Project 1: Scanner

## Introduction

For the first project of the semester, a scanner needed to be implemented by using the
Lex (or Flex) to create the scanner. First, we needed to define the codes for all the 
different possible symbols ( `+` and `while` for example). Then we specified the regular
expressions for the different symbols, as well as more complex types like integers, floats,
strings, and comments. These proved to be the most challenging.

## How to run

The same commands for running the instructions apply to this project, as only the Lex tool 
was used. First, use Lex/Flex:

`flex 0616110.l`

Then, the command might change a little bit depending on the OS. For Linux, you can then run:

`cc lex.yy.c -lfl`

Finally, we just use as input the contents of the .p files. For example: 

`./a.out < String.p`

Following should be a message for every token and the line number on which it appears. 
