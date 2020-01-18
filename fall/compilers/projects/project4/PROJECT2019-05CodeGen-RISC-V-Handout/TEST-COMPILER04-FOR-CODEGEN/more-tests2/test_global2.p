PROGRAM test_global2(input, output, error); 
VAR a, b: INTEGER;
VAR c: REAL;

FUNCTION tt : INTEGER;
VAR a, b : INTEGER;    // No error since the scope is different from global
BEGIN
  a := 3;
  b := a+4;
  tt := b
END;

BEGIN
    a := 3;
    b := 2;
    printInt(tt);
END.
