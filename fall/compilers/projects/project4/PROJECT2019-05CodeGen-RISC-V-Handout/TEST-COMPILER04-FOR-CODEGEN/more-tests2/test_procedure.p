PROGRAM test_procedure(input, output, error); 
VAR a, b: INTEGER;
VAR c: REAL;

FUNCTION ss : INTEGER;
BEGIN
  ss := 3+4*5
END;

PROCEDURE tt;
BEGIN
    a := ss+33*ss;
    c := 0.5;
    printInt(a);
END;

BEGIN
    a := ss*ss+ss;
    printInt(a);
    tt;tt;tt
END.

