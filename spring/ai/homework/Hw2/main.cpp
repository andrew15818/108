/*
 * The goal of this assignment is: given a board with some cells
 * filled in with hints, find a possible valid board configuration 
 * such that all the hints actually are correct, i.e. the number of 
 * adjacent mines to a labeled hint is accurate given a set number of 
 * bombs.
 * */
#include<iostream>
#include<queue>
#define BOARD_SIZE 6
#define MINE 100
#define HINT 101
#define VAR 102
bool  is_valid(int x, int y)
{
	if(x < 0 || y < 0 || x >= BOARD_SIZE || y >= BOARD_SIZE)
	{
		return false;
	}
	return true;
}
struct Node
{
	int value; //can be either mine(-1) or hint, with number of adjacent mines
	int remaining; //how many mines can we assign to adjacent cells
	int x, y;
	int type = VAR;
};
class Board
{
	Node root; //empty root
	Node board[BOARD_SIZE][BOARD_SIZE]; //figure out how to make it changeable to other sizes
	int rows, cols, mines;
	std::queue<Node*> unassigned;
	std::queue<Node*> assigned;
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
		bool accept(const Node* node);
		Node* first(const Node* node); //maybe don't require a node argument
		Node* next(const Node* node); //same as above
};
bool Board::reject(const Node* node)
{
	int x, y;
	int adjacent_nodes = 8;
	//need to check all adjacent nodes
	for(int i = 0; i < adjacent_nodes; i++)
	{
		x = node->x; y = node->y;
		switch(i % adjacent_nodes){
			case 0: //left
				y -= 1;
				break;
			case 1: //diagonal up left
				x -= 1;y -= 1;
				break;
			case 2: //straight up
				 y -= 1;
				break;
			case 3: //up right
				x += 1; y -= 1;
				break;
			case 4: //right
				y+=1;
				break;
			case 5: //down right
				x -= 1; y += 1;
				break;
			case 6: //down
				y += 1;
				break;
			case 7: //down left
				x -= 1; y += 1;
				break;
		}
		//
		if(is_valid(x, y))
		{
			Node *tmp = &board[x][y];
			//we can't assign a node b/c there would be too many next to tmp
			if(tmp->type == HINT && tmp->remaining == 0)
			{
				return true;
			}
			//then try and assign a mine here if we can
			else if(tmp->type == HINT)
			{
				tmp->remaining--;
			}
		}
	}
	this->mines--; //not sure if we should remove a mine at this stage?
	return false; //we cannot reject this node
} 
//input value into board node
void Board::input(int x, int y, int value)
{
	board[x][y].x = x; board[x][y].y = y; board[x][y].value = value;
	//marking the node as unassigned
	if( value == -1)
	{
		Node *tmp = &board[x][y];
		tmp->value = VAR;
		unassigned.push(tmp);
	}
	//the "remaining" field will be subtracted from and added to, value is const
	else if(value != -1)
	{
		board[x][y].type = HINT;
		board[x][y].remaining = value;
	}
}
//print out current state of the board
void Board::print_out()
{
	for(int i =0; i < BOARD_SIZE; i++)
	{
		for(int j = 0;j < BOARD_SIZE; j++)
		{
			std::cout<<board[i][j].value<<" ";
			if(j == BOARD_SIZE - 1){ std::cout<<std::endl; }
		}
	}
}
void print_intro()
{
	printf("***------***\n"
		"Please input a 6x6 matrix with the following instructions: \n"
			"\t-1 if the spot is a variable\n"
			"\t the number of adjacent bombs to that square\n"
			"***------***\n\n"
		);
}

int main(int argc, char* argv[])
{
	print_intro();
	int input = 1, value;
	int rows, cols, mines;
	while(1){
		std::cout<<"\tInput 1 to keep playing, 0 to exit:"<<std::endl;
		std::cin>>input;
		if(input == 0 ){break;}
		std::cin>>rows>>cols>>mines;
		std::cout<<rows<<" rows\t"<<cols<<" columns\t"<<mines<<" mines"<<std::endl;
		Board board(rows, cols, mines); //create the main board
		for(int i = 0; i < BOARD_SIZE; i++)
		{
			for(int j = 0; j < BOARD_SIZE; j++)
			{
				std::cin>>value; //either a bomb or hint
				board.input(i, j, value);
			}
		}
		board.print_out();
	}
}
