#include<cstdio>
#include<vector>
#include<iostream>
#include<queue>
#include<math.h>
#define  MAX_WEIGHT 1000000001
using namespace std;
struct Vertex
{
	long long int id;
	long long int powerStationCost; //cost to build a station 
	long long int x, y; //coords
	long long int minimum = MAX_WEIGHT;
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
		long long int distance(const Vertex* v1, const Vertex* v2)
		{
			return abs(v1->x - v2->x) + abs(v1->y - v2->y);
		}
		long long int minCost( long long int n1, long long int n2)
		{
			return (n1<=n2)?n1:n2;
		}
		void printGraph(){
			for(int i=0; i< nodes; i++)	{
				printf("%lld: (%lld, %lld), $%lld, %lld\n", i, vertices[i].x, vertices[i].y, vertices[i].powerStationCost,
								vertices[i].minimum);	
			}
		}
		void buildMST()
		{
			for(int i=0; i< nodes; i++){
				Vertex* v1 = &vertices[i];
				for(int j=0; j< nodes; j++){
					Vertex* v2 = &vertices[j];
					long long int nodeDist = distance(v1, v2);
					v2->minimum = minCost(nodeDist, v2->powerStationCost);
				}
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
	graph.buildMST();
	graph.printGraph();
	return 0;
}
