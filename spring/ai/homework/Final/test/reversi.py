import copy
'''
board = [[-1, 0, 0, 0, 0, 0, 0, -1],
        [0, 0, 0, 1, 0, 0, 0, 0],
        [0, 0, 0, 1, 0, 0, 0, 0],
        [0, 0, 0, 1, 0, 0, 0, 0], 
        [0, 0, 1, 2, 1, 2, 0, 0], 
        [0, 0, 0, 1, 0, 0, 0, 0], 
        [0, 0, 0, 2, 0, 0, 0, 0],
        [-1, 0, 0, 0, 0, 0, 0, -1]]
'''
board = [[0, 0, 0],
        [ 2, 1, 2],
        [ 0, 1, 1],
        [ 0, 0, 2]]

BOARD_ROWS = len(board)
BOARD_COLS = len(board[0])

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
def check_opponent_line(row, col, board, rowdir, coldir, is_black=False):
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
        print(f"\tchecking ({row}, {col})")
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
def heuristic(node, board):

    # How many nodes we can turn starting from this node in total 
    can_eat = 0
    for row_dir in range(-1, 2):
        for col_dir in range(-1, 2):
            # Out of bounds or repeating same node
            if row_dir == 0 and col_dir == 0:
                continue
            x = node[0] + row_dir
            y = node[1] + col_dir
            if not is_valid(x, y):
                continue

            can_eat += check_opponent_line(node[0], node[1], board,row_dir, col_dir)
    return can_eat
# Helper function
def print_board(board):
    for row in range(len(board)):
        print(board[row])
    print("\n")
# Assign the value of the color to the copy of the board
def modify_board(node, board, assign_black=False): 

    # Take the copy of the board and assign a value to the node
    assign_value = tiles["black"] if assign_black else tiles["white"]
    board[node[0]][node[1]] = assign_value

    return board 


#TODO: Check the value of the implemented move on the copy of the board
def minmax( node, board, depth, is_black, alpha, beta):
    #print(f"Currently getting the minmax at ({node[0]}, {node[1]})")

    if depth == 0:
        heu = heuristic(node, board)
        print(f"\t\tHeur value for ({node[0]},{node[1]}): {heu}")
        return heu 

    board_copy = copy.deepcopy(board)
    print_board(board)
    # Alpha-Beta Implementation
    if is_black:
        best_val = -1000
        board_copy = modify_board(node=node, board=board, assign_black=True)
        for i in range(-1, 2):
            for j in range(-1, 2):
                x = node[0] + i
                y = node[1] + j

                if not is_valid(x, y):
                    continue
                value = minmax((x, y), board=board_copy, depth=depth-1, is_black=False, alpha=alpha, beta=beta)
                best_val = max(value, best_val)
                alpha = max(alpha, best_val)
                if beta <= alpha:
                    break
                return best_val

    elif not is_black:
        best_val = 1000
        board_copy = modify_board(node=node, board=board, assign_black=False)
        for i in range(-1, 2):
            for j in range(-1, 2):
                x = node[0] + i
                y = node[1] + j
                if not is_valid(x, y):
                    continue

                
                value = minmax((x, y), board=board_copy, depth=depth-1, is_black=True, alpha=alpha, beta=beta) 
                best_val = min(value, best_val)
                beta = min(beta, best_val)
                if beta <= alpha:
                    break
                return best_val

#TODO: Possible way to modify this
# 1. Look for unoccupied slots.
# 2. Make a copy of the board.
# 3. Get the heurisitic/minmax value on that copy of the board
#   3.1 If we dont make a modified copy, then we can't measure exactly
#       How placing a tile on the board will affect the minmax calculation.    
def GetStep(board, is_black=False):

    best_row = 0 
    best_col = 0
    curr_best_heur = -1
    
    for row in range(len(board)):
        for col in range(len(board[0])):
            
            if not is_valid(row, col):
                continue
            elif board[row][col] == tiles["corner"]:
                continue

            tmp = heuristic((row, col), board=board)
            if tmp > curr_best_heur:
                print(f"Found a new best path through: ({row},{col}): {tmp}")
                curr_best_heur = tmp
                best_row = row
                best_col = col


    return (best_row, best_col) 

print(GetStep(board, True))
#print(minmax((4, 3), board=board, depth=2, is_black=True, alpha=-1000, beta=1000))
