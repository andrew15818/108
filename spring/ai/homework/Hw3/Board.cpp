#include <iostream>
#include <math.h>
#include <cstdio>
#include"Board.h"
#include "Util.h"

// set the mines at random locations
// TODO: maybe make sure that no mines are overlapping
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
			Node *current = &board[i][j];
			Node *tmp;
			int x, y;
			for(int rows = -1; rows <= 1; rows++){
				for(int cols = -1; cols <= 1; cols++){
					if(rows == 0 && cols == 0){continue;}
					x = i + rows; y = j + cols;  
					
					
					if(!is_valid(x, y, this->rows, this->cols)){continue;}
					tmp = &board[x][y];

					if(tmp->type == mine){
						current->adjacent++;
					}
				}
			}
		}
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
			(board[i][j].type == mine)? printf("-1"): printf(" %d", board[i][j].adjacent);
			if(j == this->cols -1) printf("\n");
		}
	}	
}
