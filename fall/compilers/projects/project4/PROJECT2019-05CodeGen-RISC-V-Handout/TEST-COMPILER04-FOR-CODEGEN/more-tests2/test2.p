PROGRAM test2(aaa,bbb,ccc);
VAR aa,bb,cc : INTEGER;
VAR g: ARRAY[0..1] of ARRAY[2..3] of ARRAY[4..5] of INTEGER;
VAR r: ARRAY[0..1] of  ARRAY[4..5] of INTEGER;

PROCEDURE ss;
VAR z : INTEGER;
BEGIN
END;

FUNCTION tt(a, b: integer;c,d: real ) : INTEGER;
VAR z : INTEGER;
BEGIN
z := 3 + 4*5;
printInt(z);
tt := a + 5;
END;


BEGIN
    aa := aa+3*bb-(4/2);
    
    printInt(aa);
    printInt(bb);
    
    //nested if
    if aa <= bb 
    then if aa < 0 then aa := 333 else aa := 111
    else aa := 222;
    
    printInt(aa);
    
    //nested while
    while bb < 5 do
    begin
    	aa := 0;
    	while aa < 5 do
    	begin
    		aa := aa + 1;
    	end;
    	bb := bb +1;
    	printInt(bb);
    end;
    
    g[0][3][4] := aa+r[1][4] + tt(2,3,4.0,6.5);
    printInt(g[0][3][4]);
END.

