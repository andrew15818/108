#include <iostream>
#include <math.h>
#include <cstdio>
#include"Board.h"
#include "Util.h"

Board::Board(){
	printf("hola\n");
	setup();
}
// set the mines at random locations
// TODO: maybe make sure that no mines are overlapping
void Board::set_mines()
{
	for(int i = 0; i < this->mine_no; i++){
		int x = (int)(rand() % (this->cols));
		int y = (int)(rand() % (this->rows ));
		//printf("x and y: (%d, %d)\n", x, y);
		board[x][y].type = mine;
		board[x][y].adjacent = -1;
	}

}
void Board::calculate_hints()
{
	int count = 0;
	while(count < this->safe_cells)
	{
		int x = (int) (rand() % this->rows);
		int y = (int) (rand() % this->cols);
		// skip previously assigned nodes
		if(board[x][y].type == mine){
			continue;
		}
		board[x][y].type = hint;

		// adding a single literal clause
		Clause tmp;
		tmp.n1 = &board[x][y];
		tmp.assigned = 1;
		printf("pushing back: (%d, %d)\n", tmp.n1->x, tmp.n1->y);
		KB.push_back(tmp);
		int currx, curry;

		// calculate adjacent mines to nodes we mark as safe
		for(int i = -1; i <= 1; i++){
			for(int j = -1; j <= 1; j++){
				currx = x + i; curry = y + j;
				if(i == 0 && j == 0){continue;}
				if(!is_valid(currx, curry, this->rows, this->cols)){
					continue;
				}
				if(board[currx][curry].type == mine){
					board[x][y].adjacent++;
				}
			}
		}
		count++;
	}
}
void Board::setup()
{
	for(int i = 0; i < this->rows; i++){
		for(int j = 0; j < this->cols; j++){
			board[i][j].x = i;
			board[i][j].y = j;
		}
	}
	set_mines();
	calculate_hints();
}
void Board::print()
{
	for(int i = 0; i < this->rows; i++){
		for(int j = 0; j < this->cols; j++){
			//printf("%d ", board[i][j].adjacent);	
			(board[i][j].type == mine)? printf("-1"): printf(" %d", board[i][j].type);
			if(j == this->cols -1) printf("\n");
		}
	}
}
/*TODO: Since we moved the clause to another file, update 
 * the ways we call and treat clauses in this function.*/
void Board::solve()
{
	printf("KB size: %d\n", KB.size());
	//all the nodes are assigned
	if(KB.size() == 0){return;}

	//checking for a single literal
	std::list<Clause>::iterator it = KB.begin();
	Clause single;
	for(it; it != KB.end(); it++)
	{
		if(it->assigned == 1){
			single = (*it);
			break;
		}
	}

	//checking if actually found value
	if(single.assigned == 1){
		printf("Found (%d, %d)\n", single.n1->x, single.n1->y);
		// mark the node as either safe or mined
		if(single.n1->type == unassigned)
		{
			single.n1->type = hint; // mined nodes
			KB0.push_back(single);  // move it to list of assigned nodes
			/* TODO: 
			 *	 1. Process the matching of clauses to others in KB. Should we do a clause class file?
			 *	 	1.a Insert new clauses into KB
			 *	 2. If safe, query the board for hint at cell, insert unmarked neighbors into KB.
			 * */
		}
		/*TODO: If there are no single clauses in KB:
		 * 	1. Apply "pairwise mathcing" to all the  other clauses in KB
		 * 		1.a Insert new clauses into KB. Match clauses where one node has at most two literals.
		 *
		 * */
	}

}
