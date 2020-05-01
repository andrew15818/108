#ifndef BOARD_H
#define BOARD_H
#include <deque>
#include<string.h>
#define BOARD_SIZE 6
#define MINE 0
#define HINT 10 
#define VAR 1

struct Node
{
	int value = -1; //can be either mine(-1) or hint, with number of adjacent mines
	int remaining; //how many mines can we assign to adjacent cells
	int x, y;
	int type;// = VAR;
};
class Board
{
	private:
		//Node root; //empty root
		Node board[BOARD_SIZE][BOARD_SIZE]; //figure out how to make it changeable to other sizes
		bool visited[BOARD_SIZE][BOARD_SIZE] ;
		
		int rows, cols, mines;
		long int expanded;
		std::deque<Node*> unassigned;
		//bool check_adjacent_cells(const Node* node);
		bool solve_main(Node* node);
		void adjust_adjacent_values(const Node* node, int operation); //1 for adding 1 to adj. hint nodes, 0 to subtract when assigning mine
		Node* get_closest_node(const Node* node, int heuristic);
		Node* no_heuristic(const Node* node);
		Node* mrv(const Node* node); //minimum remaining values
		Node* dh(const Node* node);	 //degree heuristic
		Node* lcv(const Node* node); //something or other
	public:
		Board(int rows, int cols, int mines)
		{
			this->rows = rows;
			this->cols = cols;
			this->mines = mines; //number of mines on the board
			memset(visited, false, sizeof(visited));
		}
		void input(int x, int y, int value);
		void print_out();
		bool reject(const Node* node);
		bool accept();
		void solve();
};

#endif
