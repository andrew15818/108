program knight_tour(void);
// solving knight's tour problem using backtracking algorithm
// see https://www.geeksforgeeks.org/backtracking-set-1-the-knights-tour-problem/
var sol: array[0..7] of array[0..7] of integer;
var xMove, yMove: array[0..7] of integer;
var x, y : integer;

procedure solveKT(start_x, start_y: integer);
var x, y : integer;
begin
    for x:= 0 to 7 do
        for y:= 0 to 7 do
            sol[x][y] := -1;
    xMove[0] := 2;
    xMove[1] := 1;
    xMove[2] := -1;
    xMove[3] := -2;
    xMove[4] := -2;
    xMove[5] := -1;
    xMove[6] := 1;
    xMove[7] := 2;

    yMove[0] := 1;
    yMove[1] := 2;
    yMove[2] := 2;
    yMove[3] := 1;
    yMove[4] := -1;
    yMove[5] := -2;
    yMove[6] := -2;
    yMove[7] := -1;

    sol[start_x][start_y] := 0;

    if not solveKTUtil(start_x, start_y, 1) then
        printString("Solution does not exist")
    else 
        printSolution;

end;

procedure printSolution;
var x, y : integer;
begin
    for x:= 0 to 7 do
    begin
        for y:= 0 to 7 do
        begin
            printString(" ");
            printInt(sol[x][y]);
        end;
        printlnString(" ");
    end
end;

function solveKTUtil(x, y, movei: integer): integer;
var k, next_x, next_y : integer;
begin
    if movei = 64 then
        solveKTUtil := 1
    else begin end;

    for k:= 0 to 7 do
    begin
        next_x := x + xMove[k];
        next_y := y + yMove[k];
        if isSafe(next_x, next_y) then
        begin
            sol[next_x][next_y] := movei;
            if solveKTUtil(next_x, next_y, movei + 1) then
                solveKTUtil := 1
              else
                    sol[next_x][next_y] := -1;
        end 
        else begin end;
    end;
    solveKTUtil := 0;
end;

function isSafe(x, y: integer): integer;
begin
    if x >= 0 && x < 8 then
    begin
        if y >= 0 && y < 8 then
        begin
            if sol[x][y] = -1 then
                isSafe := 1
            else
                isSafe := 0;
        end
        else
            isSafe := 0;
    end
    else
        isSafe := 0;
end;

begin
    printlnString("Please input the coordinate (x, y) of start position (0 ~ 7):"); 
    x := readInt;
    y := readInt;
    if x >= 0 && x <= 7 then
    begin
        if y >= 0 && y <= 7 then
            solveKT(x, y)
        else
            printlnString("y is out of range!");
    end
    else
        printlnString("x is out of range!");
    
end.
