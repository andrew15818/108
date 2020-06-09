BOARD_ROWS = 8
BOARD_COLS = 8
board = [[-1, 0, 0, 0, 0, 0, 0, -1],
        [0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0], 
        [0, 0, 0, 0, 0, 0, 0, 0], 
        [0, 0, 0, 0, 0, 0, 0, 0], 
        [-1, 0, 0, 0, 0, 0, 0, -1]]

tiles =  {
    "corner": -1,
    "unoccupied":0,
    "white": 1,
    "black": 2
}
# Check if a node is out of bounds or in a corner tile
def is_valid(row, col):

    if row < 0 or row >= BOARD_ROWS or col < 0 or col >= BOARD_COLS:
        return False

    # Corner tiles
    if row == 0 or row == BOARD_ROWS - 1:
        if col == row:
            return False
    return True 

# Get the valid coordinates of current node's next moves
def get_children(node):
    children = []
    for i in range(-1, 1):
        for j in range(-1, 1):
            if i == 0 && j == 0:
                continue
            x = node[0] + i 
            y = node[1] + j

            if is_valid(x, y):
                children.append((row, col))
# Get the amount of nodes we can turn by selecting this node
def heuristic(node):
    for i in range(-1, 1):
        for j in range(-1, 1):
            row = node[0] + i
            col = node[1] + j
            # Check if adjacent tile is of different color
            if board[node[0]][node[1]] == tiles["black"]


def minmax():
    pass
def GetStep():
    pass
        
