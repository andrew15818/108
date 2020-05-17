#include "Util.h"

bool is_valid(int x, int y, int rows, int cols)
{
	if (x < 0 || x >= rows || y < 0 || y >= cols){
		return false;
	}
	return true;
}
