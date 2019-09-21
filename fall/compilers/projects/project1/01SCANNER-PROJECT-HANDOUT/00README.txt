README for the scanner project.




For the first part of the compiler project, we will implement a scanner. Our target language is {\it Mini-Pascal}, whose syntax is given in the file MINI-PASCAL-GRAMMAR.txt. Since we will use the lex tool, you will need to prepare the input for lex. 

Your work is to study MINI-PASCAL-GRAMMAR.txt and semantics-of-mini-pascal.txt and define the tokens used in the Mini-Pascal language. If you do not know how to start the project, please study the file SAMPLE1-standard-pascal-no-yacc.l or SAMPLE2-standard-pascal-need-yacc.l.

In particular, you need to add regular expressions for num, strings, and comments.

Comments in a program are marked with two slashes and continue to the end of the current line. For example,

           a := a + 1 ; // This is a comments

Comments may also be enclosed in the pair /* and */, such as

	/* hello, this is also a comment.  */

This comments may span multiple lines.  Your scanner should print a message for each comments.  Comments will not be returned to the parser.

A number could be prefixed with an optional positive/negative sign. A number could be an integer or a floating-point number. They both are considered as the token 'num'. You need to define the regular expression for a number in an appropriate way. You may even define the scientific notation, such as 10.3E+5.

Furthermore, in the Mini-Pascal grammar, there are string constants, such as "hello". A string is enclosed in a pair of double quotes. A string may not contain end-of-lines and double quotes unless they are properly escaped, as in C. On the other hand, there are no char type, no char variables, no char constants.  You need to define the regular expressions for strings in a reasonable way.

Please come to discuss with me if you need help.  Do not leave the project blank.

The list of tokens for Mini-Pascal includes the following tokens:



program
id
(
)
;
.
,
var
:
array
[
]
num
stringconst
of
integer
real
function
procedure
begin
end
:= (assignop)
if
then
else
while 
do
<
>
<=
>=
=
!=
+
-
*
/
not 
..



The GNU flex distribution is located at
	ftp://prep.ai.mit.edu/pub/gnu/
You may find the source there.  An easier way to obtain lex/yacc tools is to check the `flex&bison_for_Windows'' directory.


To generate a scanner, run the following commands:

>> flex SAMPLE1-standard-pascal-no-yacc.l
   The above command will generate a file named ``lex.yy.c''.
   Use a C compiler to compile the C file.

>> cc lex.yy.c -ll
   The above command will produce an executable file, say ``a.out''.
   Then execute the scanner:

>> a.out scanner-test01.p   (or "./a.out < scanner-test01.p")
 
The output of your scanner should be the list of the tokens produced by the scanner, together with the line number and character position in the line:

  0-th token(type:28) on line 1 : PROGRAM
  1-th token(type:39) on line 1 : mytest
  2-th token(type:52) on line 1 : (
  3-th token(type:39) on line 1 : input
  4-th token(type:43) on line 1 : ,
  5-th token(type:39) on line 1 : output
  ... 


>> The two files scanner-test01.p and scanner-test01-output.txt are a sample test file and the intended output.

>> The directory "Scanner 測資" contains more test cases.

>> Common problems in the scanner project:	
	1.  註解、字串和科學記號這三個比較常漏掉
	2.  input file寫死
	3.  資料夾沒有放置測試檔(test cases)


For the 1st (scanner) project, you need to turn in your lex files, yacc files (if you have one), semantic routine files, test cases, and the executable code. You also need to write a readme.txt file for the project, telling the TA how to run your program. You also need to turn in a file output.txt showing the output of your program. For the output, you can also show the screen dump (as a jpg file) when running your program.

Put all of the above files in a single zip file which will be named "DDDDDDD-scanner.zip", where
DDDDDDD is your student id. Upload the zip to the new e3 platform.

Deadline of the scanner project is October 2, 2019, 23:59 pm.

--
