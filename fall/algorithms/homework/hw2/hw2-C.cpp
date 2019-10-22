#include<iostream>
#include<cstdio>
#include<cstring>
#define SIZE 100
using namespace std;
//first try to implement the naive case,
//then attempt to memoize
long long int dp[100][100];

long long int max(long long int n1, long long int n2){
	return (n1>=n2)?n1:n2;
}
long int knap(long long int* weights, long long int* values , long long int index, long long int weightLeft,
				long long int smallest, long long int largest)
{
	if(index<0){
		return 0;	
	}

	printf("index: %lld\t weightLeft:%lld\n",index,weightLeft);
	//if we memoized the solution
	if(dp[index][weightLeft]!=-1){
		//printf("I was useful!\n");	
		return dp[index][weightLeft];
	}
	//else if the item is twice as small as the current smallest
	else if(weights[index]<=(smallest/2)){
		//another recursive call	
	}
	else if(weights[index]>(largest*2)){
		//yet another recursive call	
	}
	
	//else if the item is twice as big as the current biggest
}
int main(){
	int dolls, totalWeight;
	cin>>dolls>>totalWeight;
	long long int weights[dolls], values[dolls];
	for(int i=0; i<dolls; i++){
		cin>>weights[i]>>values[i];	
	}
	memset(dp,-1, sizeof(dp));
	/*
	for(int i=0; i<SIZE; i++){
		for(int j=0; j<SIZE; j++){
			printf("%lld ", dp[i][j]);	
			if(j==SIZE-1){printf("\n");}
		}	
	}*/
	printf("%lld\n",knap(weights, values, dolls-1, totalWeight));
	return 0;
}
