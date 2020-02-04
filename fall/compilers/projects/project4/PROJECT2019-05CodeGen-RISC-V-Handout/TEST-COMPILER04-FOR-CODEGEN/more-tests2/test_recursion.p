PROGRAM test_recursion(input, output, error); 
VAR a, b: INTEGER;
VAR c: REAL;

FUNCTION fact(x:INTEGER) : INTEGER;
BEGIN
    if(x = 1) then
        fact := x
    else
        fact := x*fact(x-1)
END;

BEGIN
    a := fact(10);
    printInt(a);
END.
