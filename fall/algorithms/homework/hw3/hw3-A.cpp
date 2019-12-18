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
	long int deltaDistance; //basically the weight value from predecessor to current node
	long long int edgeCount; //how many edges we've traveled through
	vector<pair<long long int, Vertex*> > adj;
	Vertex* predecessor = NULL; //the predecessor of vertices along the shortest path
	Vertex* successor = NULL; //the successor in the graph
	bool visited = false;
};
struct compare
{
	bool operator()(const Vertex* v1, const Vertex* v2){
		return v1->dist > v2->dist;
	}
};
class  Graph
{
	protected:
		bool *visited;
		Vertex* vertices;
		long long int nodes, edges, source, dest; 
		//priority_queue< pair<long long int, Vertex*> > nodeQueue;
	public:
		bool foundShortestPath = false;
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
		}
		/*TODO: create the vertices and edges separately, otherwise, not all the vertices will be defined*/
		void addEdge(long long int source, long long int dest, long long int weight)
		{
			pair< long long int, Vertex* > tmp = make_pair(weight, &vertices[dest]);
			vertices[source].adj.push_back(tmp);
			vertices[source].id = source;	
			vertices[source].dist =  MAX_WEIGHT;		
			vertices[source].edgeCount=  MAX_WEIGHT;		

			vertices[dest].edgeCount =  MAX_WEIGHT;		
			vertices[dest].id = dest;
			vertices[dest].dist = MAX_WEIGHT;
		}
		void relax(Vertex* v1, Vertex* v2, long long int weight )
		{
			//printf("checking: %lld(%lld) and %lld(%lld) with weight %lld\n", v1->id, v1->dist, v2->id, v2->dist, weight);
			if(v2->dist > v1->dist + weight && v2->edgeCount > v1->edgeCount
					&& weight >= v1->edgeCount+1){

				v2->dist = v1->dist + weight;	
				v2->edgeCount = v1->edgeCount + 1;
				v2->deltaDistance = weight;
				v2->predecessor = v1;
				v1->successor = v2;
			}
		}
		void search()
		{
			//list<Vertex*> nodeQueue;
			priority_queue<Vertex*, vector<Vertex*>, compare> nodeQueue;

			nodeQueue.push(&vertices[source]);
			vertices[source].dist = 0;
			vertices[source].edgeCount = 0;
			//printf("%lld\n", vertices[source].dist);

			while( !nodeQueue.empty() ){
				//make_heap(nodeQueue.begin(), nodeQueue.end(), compare);
				Vertex* v = nodeQueue.top();
				v->visited = true;
				nodeQueue.pop();
				
				//cout<<"comparing: "<<v->id<<endl;
				vector< pair<long long int, Vertex*> >::iterator it = v->adj.begin();
				for(it; it!= v->adj.end(); it++){

					relax(v, it->second, it->first);	
					if(it->second->visited == false){
						nodeQueue.push(it->second);
					}
				}
				
				if(v->id == dest){
					//foundShortestPath = true;
					return;
					//printf("There does exist a shortest path\n");	
				}	
				
			}
		}
		int printPredecessor(long long int id)
		{
			Vertex* v = &vertices[id];
			if(v->id == source){
				printf("%lld ",v->id);	
				return 1;
			}
			else if(v->predecessor == NULL){
				printf("-1");	
				return 0;
			}
				printPredecessor(v->predecessor->id);
				printf("%lld ",v->id);			
		}
};
int main(){
	long long int testcases, nodes, edges, startId, endId;	
	long long int u, v, weight;
	cin>>testcases;
	for(long long int i=0; i<testcases;i++){
		scanf("%lld %lld %lld %lld", &nodes, &edges, &startId, &endId);
		Graph g(nodes, edges, startId, endId);
		for(long long int j=0; j<edges; j++){
			scanf("%lld %lld %lld", &u, &v, &weight);
			g.addEdge(u, v, weight);
		}
		g.search();
		g.printPredecessor(endId);
		printf("\n");
	}
	return 0;
}
