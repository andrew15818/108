#include <iostream>
#include <math.h>
#include <cstdio>
#include"Board.h"
#include "Util.h"

Board::Board(){
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
		board[x][y].type = safe;

		// adding a single literal clause
		Clause tmp;
		tmp.insert_literal(board[x][y]);
		tmp.size = 1;

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
int Board::query_type(const Clause& clause)
{
	Node* tmp = clause.literals.front();
	return tmp->type;
}
//check if there is a stricter phrase in teh two nodes
bool Board::check_subsumption(Clause& c1, Clause& c2)
{
	std::list<Node*>::iterator it1;
	std::list<Node*>::iterator it2;
	int match_c1 = 0, match_c2 = 1; //how many literals in each class we've matched

	for(it1 = c1.literals.begin(); it1 != c1.literals.end(); it1++){
		printf("%d\n", (*it1)->x);

		for(it2 = c2.literals.begin(); it2 != c2.literals.end(); it2++){
			if((*it1)->x == (*it2)->x && (*it1)->y == (*it2)->y){
				printf("matched: (%d, %d)",(*it1)->x, (*it2)->y);	
				match_c1++; match_c2++;
			}
		}
	}
	if(c1.literals.size() == match_c1 || c2.literals.size() == match_c2){
		printf("There is actual subsumption going on :D\n");	
	}
}
void Board::solve()
{

	//all the nodes are assigned
	if(KB.size() == 0){return;}

	//checking for a single literal
	std::list<Clause>::iterator it = KB.begin();
	Clause single;
	for(it; it != KB.end(); it++)
	{
		if(it->size == 1){
			single = (*it);
			break;
		}
	}
	
	// if a single-valued literal
	if(single.size == 1){
		printf("%d\n", query_type(single));		
	}



			/* TODO: 
			 *	 1. Process the matching of clauses to others in KB. Should we do a clause class file?
			 *	 	1.a Insert new clauses into KB
			 *	 2. If safe, query the board for hint at cell, insert unmarked neighbors into KB.
			 * */
		
		/*TODO: If there are no single clauses in KB:
		 * 	1. Apply "pairwise mathcing" to all the  other clauses in KB
		 * 		1.a Insert new clauses into KB. Match clauses where one node has at most two literals.
		 *
		 * */
	

}
