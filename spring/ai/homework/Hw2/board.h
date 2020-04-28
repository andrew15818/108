#ifndef BOARD_H
#define BOARD_H
#include <deque>
#define BOARD_SIZE 6
#define MINE 100
#define HINT 101
#define VAR 102

struct Node
{
	int value = -1; //can be either mine(-1) or hint, with number of adjacent mines
	int remaining; //how many mines can we assign to adjacent cells
	int x, y;
	int type = VAR;
};
class Board
{
	private:
		Node root; //empty root
		Node board[BOARD_SIZE][BOARD_SIZE]; //figure out how to make it changeable to other sizes
		int rows, cols, mines;
		std::deque<Node*> unassigned;
		std::deque<Node*> assigned;

		bool check_adjacent_cells(const Node* node);
		bool solve_main(const Node* node);
		Node* get_closest_node(const Node* node);
	public:
		Board(int rows, int cols, int mines)
		{
			this->rows = rows;
			this->cols = cols;
			this->mines = mines; //number of mines on the board
		}
		void input(int x, int y, int value);
		void print_out();
		bool reject(const Node* node);
		bool accept();
		void solve();
};

#endif
