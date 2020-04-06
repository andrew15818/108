#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<list>
#define BFS 1
#define DFS 2
#define IDS 3
#define A_STAR 4
#define IDA_STAR 5
#define BOARD_SIZE 8
#define CHILD_NO 8
//int board[BOARD_SIZE][BOARD_SIZE];

//these functions return the number of expanded nodes
struct Node
{
	int x, y, discovered  = 0, children=0;
	Node *parent, *child[CHILD_NO];
	void add_child(struct Node* node)
	{
		if(children >= CHILD_NO){return;}
		child[children] = node;
		children++;
		return;
	}
};

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
	//reset_board();
	int index = get_index(startx, starty);
	Node* initial = &board[index];
	initial->parent = NULL;
	frontier.push_back(initial);
	
	while(!frontier.empty())
	{
		Node* current = frontier.front();
		current->discovered = 1;
		if(!is_valid(current->x, current->y)){
			continue;
		}

		if(current->x == endx && current->y == endy)
		{
			print_path(current, startx, starty);
			return expanded;
		}
		expanded++;
		frontier.pop_front();
		Node* tmp = &board[get_index(current->x + 1, current->y + 2)];
		for(int i=0; i< CHILD_NO; i++){
			int x = current->x, y = current->y;
			switch(i % CHILD_NO){
				case 0:
					x+=1;y+=2;
					break;
				case 1:
					x+=1;y-=2;
					break;
				case 2:
					x-=1;y+=2;
					break;
				case 3:
					x-=1;y-=2;
					break;
				case 4:
					x+=2;y+=1;
					break;
				case 5:
					x+=2;y-=1;
					break;
				case 6:
					x-=2;y+=1;
					break;
				case 7:
					x-=2;y-=1;
					break;
			}
			//add child point to frontier if valid
			if(is_valid(x, y)){
				if(!board[get_index(x,y)].discovered){
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
	//reset_board();
	Node *current = &board[get_index(startx, starty)];
	printf("starting with: %d, %d\n", current->x, current->y);
	board[get_index(current->x, current->y)].discovered = 1;
	if(startx == endx && starty == endy){
		printf("Found Target\n");
		return expanded;
	}
	
	for(int i = 0; i<CHILD_NO; i++){
		int x=current->x, y= current->y;
		switch(i % CHILD_NO)
		{
			case 0:
				x+=1; y+=2;
				break;
			case 1:
				x+=1; y-=2;
				break;
			case 2:
				x-=1; y+=2;
				break;
			case 3:
				x-=1; y-=2;
				break;
			case 4:
				x+=2; y+=1;
				break;
			case 5:
				x+=2; y-=1;
				break;
			case 6:
				x-=2; y+=1;
				break;
			case 7:
				x-=2; y-=1;
				break;
		}
		//recursively call if there is a valid, unexplored node
		if(is_valid(x, y) && !board[get_index(x, y)].discovered)
		{
			board[get_index(x, y)].parent = current;
			DFS_search(x, y, endx, endy);
		}
	}	
	return 0;
}

int IDS_search(int startx, int starty, int endx, int endy){
	return 0;
}

int  A_STAR_search(int startx, int starty, int endx, int endy){
	return 0;
}

int IDA_STAR_search(int startx, int starty, int endx, int endy){
	return 0;
}

//calls the appropriate function for the search type
void search(int search_type, int startx, int starty, 
				int endx, int endy)
{
	reset_board();
	switch(search_type){
		case BFS:
			BFS_search(startx, starty, endx, endy);
			break;
			
		case DFS:
			DFS_search(startx, starty, endx, endy);
			break;
		case IDS:
			IDS_search(startx, starty, endx, endy);
			break;

		case A_STAR:
			A_STAR_search(startx, starty, endx, endy);
			break;

		case IDA_STAR:
			IDA_STAR_search(startx, starty, endx, endy);
			break;
	}
}
void print_introduction()
{
	printf("-----\n"
			"Enter the number of the algorithm to use, and starting x,y and ending x,y  like:\n"
			" algorithm startx starty endx endy.\n"
			"The algorithms numbers are as follows:\n"
			"\t1.DFS\n"
			"\t2.BFS\n"
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
