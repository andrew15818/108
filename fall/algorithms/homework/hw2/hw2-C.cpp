#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long int max(long long int n1, long long int n2)
{
	return (n1>=n2)?n1:n2;
}
long long int max3(long long int n1, long long int n2, long long int n3)
{
	long long int tmp = max(n1, n2);
	return (tmp>=n3)?tmp:n3;
}
long long int knap(long long int* best, long long int* weights, long long int* values,long int index, long long int weight,
				long long int prevWeight)
{
	printf("Current weight: %lld\n", weight);
	if(index<0 || weight<0){		
		return 0;	
	}
	else if (best[index] != -1){
		return best[index];	
	}
	long long int temp;
	if(weight - weights[index] < 0){

		printf("at %lld, weight: %lld, current weight: %lld, prevoius weight: %lld\n",index, weight, weights[index], prevWeight);
		temp = knap(best, weights, values, index-1, weight, prevWeight);	
		best[index] = temp;
		return best[index];
	}

	else if(prevWeight/2 >= weights[index] || weights[index]/2 >= prevWeight){
		//printf("going to compare %lld and %lld\n", weights[index], prevWeight);
		//printf("at %lld, weight: %lld, current weight: %lld, prevoius weight: %lld\n",index, weight, weights[index], prevWeight);
		temp = max3(
			knap(best, weights, values, index-1, weight-weights[index], weights[index]) + values[index],	//including the item inside the prevweight
			knap(best, weights, values, index-1, weight-weights[index], prevWeight) + values[index], 
			knap(best, weights, values, index-1, weight, prevWeight) 									//not including the item
		);	
		printf("at %lld, the best alterantive is : %lld\n", index, temp);
		best[index] = temp;
		return temp;
	}

}
int main(){
	long int n,k;
	cin>>n>>k;
	long long int weights[n],values[n], best[n];//best is the arr we use for memoization

	long long int maxerino = -1;
	for(long int i = 0; i<n;i++ ){

		cin>>weights[i]>>values[i];
		best[i] = -1;
		maxerino = max(maxerino, weights[i]);
	}

	cout<<knap(best, weights, values, n-1,k, maxerino)<<endl;
	return 0;
}
