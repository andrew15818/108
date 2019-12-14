#include<iostream>
#include<queue>
#include<vector>
#include<list>
#include<cstdio>
#include<algorithm>
#define MAX_WEIGHT 10000000001
using namespace std;
struct Vertex
{
	long long int id, dist; //dist from the source
	vector<pair<long long int, Vertex*> > adj;
	Vertex* predecessor = NULL; //the predecessor of vertices along the shortest path
	bool visited = false;
};
class  Graph
{
	protected:
		bool *visited;
		Vertex* vertices;
		long long int nodes, edges, source, dest; 
		//priority_queue< pair<long long int, Vertex*> > nodeQueue;
	public:
		Graph(long long int nodes, long long int edges, long long int source, long  long int dest)
		{
			this->nodes = nodes;
			this->edges = edges;
			this->source = source;
			this->dest = dest;

			//visited = new bool[nodes]; //to keep track of cycles
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
			vertices[source].id = source;
			vertices[dest].id = dest;
			vertices[source].dist = (this->source == source)?0: MAX_WEIGHT;		

		}
		static bool compare(const Vertex* v1, const Vertex* v2)
		{
			return v1->dist < v2->dist;
		}


		void relax(Vertex* v1, Vertex* v2, long long int weight )
		{
			if(v1->dist > v2->dist + weight){
				v1->dist = v2->dist + weight;
				v1->predecessor = v2;
			}	
		}
		void search()
		{
			list<Vertex*> nodeQueue;
			nodeQueue.push_front(&vertices[source]);
			vertices[source].dist = 0;
			printf("%lld\n", vertices[source].dist);

			while( !nodeQueue.empty() ){
				make_heap(nodeQueue.begin(), nodeQueue.end(), compare);
				nodeQueue.pop_front();
			}
		}
		void printGraph(){
			vector< pair<long long int, Vertex*> >::iterator it;
			for(long int i=0; i<nodes; i++){
				printf("%lld: ", i);
				it = vertices[i].adj.begin();	
				for(it; it != vertices[i].adj.end(); it++){
					printf("-> %lld(%lld)", it->second->id, it->first);
				}
				printf("\n");
			}
			
		}
};
int main(){
	long long int testcases, nodes, edges, startId, endId;	
	long long int u, v, weight;
	cin>>testcases;
	for(long long int i=0; i<testcases;i++){
		//cin>>nodes>>edges>>startId>>endId;	
		scanf("%lld %lld %lld %lld", &nodes, &edges, &startId, &endId);
		Graph g(nodes, edges, startId, endId);
		for(long long int j=0; j<edges; j++){
			scanf("%lld %lld %lld", &u, &v, &weight);
			g.addEdge(u, v, weight);
		}
		g.search();
		//g.printGraph();
	}
	return 0;
}
