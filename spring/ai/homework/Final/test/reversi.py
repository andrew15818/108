BOARD_ROWS = 8
BOARD_COLS = 8
board = [[-1, 0, 0, 2, 0, 0, 0, -1],
        [0, 0, 0, 1, 0, 0, 0, 0],
        [0, 0, 0, 1, 0, 0, 0, 0],
        [0, 0, 0, 1, 0, 0, 0, 0], 
        [0, 0, 1, 2, 1, 2, 0, 0], 
        [0, 0, 0, 1, 0, 0, 0, 0], 
        [0, 0, 0, 0, 0, 0, 0, 0],
        [-1, 0, 0, 0, 0, 0, 0, -1]]

tiles =  {
    "corner": -1,
    "unoccupied": 0,
    "white": 1,
    "black": 2
}
# Helper functions
def min(n1, n2):
    return n1 if n1 <= n2 else n2
def max(n1, n2):
    return n1 if n1 >= n2 else n2 

# Check if a node is out of bounds or in a corner tile
def is_valid(row, col):

    if row < 0 or row >= BOARD_ROWS or col < 0 or col >= BOARD_COLS:
        return False

    # Corner tiles
    if row == 0 or row == BOARD_ROWS - 1:
        if col == row:
            return False
    return True 
# Given the direction of an opponent, check if there is a friendly piece at the end of the 
# sequence of opponent pieces
def check_opponent_line(row, col, rowdir, coldir, is_black=False):
    if not is_valid(row, col):
        return 0

    # How many enemy pieces lie along this line
    can_move =  0
    opponent_team = tiles["black"] if board[row][col]  == tiles["white"] else tiles["white"]
    player_team = tiles["white"] if board[row][col] == tiles["white"] else tiles["black"]

    while True:
        # Traveling along the direction
        row += rowdir
        col += coldir
        print(f"checking ({row}, {col})")
        # Out of bounds
        if not is_valid(row, col) or board[row][col] == tiles["unoccupied"]:
            break
         
        # If there is another opponent along the direction line
        elif board[row][col] == opponent_team:
            can_move += 1

        # If reached same-colored tile at the end of the line
        elif board[row][col] == player_team:
            return can_move 

    # If we reach the end, then can't change pieces along this route
    return 0
# Get the amount of nodes we can turn by selecting this node
# TODO: May have to severely change this heuristic function
def heuristic(node):
    
    opponent = None
    x,y = node[0], node[1]
    print(f"\t\tCalling the heuristic on ({node[0]}, {node[1]})")
    if board[x][y] == tiles["black"]:
        opponent = tiles["white"]
    elif board[x][y] == tiles["white"]:
        opponent = tiles["black"]

    # Amount of chips we can turn color 
    can_turn = 0
    for i in range(-1, 2):
        for j in range(-1, 2):
            row = node[0] + i
            col = node[1] + j
            
            # Check if adjacent tile is of different color
            if is_valid(row, col): 
                if board[row][col] == opponent:
                    while (is_valid(row, col) 
                        and board[row][col] == opponent):
                        row += i
                        col += j
                        #print(f"\tChecking: ({row},{col})")
                        can_turn += 1  


                    print(f"\tcan turn: {can_turn}")
    return can_turn

def minmax(node, depth=2, is_maximizing=True, currsum=0):
    # End of the recursion
    if depth == 0:
        value = heuristic(node)
        print(f"\theuristic for ({node[0]},{node[1]}):{value}")
        return value

    val = -1000 if is_maximizing else 1000


    # Recursing on the min/max values for all the curr node's children
    for i in range(-1, 2):
       for j in range(-1, 2):
           if i == 0 and j == 0:
               continue
           x = node[0] + i
           y = node[1] + j
           # Get the maximum value available at a given node
           if is_valid(x, y):
               if is_maximizing:
                   #val = max(val, minmax((x, y), depth-1, False))
                   currsum += minmax((x, y), depth-1, False, currsum=currsum)
                   print(f"\tMaximum value: {currsum}")

               elif not is_maximizing:
                   tmp = minmax((x, y), depth-1, True, currsum=currsum)
                   currsum -= tmp
                   print(f"\tMinimum value: {currsum}")
            

    return currsum
def GetStep():
    pass
'''
for row in range(len(board) - 1):
    for col in range(len(board) - 1):
        if board[row][col] == tiles["unoccupied"]:
            continue
        print(f"Minmax value for {row}, {col}: {minmax((row, col), 2, False)}")
 '''
#print(heuristic((4,3)))
#print(minmax( (4, 3), depth=2, is_maximizing=True, currsum=0))
print(check_opponent_line(4, 3, -1, 0))