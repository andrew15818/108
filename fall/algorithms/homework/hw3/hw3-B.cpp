#include<cstdio>
#include<vector>
#include<iostream>
#include<queue>
using namespace std;
struct Vertex
{
	long long int id;
	long long int powerStationCost; //cost to build a station 
	long long int x, y; //coords
};
class Graph
{
	public:
		int nodes; //how many nodes
		long long int currVertex;
		Vertex* vertices;

		Graph(int quantity):nodes(quantity){
			vertices = new Vertex[quantity];		
			currVertex = 0;
		};
		void setPowerCost(long long int index, long long int cost)
		{
			vertices[index].powerStationCost = cost;
		}
		void addNode(long long int index, long long int x, long long int y)
		{
			vertices[index].x = x;	
			vertices[index].y = y;
		}
		void printGraph(){
			for(int i=0; i< nodes; i++)	{
				printf("%lld: (%lld, %lld), $%lld\n", i, vertices[i].x, vertices[i].y, vertices[i].powerStationCost);	
			}
		}
};
int main(){
	int nodes;
	cin>>nodes;
	Graph graph(nodes);
	long long int x, y;
	long long int cost;
	for(int i =0; i< nodes; i++){
		cin>>cost;	
		graph.setPowerCost(i, cost);
	}
	
	for(int i=0; i< nodes; i++){
		cin>>x>>y;	
		graph.addNode(i, x, y);
	}
	graph.printGraph();
	return 0;
}
