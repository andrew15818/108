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
int board[BOARD_SIZE][BOARD_SIZE];

//these functions return the number of expanded nodes
struct Node
{
	int x, y, child_count =0 ;
	Node *parent, children[CHILD_NO];
	Node(int x, int y):x(x), y(y){}

	void add_node(struct Node *node){
		children[child_count] = node;	
		child_count++;
		node->parent = this;
	}
};
inline int is_valid(int x, int y)
{
	int tmp = 0;
	tmp = (x < 0 || y < 0 || y >= BOARD_SIZE || x>=BOARD_SIZE)? 0 : 1;
	return tmp;
}
int BFS_search(int startx, int starty, int endx, int endy)
{
	Node initial(startx, endy);
	initial.parent = NULL;
	std::list<Node> frontier;
	frontier.push_back(initial);
	
	//perform fast lookup of whether we already visited this spot
	int expanded = 0, graph[BOARD_SIZE][BOARD_SIZE]; //store whether the point has been visited
	memset(graph, 0, sizeof(graph));
	
	while( !frontier.empty() )
	{
		Node* current = &frontier.front();		
		frontier.pop_front();
		printf("testing: %d %d\n", current->x, current->y);
		expanded++;
		if(!is_valid(current->x, current->y))
		{
			continue;	
		}
		else if(current->x == endx && current->y == endy)	
		{
			printf("Found target.\n");
			return expanded;
		}
		current->add_node(Node(current->x, current->y));
	}
	return 0;
}
/*
int BFS_search(int startx, int starty, int endx, int endy)
{
	//printf("startx: %d\tstarty: %d\tendx: %d\t, endy: %d\n", startx, starty,endx, endy);
	int graph[BOARD_SIZE][BOARD_SIZE]; //store whether the point has been visited
	memset(graph, 0, sizeof(graph));
	std::pair<int, int> initial(startx, starty); //store the point coordinates

	std::list<std::pair<int, int> > frontier;
	Node first(initial.first, initial.second);

	frontier.push_back(initial);


	int expanded = 0;
	while(!frontier.empty()){

		std::pair<int, int>current = frontier.front();
		frontier.pop_front();
		expanded++;
		if(current.first == endx && current.second == endy){
			printf("arrived at (%d, %d). Found target\n",current.first, current.second);
			break;
		}

		//continue if we've already expaned this node.
		if(graph[current.first][current.second] == 1 || !is_valid(current.first, current.second)){ 
			continue;
		}
		printf("(%d,%d) is being checked with %d elements in list\n", 
				current.first, current.second, frontier.size());


		graph[current.first][current.second] = 1;
		//next nodes in line
		frontier.push_back(std::pair<int, int>(current.first+1, current.second+2));
		frontier.push_back(std::pair<int, int>(current.first+1, current.second-2));
		frontier.push_back(std::pair<int, int>(current.first-1, current.second+2));
		frontier.push_back(std::pair<int, int>(current.first-1, current.second-2));

		frontier.push_back(std::pair<int, int>(current.first+2, current.second+1));
		frontier.push_back(std::pair<int, int>(current.first+2, current.second-1));
		frontier.push_back(std::pair<int, int>(current.first-2, current.second+1));
		frontier.push_back(std::pair<int, int>(current.first-2, current.second-1));
	}
	printf("returning %d expanded\n", expanded);
	return expanded;
}
*/
int DFS_search(int startx, int starty, int endx, int endy){
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

	while(algorithm > 0){
		//scanf("%d %d %d %d", &algorithm, &startx, &starty, &endx, &endy);
		std::cin>>algorithm>>startx>>starty>>endx>>endy;
		printf("bout to search %d %d %d %d\n", startx, starty, endx, endy);
		search(algorithm, startx, starty, endx, endy);
	}
}
