#include<iostream>
#include<vector>
#include<utility>
#include<cstdio>
#define MAX_WEIGHT 10000000001 //ten million is the max weight
using namespace std;

struct Vertex{
	long long int id,color; //the color is to use while we search
	long long int distance; //distance from the center
	vector<pair<long long int , Vertex*> > adj;
};
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
		void init();
		void addEdge(long long int source, long long int dest, long long int weight);
		void relax(Vertex& v1, Vertex&v2, long long int weight);
		//for debugging purposes
		void printGraphInfo();
		long long int search(Vertex*);
};
void Graph::init()
{
	for(long long int i=0; i<nodes; i++){
		vertices[i].distance = MAX_WEIGHT;	
	}
	vertices[src].distance = 0;
}
void Graph::addEdge(long long int source, long long int dest, long long int weight)
{

	vertices[source].adj.push_back(make_pair(weight, &vertices[dest]));
	vertices[source].id = source;
	//vertices[source].distance = MAX_WEIGHT; //we will relax this distance later

	vertices[dest].id = dest;
	//vertices[dest].distance = MAX_WEIGHT; //initializing the value	
}
void Graph::relax(Vertex& v1, Vertex &v2, long long int weight)
{
	if(v2.distance > v1.distance + weight){
		v2.distance = v1.distance + weight;	
	}	
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
		graph.init();
		long long int srcVertex, dstVertex, weight;
		for(int j=0; j< edges; j++){
			cin>>srcVertex>>dstVertex>>weight;
			graph.addEdge(srcVertex,dstVertex, weight);	
		}
		graph.printGraphInfo();
	}
	return 0;
}
