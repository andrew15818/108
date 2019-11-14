#include<iostream>
#include<cstdio>
#define INCREASING 0
#define DECREASING 1
using namespace std;
long int arr[1000][1000];
long int sol[1000][1000];
long int max(long int n1, long int n2){
	return (n1>=n2)?n1:n2;
}


long int solve(int rows, int cols, int curRow, int curCol, int state, int prevElement, int monoCount)
{
	//static int counter =0;
	if(curRow < 0 || curRow >= rows || curCol < 0 || curCol >= cols || monoCount <=0){
		return 0;
	}
	//printf("calling %dth time \n",counter++);
	if( sol[curRow][curCol] != -1){
		return sol[curRow][curCol];
	}

	if(state == INCREASING){
		//printf("state is increasing at %d %d\n", curRow, curCol);
		if( arr[curRow][curCol] < prevElement){
			//printf("changing state from inc to dec at %ld %ld\n",curRow, curCol);
			state = DECREASING;
			monoCount--;
		}
	}
	if(state == DECREASING){
		//printf("state is decreasing at %d %d\n", curRow, curCol);
		if( arr[curRow][curCol] > prevElement ){
			//printf("changing state from dec to inc  at %ld %ld\n",curRow, curCol);
			state = INCREASING;
			monoCount--;
		}
	}
	if(rows ==0 && cols==0){
		return (monoCount>0)?1:0;
	}
	sol[curRow][curCol] = max(sol[curRow][curCol], monoCount);
	return solve(rows, cols, curRow-1, curCol, state, arr[curRow][curCol], monoCount) ||
	solve(rows, cols, curRow, curCol-1, state, arr[curCol][curCol], monoCount);
}
long int initSolve(int dimensions, int monoCount)
{
	int curRow = dimensions -1, curCol = dimensions-1, state1, state2;	
	state1 = (arr[curRow-1][curCol] > arr[curRow][curCol])?INCREASING:DECREASING;
	state2 = (arr[curRow][curCol-1] > arr[curRow][curCol])?INCREASING:DECREASING;
	sol[curRow][curCol] = monoCount;
	/*
	return (solve(dimensions, dimensions, curRow-1, curCol, state1, arr[curRow][curCol], monoCount) || 
			solve(dimensions, dimensions, curRow, curCol-1, state2, arr[curRow][curCol], monoCount));
	*/
	return (solve(dimensions, dimensions, curRow, curCol-1, state1, arr[curRow][curCol], monoCount) || 
			solve(dimensions, dimensions, curRow-1, curCol, state2, arr[curRow][curCol], monoCount));
	
}
void printArray(int dimensions){
	for(int i =0; i<dimensions; i++){
		for(int j=0; j<dimensions; j++){
			printf("%ld ", sol[i][j]);	
			if(j==dimensions-1)printf("\n");
		}	
	}
}

int main()
{
	
	int dimensions, monoCount;
	cin>>dimensions>>monoCount;
	for(int i=0; i<dimensions; i++){
		for(int j=0; j<dimensions; j++){
			cin>>arr[i][j];
			sol[i][j]=-1;
		}
	}
	//solve(dimensions, dimensions, dimensions-1, dimensions-1, DECREASING, 2*arr[dimensions][dimensions], monoCount);
	initSolve(dimensions, monoCount);
	string result = (sol[0][0] >0)?"Yes":"No";
	cout<< result <<endl;
	//printArray(dimensions);
	return 0;
}
