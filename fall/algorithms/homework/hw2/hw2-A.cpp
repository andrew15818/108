#include<iostream>
using namespace std;
long int arr[1000][1000];
long int sol[1000][1000];
long int max(long int n1, long int n2){
	return (n1>=n2)?n1:n2;
}
void solve(int rows, int cols, int curRow, int curCol, int state, int prevElement, int monoCount)
{
	if(curRow < 0 || curRow >= rows || curCol < 0 || curCol >= cols || monoCount <=0){
		return;
	}
	else if( sol[curRow][curCol] != -1){
		return sol[curRow][curCol];
	}
	if(state == INCREASING){
		if( arr[curRow][curCol] < prevElement){
			state = DECREASING;
			monoCount--;
		}
	}
	if(state == DECREASING){
		if( arr[curRow][curCol] > prevElement ){
			state = INCREASING;
			monoCount--;
		}
	}
	sol[curRow][curCol] = max(sol[curRow][curCol]);
	solve(rows, cols, curRow-1, curCol, state, arr[curRow][curCol], monoCount);
	solve(rows, cols, curRow, curCol-1, state, arr[CurCol][curCol], monoCount);
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
	return 0;
}
