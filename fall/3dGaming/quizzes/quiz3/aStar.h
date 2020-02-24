#ifndef A_STAR_H
#define A_STAR_H
struct aStarNode{
	float f; //final result, sum of g and h
	float g; //distance from source node to current Node
	float h; //remaining distance from current node to destination
	int type; //decides whether we can move here
	int x, z; //x and z coordinates, needed bc the nodes might be shuffled around
	//aStarNode& parent ;
	int parentX, parentZ;
};

float manDist(int startX, int startY, int endX, int endY); //manhattan distance b/w 2 points

#endif