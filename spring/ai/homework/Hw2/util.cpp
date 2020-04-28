#include "util.h"
#include <cstdio>
#include <cmath>
//quick check if cell coords are out of bounds
bool  is_valid(int x, int y)
{
	if(x < 0 || y < 0 || x >= BOARD_SIZE || y >= BOARD_SIZE)
	{
		return false;
	}
	return true;
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
//manhattan distance between two cells
double man_distance(const Node* n1, const Node* n2)
{
	return ( abs(n1->x - n2->x) + abs(n1->y - n2->y) );
}

