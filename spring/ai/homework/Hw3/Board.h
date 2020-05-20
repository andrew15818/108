#ifndef BOARD_H
#define BOARD_H
#include "Clause.h"
#include<math.h>

class Board{
	private:
		int mine_no = 10; 			// aiming for the easy configuration
		
		int rows = 9;
		int cols = 9;
		int safe_cells = 
			(int) sqrt(rows * cols);// number of hints we provide at the beginning of the game
		Node board[9][9];
		std::list<Clause> KB; 		// Knowledge Base of what we have to solve
		std::list<Clause> KB0;		// Nodes we have already assigned
		
		void set_mines();			// set the mines randomly
		void calculate_hints();		// set the hint no. for every cell
		void setup();				// calculate the hints and mines for the nodes

	public:
		Board();
		int query_hint(int row, int col);// return hint value and change status to marked  
		int query_type(const Clause& clause); // return status of first node in the clause
		void solve();				// play the game and mark the cells as safe or mined
		void print();
		bool check_subsumption(Clause& c1, Clause& c2); // check if one clause is stricter than the other
		void match_clause(Clause& clause); //try to find a match for clause in KB
};
#endif 
