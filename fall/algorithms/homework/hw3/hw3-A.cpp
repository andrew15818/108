#include<iostream>
#include<queue>
#include<vector>
#include<cstdio>
#define MAX_WEIGHT 10000000001
using namespace std;
struct Vertex
{
	long long int id, dist; //dist from the source
	vector<pair<long long int, Vertex*> > adj;
	Vertex* predecessor = NULL; //the predecessor of vertices along the shortest path
};
class  Graph
{
	protected:
		bool *visited;
		Vertex* vertices;
		long long int nodes, edges, source, dest; 
		priority_queue< pair<long long int, Vertex*> > nodeQueue;
	public:
		Graph(long long int nodes, long long int edges, long long int source, long  long int dest)
		{
			this->nodes = nodes;
			this->edges = edges;
			this->source = source;
			this->dest = dest;

			visited = new bool[nodes]; //to keep track of cycles
			vertices = new Vertex[nodes]; //for the adjacency
		}
		~Graph()
		{
			delete[] visited;
			delete[] vertices;
		}
		void addEdge(long long int source, long long int dest, long long int weight)
		{
			pair< long long int, Vertex* > tmp = make_pair(weight, &vertices[dest]);
			vertices[source].adj.push_back(tmp);
			vertices[source].dist = (this->source == source)?0: MAX_WEIGHT;		

		}
};
int main(){
	
	return 0;
}
