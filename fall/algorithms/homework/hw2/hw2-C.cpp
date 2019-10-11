#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct doll{
	long long int weight, value;
};
bool mine(const doll& a, const doll& b){
	return a.weight<=b.weight;
}
bool func(long int i, long int j){

}
long long int max(long long int n1, long long int n2)
{
	return (n1>=n2)?n1:n2;
}
long long int knap(long long int* weights, long long int* values,long int index, long long int weight,
				long long int prevWeight)
{

	if(index<0 || weight<0){
		return 0;	
	}
	printf("In this call: index: %lld\t weight:%lld\t prevWeight:%lld, and we're checking %lld\n",index,weight,prevWeight, weights[index]);	
	if(weight - weights[index] < 0 /*|| (prevWeight/2 < weights[index] && prevWeight!= -1)*/){
		return knap(weights, values, index-1, weight, prevWeight);	
	}
	if(prevWeight/2 >= weights[index]){
		return max(knap(weights, values, index-1, weight-weights[index],weights[index])+values[index],
						knap(weights, values, index-1,weight, prevWeight));	
	}

	return knap(weights, values, index-1, weight, prevWeight);
	
}
int main(){
	long int n,k;
	cin>>n>>k;
	long long int weights[n],values[n];

	long long int maxerino = -1;
	for(long int i = 0; i<n;i++ ){

		cin>>weights[i]>>values[i];
		maxerino = max(maxerino, weights[i]);
	}

	cout<<knap(weights, values, n-1,k,2*maxerino+1)<<endl;
	return 0;
}
