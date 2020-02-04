PROGRAM test_array(input, output, error); 
VAR a: ARRAY[1..2] of INTEGER;
VAR b: INTEGER;
VAR c: ARRAY[1..2] of ARRAY[1..2] of INTEGER;

FUNCTION ss(rr :INTEGER) : INTEGER;
BEGIN
  ss := rr
END;

BEGIN
  a[1] := 1;
  a[2] := 1;
  c[1][1] := 1;
  c[1][2] := 2;
  c[2][1] := 3;
  c[2][2] := 1;
  c[ss(c[ss(1)][ss(2)])][c[ss(a[1])][a[2]]] := a[ss(a[ss(a[1])])];
  printInt(c[2][1]);
END.

