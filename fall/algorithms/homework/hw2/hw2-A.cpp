#include<iostream>
#include<cstdio>
#define INCREASING 0
#define DECREASING 1
#define MAX_SIZE 1000
using namespace std;
long int arr[MAX_SIZE][MAX_SIZE];
long int paths(long int rows, long int cols, long int curRow, long int curCol, long int mState, long int prevElement, 
				long int monoCount ,long int maxMono){
/*row and col nums, current row and col, whether state is increasing/decreasing previous ele in seq., max No. of mono switches*/
	//base cases
	if(curRow<0 || curRow >= rows || curCol<0 || curCol >= cols){
		return 0;
	}	
	else if(curRow == rows-1 && curCol == cols-1 && (monoCount > maxMono)){
		return 0;
	}
	else if(curRow == rows-1 && curCol == cols-1 && (monoCount <= maxMono)){
		printf("arriving with info: prevEl: %lld, monoCount: %lld\n", prevElement, monoCount);
		return 1;
	}
	//printf("still alive and well \n");
	//checking whether we change the monotone state
	if(arr[curRow][curCol] > prevElement && mState == DECREASING){
		mState = INCREASING;
		monoCount++;
	}
	else if(arr[curRow][curCol] < prevElement && mState == INCREASING){
		mState = DECREASING;
		monoCount++;
	}
	return (paths(rows, cols, curRow, curCol+1, mState, arr[curRow][curCol], monoCount, maxMono) || //item directly to the right
			paths(rows, cols, curRow+1, curCol+1, mState, arr[curRow][curCol], monoCount, maxMono) || //item diagonally left
			paths(rows, cols, curRow+1, curCol+1, mState, arr[curRow][curCol], monoCount, maxMono)	   //item to the bottom
			);
}
int main(){
	long int dimensions, mLimit;
	cin>>dimensions>>mLimit;
	for(int i =0; i<dimensions; i++){
		for(int j=0; j<dimensions; j++){
			cin>>arr[i][j];
		}
	}
	printf("%lld\n", paths(dimensions, dimensions, 0, 0, 0, arr[0][0], 0, mLimit));
}
