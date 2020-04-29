/*
 * The goal of this assignment is: given a board with some cells
 * filled in with hints, find a possible valid board configuration 
 * such that all the hints actually are correct, i.e. the number of 
 * adjacent mines to a labeled hint is accurate given a set number of 
 * bombs.
 * */
#include <iostream>
#include <queue>
#include "board.h"
#include "util.h"
#define BOARD_SIZE 6
#define MINE 100
#define HINT 101
#define VAR 102
int main(int argc, char* argv[])
{
	print_intro();
	int input = 1, value;
	int rows, cols, mines;
	while(1){
		std::cout<<"\tInput 1 to keep playing, 0 to exit:"<<std::endl;
		//std::cin>>input;
		//if(input == 0 ){break;}
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
		board.solve();
		board.print_out();
	}
}
