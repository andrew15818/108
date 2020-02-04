program knight_tour_Warnsdorff(void);
//solving knight's tour problem using Warnsdorff’s algorithm
// see https://www.geeksforgeeks.org/warnsdorffs-algorithm-knights-tour-problem/
var cx, cy : array[0..7] of integer;
var a : array[0..63] of integer;
var xx, yy, ix, iy : integer;

procedure findClosedTour(sx, sy : integer);
var i: integer;
begin
    for i := 0 to 63 do
        a[i] := -1;
 
    xx := sx;
    yy := sy;

    a[yy*8+xx] := 0;
    
    for i := 0 to 62 do
    begin
        if not nextMove(i) then
            printlnString("can not find a solution")
        else begin end;
    end;

    print;
end;

function nextMove(dummy:integer): integer;
var min_deg_idx, c, min_deg, nx, ny, i : integer;
begin
    min_deg_idx := -1;
    min_deg := 9;
    
    for i:= 0 to 7 do 
    begin
        nx := xx + cx[i];
        ny := yy + cy[i];
        c := getDegree(nx, ny);
        if isempty(nx, ny) && c < min_deg then
        begin
            min_deg_idx := i;
            min_deg := c;
        end
        else begin end;
    end;
   
    if min_deg_idx = -1 then
        nextMove := 0
    else begin end;

    nx := xx + cx[min_deg_idx];
    ny := yy + cy[min_deg_idx];

    a[ny*8 + nx] := a[yy*8 + xx] + 1;

    xx := nx;
    yy := ny;
    
    nextMove := 1;
end;

procedure print;
var i, j : integer;
begin
    for i := 0 to 7 do
    begin
        for j := 0 to 7 do
        begin
            printString(" ");
            printInt(a[j*8+i]);
        end;
        printlnString("");
    end;
end;

function getDegree(x, y : integer): integer;
var count, i : integer;
begin
    count := 0;
    for i := 0 to 7 do
    begin
        if isempty(x + cx[i], y + cy[i]) then
            count := count + 1
        else begin end;
    end;
    getDegree := count;
end;

function isempty(x, y : integer): integer;
begin
    if limits(x, y) && a[y*8+x] < 0 then
        isempty := 1
    else
        isempty := 0;
end;

function limits(x, y : integer): integer;
begin
    if x >= 0 && y >= 0 then
    begin
        if x < 8 && y < 8 then
            limits := 1
        else
            limits := 0;
    end
    else 
        limits := 0;
end;

begin
    cx[0] := 1;
    cx[1] := 1;
    cx[2] := 2;
    cx[3] := 2;
    cx[4] := -1;
    cx[5] := -1;
    cx[6] := -2;
    cx[7] := -2;

    cy[0] := 2;
    cy[1] := -2;
    cy[2] := 1;
    cy[3] := -1;
    cy[4] := 2;
    cy[5] := -2;
    cy[6] := 1;
    cy[7] := -1;

    printlnString("Please input the coordinate (x, y) of start position (0 ~ 7):"); 
    ix := readInt;
    iy := readInt;
    if ix >= 0 && ix <= 7 then
    begin
        if iy >= 0 && iy <= 7 then
            findClosedTour(ix, iy)
        else
            printlnString("y is out of range!");
    end
    else
        printlnString("x is out of range!");
    
    
end.
