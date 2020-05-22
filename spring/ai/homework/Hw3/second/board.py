import math
from random import randint
status = {
	"mine": 0,
	"safe": 1,
	"hint": 2,
	"unassigned": 3
}
class Node:
    def __init__(self):
    	self.x = None
    	self.y = None
    	self.adjacent = 0
    	self.status = status["unassigned"]
			    
def is_valid(x, y, rows, cols):
	if (x < 0 or y < 0 or x >= cols or y >= cols):
		return false
	return true
class Board:
    def __init__(self, rows, cols):
    	self.rows = rows
    	self.cols = cols
    	self.mines = 9
    	self.safe_cells= math.sqrt(self.rows * self.cols)
    	self.board = [[Node() for i in range(self.cols)]for i in range(self.rows)]

    	for i in range(self.rows):
    		for j in range(self.cols):
    			self.board[i][j].x = i
    			self.board[i][j].y = j
    	
    	self.assign_mines()
    	self.assign_safe_cells()
    	self.print()	

    def assign_mines(self):
    	i = 0	

    	# choosing random node and assigning its status 
    	while i < self.mines:
    		row = randint(0, self.rows - 1)
    		col = randint(0, self.cols - 1)
    		# check for previously assinged mines	
    		if(self.board[row][col] == status["mine"]):
    			continue

    		self.board[row][col].status = status["mine"]
    		i += 1

    def assign_safe_cells(self):
    	i = 0 
    	# choosing random cell and changing its status,
    	# we also calculate adjacent mines
    	while i < self.safe_cells:
    		row = randint(0, self.rows - 1)
    		col = randint(0, self.cols - 1)



    		if self.board[row][col].status != status["unassigned"]:	
    			continue

			
    		self.board[row][col].status = status["safe"]
    		x = row
    		y = col
    		#calculate adjacent cells
    		adjacent = 0
    		i += 1

    		"""
    		for i in range(-1, 1):
    			for j in range(-1, 1):
    				if i == 0 and j == 0:
    					continue
    				x += i
    				y += j
    				if(is_valid(x, y, self.rows, self.cols) and 
    					board[x][y].status == status["mine"]):
    					current += 1

    		board[row][col].adjacent = current
    		"""	

    def print(self):
    	for i in range(self.rows):
    		s = ''
    		for j in range(self.cols):
    			s += str(self.board[i][j].status) + ' '
    		print(s)	