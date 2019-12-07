#include<iostream>
#include<vector>
#include<utility>
#include<cstdio>
using namespace std;

struct Vertex{
	long long int id,color; //the color is to use while we search
	long long int distance; //distance from the center
	vector<pair<long long int , Vertex*> > adj;
};
/*
struct Edge{
	//long long int src, dest, weight;
	Vertex* src, dst;
	vector<Edge*> adjList;
};
*/
class Graph{
	protected:
		long long int nodes, edges, src, dst; 			
		Vertex* vertices;	
	public:
		Graph(long int nodes, long int edges, long int srcID, long int dstID)
		{
			this->nodes = nodes;
			this->edges = edges;
			this->src = srcID;
			this->dst = dstID;
			vertices = new Vertex [this->nodes]; 	
		}
		void addEdge(long long int source, long long int dest, long long int weight);
		//for debugging purposes
		void printGraphInfo();
		long long int search(Vertex*);
};

void Graph::addEdge(long long int source, long long int dest, long long int weight)
{
	//printf("\tsourve ID: %lld\t source dest:%lld\t weight:%lld\n", source, dest, weight);	
	vertices[source].adj.push_back(make_pair(weight, &vertices[dest]));
	vertices[source].id = source;
	vertices[dest].id = dest;
	vertices[dest].distance = -1; //initializing the value	
	vertices[source].distance = -1;

}

void Graph::printGraphInfo()
{
	vector<pair<long long int, Vertex*> >::iterator it;
	for(int i =0; i<nodes; i++){
		it = vertices[i].adj.begin();	
		printf("Vertex %d: ", i);
		for(it; it!=vertices[i].adj.end(); it++){
			printf("->%lld,(%lld)", (*it).second->id, (*it).first);
		}
		printf("\n");
	}
} 
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	long int testcases, nodes, edges, srcID, dstID;
	cin>>testcases;
	for(int i =0; i< testcases; i++){
		cin>>nodes>>edges>>srcID>>dstID;	
		Graph graph(nodes, edges, srcID, dstID);
		long long int srcVertex, dstVertex, weight;
		for(int j=0; j< edges; j++){
			cin>>srcVertex>>dstVertex>>weight;
			graph.addEdge(srcVertex,dstVertex, weight);	
		}
		graph.printGraphInfo();
	}
	return 0;
}
