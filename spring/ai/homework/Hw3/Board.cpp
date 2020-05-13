#include <iostream>
#include <math.h>
#include <cstdio>
#include"Board.h"
#include "Util.h"

// set the mines at random locations
void Board::set_mines()
{
	for(int i = 0; i < this->mine_no; i++){
		int x = rand() % (this->cols + 1);
		int y = rand() % (this->rows + 1);

		board[x][y].type = mine;
		board[x][y].adjacent = -1;
	}	
}
void Board::calculate_hints()
{
	for(int i = 0; i < this->rows; i++){
		for(int j = 0; j < this->cols; j++){
			Node* tmp = &board[i][j];	
			//TODO: finish calculating adjacent mines
		}
	}
}
void Board::setup()
{

	set_mines();
}
void Board::print()
{
	for(int i = 0; i < this->rows; i++){
		for(int j = 0; j < this->cols; j++){
			printf("%d ", board[i][j].adjacent);	
			if(j == this->cols -1) printf("\n");
		}
	}	
}