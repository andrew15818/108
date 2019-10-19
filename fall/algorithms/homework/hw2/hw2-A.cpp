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
	if(curRow<0 || curRow >= rows || curCol<0 || curCol >= cols || monoCount>maxMono){
		return 0;
	}	
	//if we're at the last element and the count is greater than the max
	if(curRow == rows-1 && curCol == cols-1 && (monoCount > maxMono)){
		//printf("failed arrival with prevEl: %ld, monoCount: %ld\n", prevElement, monoCount);
		return 0;
	}
		//if we're at the last element and found a possible path
	else if(curRow == rows-1 && curCol == cols-1 && (monoCount <= maxMono)){
		//printf("arriving with info: prevEl: %ld, monoCount: %ld\n", prevElement, monoCount);
		return 1;
	}

	//checking whether we change the monotone state
	if(arr[curRow][curCol] > prevElement && mState == DECREASING){
		mState = INCREASING;
		monoCount++;
	}
	else if(arr[curRow][curCol] < prevElement && mState == INCREASING){
		mState = DECREASING;
		monoCount++;
	}

	//return the binary value for a possible path
	return (paths(rows, cols, curRow, curCol+1, mState, arr[curRow][curCol], monoCount, maxMono) || //item directly to the right
			paths(rows, cols, curRow+1, curCol, mState, arr[curRow][curCol], monoCount, maxMono)	   //item to the bottom
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
	//printf("the function when the mstate is first set to increasing\n");
	//printf("%lld\n", paths(dimensions, dimensions, 0, 0, 0, arr[0][0], 1, mLimit));
	//printf("the function when  mstate is set to increasing first\n");

	int result  = paths(dimensions, dimensions, 0, 0, 1, arr[0][0], 1, mLimit);
	(result == 1)?printf("Yes\n"):printf("No\n");
}
