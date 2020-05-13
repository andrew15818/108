#ifndef BOARD_H
#define BOARD_H
#include<math.h>

// type of each cell
enum Type
{
	mine,
	hint
};
/*For the status, we can know the status 
of a cell without actually querying it,
so it can ben 'mined' since we know its 
status beforehand.*/
struct Node
{
	int x, y; 	  // row and column number, respectively
	int adjacent = 0; // number of adjacent mines
	bool status;  // false=safe, true=mined
	Type type = hint; 	  	 // can be either hint or mine
};

class Board{
	private:
		int mine_no = 10; 			// aiming for the easy configuration
		int safe_cells = 9; 		// number of hints we provide at the beginning of the game
		int rows = 9;
		int cols = 9;
		Node board[9][9];

		
		void set_mines();			// set the mines randomly
		void calculate_hints();		// set the hint no. for every cell
	public:
		Board(){};
		int query(int row, int col);// return hint value and change status to marked  
		void setup();				// calculate the hints and mines for the nodes
		void print();
};
#endif 