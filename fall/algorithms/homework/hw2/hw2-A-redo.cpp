#include<iostream>
#include<cstdio>
#define INCREASING 1
#define DECREASING 0
using namespace std;

//going for a bottom-up approach here
long long int max(long long int n1, long long int n2 ){
	return (n1>=n2)?n1:n2;	
}
int main(){
	
	long long int dimensions, monoCount;
	cin>>dimensions>>monoCount;
	long long int arr[dimensions][dimensions],state[dimensions][dimensions], dp[dimensions][dimensions];
	for(long long int i =0; i<dimensions; i++){
		for(long long int j=0; j<dimensions; j++){
			cin>>arr[i][j];	
			dp[i][j] = -1;
		}
	}
	//printf("INCREASING %d DECREASING %d\n",INCREASING,DECREASING);
	//preprocessing
	for(long long int i=1; i<dimensions;i++){
		state[i][0] = (arr[i][0] > arr[i-1][0])?INCREASING:DECREASING;
		state[0][i] = (arr[0][i] > arr[0][i-1])?INCREASING:DECREASING;
		//need to also set the dp values
		//make more readable
		dp[i][0] = (state[i][0]==state[i-1][0])?dp[i-1][0]:dp[i-1][0]--;
		dp[0][i] = (state[0][i]==state[0][i-1])?dp[0][i-1]:dp[0][i-1]--;
	}
	dp[0][0]=monoCount;
	for(long long int i=1; i<dimensions; i++){
		for(long long int j=1; j<dimensions; j++){
			//TODO: figure out how to use the arr, dp, and state arrays together				
			//maybe process the right and upper elements and then just take the max
			//for the left element
			long int leftCount= dp[i][j-1];
			if((arr[i][j-1] > arr[i][j] && state[i][j-1] == DECREASING)
				|| (arr[i][j-1] < arr[i][j] && state[i][j-1] == INCREASING)){
				leftCount--;
			}	
		
			//for the top element
			long int topCount = dp[i-1][j];	
			if((arr[i-1][j] > arr[i][j] && state[i-1][j] == DECREASING)
				|| (arr[i-1][j] <arr[i][j] && state[i-1][j]== INCREASING)){
				topCount--;	
			}
		
			//choosing which element goes in the dp and state arrays
			long long int maxState = -1, maxDP = 69;
			if(leftCount>=topCount){
				maxState = state[i][-1];	
				maxDP = leftCount;
			}
			else if(leftCount<topCount){
				maxState = state[i-1][j];
				maxDP = topCount;
			}
			state[i][j] = maxState;
			dp[i][j] =	maxDP; 
		}	
	}
	for(long int i=0; i<dimensions; i++){
		for(long int j=0; j<dimensions; j++){
			printf("%lld ",state[i][j]);
			if(j==dimensions-1){
				printf("\n");	
			}
		}
	}
	printf("\n");	
	for(long int i=0; i<dimensions; i++){
		for(long int j=0; j<dimensions; j++){
			printf("%lld ",dp[i][j]);
			if(j==dimensions-1){
				printf("\n");	
			}
		}
	}
}
