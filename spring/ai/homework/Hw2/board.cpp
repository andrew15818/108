#include <iostream>
#include "board.h"
#include "util.h"
#define CHILD_NO 4
bool Board::check_adjacent_cells(const Node* node)
{
	int x, y, adjacent_nodes = 8;
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
		//a successful board cannot have a hint node with unassigned mines
		if( is_valid(x, y) ){
			Node* tmp = &board[x][y];

			if(tmp->type == HINT && tmp->remaining != 0){
				return false;
			}
		}
	}
	return true;
}
bool Board::reject(const Node* node)
{
	int x, y;
	int adjacent_nodes = 8;
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
		//skip this node if out of bounds
		if(!is_valid(x, y)){continue;}
		//checking if mine number appropriate
		Node* tmp = &board[x][y];
		if(tmp->type == HINT && tmp->remaining == 0){return true;}
		
	}
	return false; //we cannot reject this node
} 
/*To check if a configuration is a possible solution we would need to:
 * 	1. Have no leftover mines.
 * 	2. No hint node may have more than than h adjacent mines*/
bool Board::accept()
{
	//check if we still have unassigned mines
	if(this->mines > 0){return false;}
	
	//check all hint cells to see if there are no exceeding mines adjacent to hint cells
	
	for(int i = 0; i < this->rows; i++){
		for(int j = 0; j < this->cols; j++){
			if(board[i][j].type == HINT && board[i][j].remaining != 0){
				return false;
			}
		}
	}
	
	return true;
}
//input value into board node
void Board::input(int x, int y, int value)
{
	board[x][y].x = x; board[x][y].y = y; board[x][y].value = value;
	//marking the node as unassigned
	if( value == -1)
	{
		Node *tmp = &board[x][y];
		tmp->type= VAR;
		unassigned.push_back(tmp);
	}
	//the "remaining" field will be subtracted from and added to, value is const
	else if(value != -1)
	{
		board[x][y].type = HINT;
		board[x][y].remaining = value;
	}
}
bool Board::solve_main(const Node* node)
{
	if(node == NULL){return false;}
	/*Main steps in this function:
	 *1. Check if we should reject this node
	 *2. Check if it is a solution.
	 *3. Generate and recurse on the first child.
	 *4. Generate the successive children and recurse on them.*/
	//maybe just start with the first or last node in the unassigned list?
	std::cout<<"in solve_main with: ("<<node->x<<", "<<node->y<<") and "<<unassigned.size()<<" nodes"<<std::endl;
	if(reject(node)){
		std::cout<<"\twe have to reject ("<<node->x<< ", "<<node->y<<")"<<std::endl;
		return false;
	}
	else if(accept())
	{
		std::cout<<"\tthis config is a possible one! :D"<<std::endl;
	}
	//assign a mine to current child and iterate forward
	Node* next;
	//node->type = MINE;
	for(int i = 0; i < CHILD_NO; i++)
	{
		next = get_closest_node(node);
		solve_main(next);
	}
	return true;
}
//get the closest node using manhattan distance, return it to continue the iteration
Node* Board::get_closest_node(const Node* node)
{
	if(unassigned.empty()){return NULL;} 
	Node* tmp;
	Node *best = unassigned.front();
	int min_dist = this->rows * this->cols; //farthest away next node can be
	int curr_dist, best_index;
	std::deque<Node*>::iterator it = unassigned.begin(); //iterator to check for distance
	std::deque<Node*>::iterator remove; //keep track of closest node iterator to remove it later

	//search for the closest one and remove it from the list
	while(it != unassigned.end()){
		curr_dist = man_distance(best, *(it)); 
		if( curr_dist < min_dist){
			min_dist = curr_dist;
			best = *(it);
			remove = it;
		}
		it++;
	}
	std::cout<<"\t\tabout to erase: ("<<(*remove)->x<<", "<<(*remove)->y<<")"<<std::endl;
	unassigned.erase(remove);
	return best;
}
//main driver function
void Board::solve()
{
	solve_main(&board[0][0]);
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
