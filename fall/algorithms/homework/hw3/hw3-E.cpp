#include<iostream>
#include<vector>
#include<cstdio>
using namespace std;
struct Vertex
{
	long long int value;
	vector<Vertex*> adj;
	Vertex* parent;
};
Vertex *vertices[100000];
int main()
{
	long long int q, n;
	cin>>n>>q;
	long long int parentId;
	for(int i = 1; i<= n; i++)
	{
		cin>>parentId;
		vertices[i]->parent = vertices[parentId];
	}
	long long int value;
	for(int j=1; j<= n; j++){
		cin>>value;
		vertices[j]->value= value;
	}
	for(int i=1; i<= n; i++){
		printf("%lld: parent: %lld, value: %lld\n", i, vertices[i]->parent->value, vertices[i]->value);		

	}
	return 0;
}
