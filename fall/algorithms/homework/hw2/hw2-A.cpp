#include<iostream>
#include<cstdio>
#define INCREASING 0
#define DECREASING 1
#define MAX_SIZE 1000
using namespace std;
long int min(long int n1, long int n2)
{
	return (n1<=n2)?n1:n2;
}
long int max(long int n1, long int n2){
	return (n1>=n2)?n1:n2;
}
long int arr[MAX_SIZE][MAX_SIZE];
long int sol[MAX_SIZE][MAX_SIZE];
void printArr(long int dimensions)
{
	for(long int i=0; i<dimensions; i++){
		for(long int j=0; j<dimensions; j++){
			printf("%lld ", sol[i][j]);
			if(j==dimensions-1){printf("\n");}
		}
	}
	printf("\n");
}
///maybe in the sol array we can store the monoCount?
long int paths(long int rows, long int cols, long int curRow, long int curCol, long int mState, long int prevElement, 
				long int monoCount ,long int maxMono)
{
	
	//maybe we can store the monoCount at each step?
	//base cases
	if(curRow <0 || curRow >= rows || curCol < 0 || curCol >= cols || monoCount==0){
		return 0;
	}
	printf("Now checking %lld %lld %lld\n", curRow, curCol ,monoCount);
	if(sol[curRow][curCol] == 0){
		return 0;
	}
	else if(curRow==0 && curCol == 0 && monoCount > 0){
		sol[curRow][curCol] = monoCount;
		return 1;
	}
	//checking increasing monotonicity
	if(arr[curRow][curCol] > prevElement && mState == INCREASING){
		monoCount--;
		mState = DECREASING;
	}		
	else if(arr[curRow][curCol] < prevElement && mState == DECREASING){
		monoCount--;
		mState = INCREASING;
	}
	long int temp = max(
					paths(rows, cols, curRow-1, curCol, mState, arr[curRow][curCol], monoCount, maxMono),
					paths(rows, cols, curRow, curCol-1, mState, arr[curRow][curCol], monoCount, maxMono)
					);
	sol[curRow][curCol] = monoCount; 
	printArr(rows);
	return sol[curRow][curCol];
	
}	
int main(){
	long int dimensions, mLimit;
	cin>>dimensions>>mLimit;
	for(int i =0; i<dimensions; i++){
		for(int j=0; j<dimensions; j++){
			cin>>arr[i][j];
			sol[i][j] = -1;
		}
	}
	//printf("the function when the mstate is first set to increasing\n");
	//printf("the function when  mstate is set to increasing first\n");
	printf("%lld\n", paths(dimensions, dimensions, dimensions-1, dimensions-1, DECREASING, arr[0][0], mLimit, mLimit));
	//printf("%lld\n", paths(dimensions, dimensions, 0, 0, 0, arr[0][0], 1, mLimit));
	/*
	for(int i=0; i<dimensions; i++){
		for(int j=0; j<dimensions; j++){
			printf("%lld ", sol[i][j]);
			if(j==dimensions-1){printf("\n");}
		}
	}
	*/
}
