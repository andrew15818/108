#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<stack>
#include<list>
#include<stdlib.h>

#define BFS 1
#define DFS 2
#define IDS 3
#define A_STAR 4
#define IDA_STAR 5
#define BOARD_SIZE 16 
#define CHILD_NO 8
#define MAX_DEPTH 10
#define FOUND 1000 
#define OPEN_SET 1001
//int board[BOARD_SIZE][BOARD_SIZE];

//these functions return the number of expanded nodes
struct Node
{
	int x, y, discovered = 0, children=0;
	int f = 0 , g = 0; //info for a* algorithm
	Node *parent; 
};
//need the struct to sort priority queue for A*
struct compare{
	bool operator()(const Node* n1, const Node* n2)
	{
		return n1-> f <= n2->f;
	}
};
//iterate through these arrays, add to parent x and y values
//to get coordinates of the child nodes
const int rowstep[CHILD_NO] = {1, 1, -1, -1, 2, 2, -2, -2}; 
const int colstep[CHILD_NO] = {2, -2, 2, -2, 1, -1, 1, -1};
static Node board[BOARD_SIZE * BOARD_SIZE];

void reset_board()
{
	//we set the x and y every iteration?
	
	for(int i =0; i < BOARD_SIZE * BOARD_SIZE; i++){
		board[i].x = i / BOARD_SIZE;
		board[i].y  = i % BOARD_SIZE;
		board[i].discovered = 0;
	}

}
inline int is_valid(int x, int y)
{
	int tmp = 0;
	tmp = (x < 0 || y < 0 || y >= BOARD_SIZE || x>=BOARD_SIZE)? 0 : 1;
	return tmp;
}
//because board is just single dimension, need to turn x, y of board to 
//single index
inline int get_index(int row, int col)
{
	return row*BOARD_SIZE + col;
}
inline int heuristic(struct Node* node, int targetx, int targety)
{
	return (abs(targetx - node->x) + abs(targety - node->y));
}
//iterate back from the target node to the starting node.
void print_path(struct Node* node, const int startx, const int starty)
{
	Node  *tmp = node;
	printf("(%d, %d)", node->x, node->y);
	if(tmp->parent == NULL || (tmp->x == startx && tmp->y == starty)){	
		return;
	}
	printf(" -> ");
	print_path(tmp->parent, startx, starty);
	return;
}

int BFS_search(int startx, int starty, int endx, int endy)
{
	int expanded = 0;
	std::list<Node*> frontier;
	//preprocessing

	int index = get_index(startx, starty);
	Node* initial = &board[index];
	initial->parent = NULL;
	frontier.push_back(initial);
	
	while(!frontier.empty())
	{
		//first node will be the one we discovered longest time ago
		Node* current = frontier.front();
		
		//if(!is_valid(current->x, current->y)){ 
		//continue;
		//}
		current->discovered = 1;
		//printf("checking: (%d, %d)\n", current->x, current->y);
		if(current->x == endx && current->y == endy){
			printf("Found Target.\n");
			print_path(current, startx, starty);
			return expanded;
		}
		expanded++;
		frontier.pop_front();
		//Node* tmp = &board[get_index(current->x + 1, current->y + 2)];
		current->discovered = 1;

		for(int i=0; i< CHILD_NO; i++)
		{
			int x = current->x + rowstep[i], y = current->y + colstep[i];

			//add child point to frontier if valid
			if(is_valid(x, y) && !board[get_index(x, y)].discovered)
			{
				if(!board[get_index(x, y)].discovered)
				{
					frontier.push_back(&board[get_index(x, y)]);
					printf("adding to frontier\n");
					board[get_index(x,y)].parent = current;
				}
			}
			printf("\n");
		}
		
	}
	return expanded;
}


int DFS_search(int startx, int starty, int endx, int endy)
{
	Node* initial= &board[get_index(startx, starty)];
	Node* current;
	initial->parent = NULL;
	int expanded = 0;
	std::stack<Node*> frontier;
	frontier.push(initial);
	
	while(!frontier.empty()){
		current = frontier.top();
		frontier.pop();
		expanded++;
		//checking for target value
		//printf("Check (%d, %d)\n", current->x, current->y);
		if(current->x == endx && current->y == endy)
		{
			printf("Found Target.\n");
			print_path(current, startx, starty);
			printf("\n");
			return expanded;
		}
		
		current->discovered = 1;
		int x, y;
		//we check valid node right after they're inserted in stacks
		for(int i = 0; i<CHILD_NO; i++){
			x=current->x + rowstep[i]; y= current->y + colstep[i];
			Node* to_check = &board[get_index(x, y)];
			if(is_valid(x,y) && !to_check->discovered){
				to_check->parent = current;
				frontier.push(to_check);

			}
		}
	}
	return 0;//placeholder ATM
}
int IDS_helper(int startx, int starty, int endx, int endy, int curr_depth, int* expanded)
{
	
	Node* current = &board[get_index(startx, starty)]; 
	//checking for end of recursion
	if(current->x == endx && current->y == endy) //1.check if we found the target
	{
		print_path(current, endx, endy);
		return 1;
	}
	if(curr_depth > MAX_DEPTH || current->discovered){
		printf("MAX_DEPTH exceeded.\n");
		return 0;
	}
	current->discovered = 1;
	(*expanded)++;
	int x ,y;
	Node* to_check;

	//checking and recursing on child nodes
	for(int i =0; i<CHILD_NO; i++)
	{
		x = current->x + rowstep[i]; y = current->y + colstep[i];
		if(is_valid(x, y)){
				to_check = &board[get_index(x, y)];

				//return if target node reachable from current node
				if(!to_check->discovered){
					to_check->parent = current;
					if(IDS_helper(x, y, endx, endy, curr_depth++, expanded) > 0){
						return 1;
					}

				}
		}
	}
	return 0;

}
//want to run limited DFS from starting nodes found in BFS manner
int IDS_search(int startx, int starty, int endx, int endy){

	int iterations = 1, found = 0, expanded = 0;
	board[get_index(startx, starty)].parent = NULL;
	//try to find min amount of nodes needed to reach goal
	//by limiting iterations
	for(iterations; iterations <= MAX_DEPTH; iterations++){
		found = IDS_helper(startx, starty, endx, endy, iterations, &expanded);
		if (found > 0){
			break;
		}
	}
	print_path(&board[get_index(endx, endy)], startx, starty);
	return expanded;
}

int  A_STAR_search(int startx, int starty, int endx, int endy){

	Node* initial = &board[get_index(startx, starty)];
	initial->parent = NULL;
	int x,y;
	std::priority_queue<Node*, std::vector<Node*>, compare > frontier;
	frontier.push(initial);
	initial->f = heuristic(initial, endx, endy);
	initial->g = 0;
	//select the best node that has not been discovered yet
	int expanded = 0;
	while(!frontier.empty())
	{

		Node* parent = frontier.top();
		frontier.pop();
		expanded++;
		
		//printf("getting: (%d, %d)\n",parent->x, parent->y);
		
		parent->discovered = OPEN_SET;
		expanded++;


		printf("for (%d, %d): f:%d \tg:%d \th:%d\n", 
						parent->x, parent->y, parent->f, parent->g, heuristic(parent, endx, endy));
		//iterate through the nodes of the parent node
		for(int i =0; i < CHILD_NO; i++)
		{
			x = parent->x + rowstep[i]; y = parent->y + colstep[i];
			if(!is_valid(x, y)){continue;}
			
			Node* child = &board[get_index(x, y)];
			
			//check if the child node is the target
			if(child->x == endx && child->y == endy){
				printf("parent: (%d, %d)\n", parent->x, parent->y);
				child->parent = parent;
				print_path(child, startx, starty);
				return expanded;
				//return expanded;
			}
			//calculate f and g for the child
			child->g = parent->g + 1;//(abs(parent->x + child->x) + abs(parent->y - child->y));
			child->f =  child->g + heuristic(child, endx, endy);
			printf("(%d, %d)'s f: %d vs parent (%d, %d)'s f:%d \n",
					child->x, child->y, child->f, parent->x, parent->y, parent->f);
			if(child->f <= parent->f && child->discovered != 1)
			{
				printf("\tfor (%d, %d): f:%d \tg:%d \th:%d\n", 
								child->x, child->y, child->f, child->g, heuristic(child, endx, endy));
				printf("hola\n");
				child->parent = parent;
				Node* tmp;
				bool found = false;
				for(int i = 0; i < frontier.size(); i++)
				{
					//checking if the child nodes are already discovered
					tmp = frontier.top();
					frontier.pop();
					if(tmp->x == child->x && tmp->y == child->y){
						tmp->parent = parent;
						frontier.push(tmp);
						break;
					}
					frontier.push(tmp);
				}
				//printf("pushing: %d %d\n", child->x, child->y);
				frontier.push(child);

				
			}
			parent->discovered = 1;	
		}
		
	}
	return expanded;
}

int IDA_STAR_helper(struct Node* parent,struct Node* target, int g, int bound, int* expanded)
{
	//check  the end conditions, discovered and whether we reached target
	if(parent->discovered){return 0;}
	else if(parent->x == target->x && parent->y == target->y){
			return FOUND;
	}

	parent->discovered = 1;
	parent->f = parent->g + heuristic(parent, target->x, target->y);

	
	printf("expanded %d times\n", *expanded);
	if(parent->f  > bound){return parent->f;}
	
	int x, y, min = 10000;
	for(int i=0; i<CHILD_NO; i++)
	{
	
		x = parent->x + rowstep[i]; y = parent->y + colstep[i];
		if(!is_valid(x, y)){continue;}
		Node* child = &board[get_index(x, y)];
		int move_cost = (abs(child->x - parent->x) + abs(child->y - parent->y));		
	
		if(!child->discovered)
		{
			(*expanded)++; //increasing the amount of expanded nodes
			child->parent = parent;
			printf("testing (%d, %d) -> (%d, %d)\n", parent->x, parent->y, child->x, child->y);
			int t = IDA_STAR_helper(child, target, parent->g + move_cost, bound, expanded);
			if(t == FOUND)
			{
				return FOUND;
			}
			min = (t < min)?t:min;
		}
	
	}
	return min;
}
int IDA_STAR_search(int startx, int starty, int endx, int endy)
{
	Node* initial = &board[get_index(startx, starty)], *target = &board[get_index(endx, endy)];
	initial->parent = NULL;
	initial->f = heuristic(initial, endx, endy);
	initial->g = 0;
	int bound = initial->f, expanded= 0;
	std::list<Node*> frontier;
	while(1)
	{
		int t = IDA_STAR_helper(initial, target, 0, bound, &expanded);
		if( t == FOUND)
		{
			print_path(&board[get_index(endx, endy)], startx, starty);
			return expanded;
		}
		bound = t;
	}
	return expanded;
}

//calls the appropriate function for the search type
void search(int search_type, int startx, int starty, 
				int endx, int endy)
{
	int expanded=0;
	reset_board();
	switch(search_type){
		case BFS:
			expanded = BFS_search(startx, starty, endx, endy);
			break;
			
		case DFS:
			expanded = DFS_search(startx, starty, endx, endy);
			break;
		case IDS:
			expanded = IDS_search(startx, starty, endx, endy);
			break;

		case A_STAR:
			expanded = A_STAR_search(startx, starty, endx, endy);
			break;

		case IDA_STAR:
			expanded = IDA_STAR_search(startx, starty, endx, endy);
			break;
	}
	printf("\nWhen performing the algorithm, expanded %d nodes.\n",expanded );
}
void print_introduction()
{
	printf("-----\n"
			"Enter the number of the algorithm to use, and starting x,y and ending x,y  like:\n"
			" algorithm startx starty endx endy.\n"
			"The algorithms numbers are as follows:\n"
			"\t1.BFS\n"
			"\t2.DFS\n"
			"\t3.IDS\n"
			"\t4.A*\n"
			"\t5.IDA*\n"
			"-----\n\n");
}
int main(int argc, char** argv)
{
	print_introduction(); //show how to input the numbers
	int algorithm =1, startx, starty, endx, endy;

	Node n1, n2, n3;

	while(algorithm > 0){
		//scanf("%d %d %d %d", &algorithm, &startx, &starty, &endx, &endy);
		std::cin>>algorithm>>startx>>starty>>endx>>endy;
		printf("bout to search %d %d %d %d\n", startx, starty, endx, endy);
		search(algorithm, startx, starty, endx, endy);
	}	
}
