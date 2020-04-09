#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
//#include<bfs.h>
#include<stack>
#include<list>
#include<stdlib.h>

#define BFS 1
#define DFS 2
#define IDS 3
#define A_STAR 4
#define IDA_STAR 5
#define BOARD_SIZE 8
#define CHILD_NO 8
#define MAX_DEPTH 10
//int board[BOARD_SIZE][BOARD_SIZE];

//these functions return the number of expanded nodes
struct Node
{
	int x, y, discovered = 0, children=0;
	Node *parent, *child[CHILD_NO];
	void add_child(struct Node* node)
	{
		if(children >= CHILD_NO){return;}
		child[children] = node;
		children++;
		return;
	}
};
const int rowstep[CHILD_NO] = {1, 1, -1, -1, 2, 2, -2, -2}; 
const int colstep[CHILD_NO] = {2, -2, 2, -2, 1, -1, 1, -1};
static Node board[BOARD_SIZE * BOARD_SIZE];
int expanded = 0; //number of expanded nodes for each algorithm

void reset_board()
{
	//we set the x and y every iteration?
	expanded = 0;
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
inline int get_index(int row, int col)
{
	return row*BOARD_SIZE + col;
}
inline int h(int currx, int curry, int targetx, int targety)
{
	return (abs(targetx - currx) + abs(targety - curry))/3;
}
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
	std::list<Node*> frontier;
	//preprocessing

	int index = get_index(startx, starty);
	Node* initial = &board[index];
	initial->parent = NULL;
	frontier.push_back(initial);
	
	while(!frontier.empty())
	{
		Node* current = frontier.front();
		
		//if(!is_valid(current->x, current->y)){ 
		//	continue;
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
		Node* tmp = &board[get_index(current->x + 1, current->y + 2)];
		current->discovered = 1;

		for(int i=0; i< CHILD_NO; i++){
			int x = current->x + rowstep[i], y = current->y + colstep[i];

			//add child point to frontier if valid
			if(is_valid(x, y)){
				if(!board[get_index(x, y)].discovered){
					frontier.push_back(&board[get_index(x, y)]);
					board[get_index(x,y)].parent = current;
				}
			}
		}
		
	}
	return 0;
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
int IDS_helper(int startx, int starty, int endx, int endy, int curr_depth)
{
	
	Node* current = &board[get_index(startx, starty)];

	if(current->x == endx && current->y == endy) //1.check if we found the target
	{
		//printf("found (%d, %d) with depth: %d \n",endx, endy, curr_depth);
		printf("\tparent:(%d, %d)\n", current->parent->x, current->parent->y);
		print_path(current, endx, endy);
		return 1;
	}
	if(curr_depth > MAX_DEPTH || current->discovered){
		printf("MAX_DEPTH exceeded.\n");
		return 0;
	}
	current->discovered = 1;
	int x ,y;
	Node* to_check;
	for(int i =0; i<CHILD_NO; i++)
	{
		x = current->x + rowstep[i]; y = current->y + colstep[i];
		if(is_valid(x, y)){
				to_check = &board[get_index(x, y)];
				
				if(!to_check->discovered){
					to_check->parent = current;
					if(IDS_helper(x, y, endx, endy, curr_depth++) > 0){
						return 1;
					}

				}
		}
	}
	return 0;

}
//want to run limited DFS from starting nodes found in BFS manner
int IDS_search(int startx, int starty, int endx, int endy){

	int iterations = 1, found = 0;
	board[get_index(startx, starty)].parent = NULL;
	for(iterations; iterations <= MAX_DEPTH; iterations++){
		found = IDS_helper(startx, starty, endx, endy, iterations);
		if (found > 0){
			break;
		}
	}
	print_path(&board[get_index(endx, endy)], startx, starty);
	return found;
}

int  A_STAR_search(int startx, int starty, int endx, int endy){
	Node* initial = &board[get_index(startx, starty)];
	initial->parent = NULL;
	int x,y;
	std::priority_queue<Node*> frontier;	
	frontier.push(initial);
	Node* tmp = frontier.top();
	//select the best node that has not been discovered yet
	
	while(!frontier.empty())
	{
		Node* tmp = frontier.top();		
		frontier.pop();
		
	}
	return 0;
}

int IDA_STAR_search(int startx, int starty, int endx, int endy){
	return 0;
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
	printf("When performing the algorithm, expanded %d nodes.\n",expanded );
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
