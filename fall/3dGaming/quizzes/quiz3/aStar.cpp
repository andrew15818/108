#include "aStar.h"
#include<math.h>
float manDist(int startX, int startY, int endX, int endY)
{
	return abs((endX-startX)+(endY-startY));
}
