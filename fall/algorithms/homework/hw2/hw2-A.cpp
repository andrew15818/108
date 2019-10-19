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
long int arr[MAX_SIZE][MAX_SIZE];
long int sol[MAX_SIZE][MAX_SIZE];
long int paths(long int rows, long int cols, long int curRow, long int curCol, long int mState, long int prevElement, 
				long int monoCount ,long int maxMono){
	if(curRow<0 || curRow >= rows || curCol<0 || curCol >= cols||sol[curRow][curCol]==0 ){
		return 0;
	}
	 if(sol[curRow][curCol] != -1){
		return 
	 }
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
	//printf("%lld\n", paths(dimensions, dimensions, 0, 0, 0, arr[0][0], 1, mLimit));
	//printf("the function when  mstate is set to increasing first\n");

	int result  = paths(dimensions, dimensions, 0, 0, 1, arr[0][0], 1, mLimit);
	(result == 1)?printf("Yes\n"):printf("No\n");
	for(int i =0; i<dimensions; i++){
		for(int j=0; j<dimensions; j++){
			printf("%ld ", sol[i][j]);
			if(j == dimensions-1){printf("\n");}
		}
	}
}
