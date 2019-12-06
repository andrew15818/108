#include<iostream>
#include<vector>
#include<deque>
using namespace std;

struct Vertex{
	long int id,color; //the color is to use while we search
};

struct Edge{
	//long long int src, dest, weight;
	Vertex* src, dst;
	vector<Edge*> adjList;
};

class Graph{
	protected:
		long int nodes, edges, src, dst; 			
		Edge **adjList;
	public:
		Graph(long int nodes, long int edges, long int srcID, long int dstID)
		{
			this->nodes = nodes;
			this->edges = edges;
			this->src = srcID;
			this->dst = dstID;
			adjList = new Edge *[this->nodes]; 

			for(long int i =0; i< nodes; i++)
			{
					
			}
		}
};

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	long int testcases, nodes, edges, srcID, dstID;
	cin>>testcases;
	for(int i =0; i< testcases; i++){
		cin>>nodes>>edges>>srcID>>dstID;	
		Graph graph(nodes, edges, srcID, dstID);
	}
	return 0;
}
