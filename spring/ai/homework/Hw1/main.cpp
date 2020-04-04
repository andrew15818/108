#include<iostream>
#include<cstdio>
#define DFS 1
#define BFS 2
#define IDS 3
#define A_STAR 4
#define IDA_STAR 5

//these functions return the number of expanded nodes
inline int is_valid(int x, int y)
{
	return (x < 0|| y < 0) || (x > 7 || y > 8);
}
int DFS_search(int startx, int starty)
{

}
int  BFS_search(int startx, int starty){}
int IDS_search(int startx, int starty){}
int  A_STAR_search(int startx, int starty){}
int IDA_STAR_search(int startx, int starty){}

//calls the appropriate function for the search type
void search(int search_type, int startx, int starty)
{
	switch(search_type){
		case DFS:
			DFS_search(startx, starty);
			break;
			
		case BFS:
			BFS_search(startx, starty);
			break;

		case IDS:
			IDS_search(startx, starty);
			break;

		case A_STAR:
			A_STAR_search(startx, starty);
			break;

		case IDA_STAR:
			IDA_STAR_search(startx, starty);
			break;
	}
}
void print_introduction()
{

}
int main(int argc, char** argv)
{
	
}
