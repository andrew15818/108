#include<iostream>
#define INCREASING 0
#define DECREASING 1
using namespace std;
long int arr[1000][1000];
long int sol[1000][1000];
long int max(long int n1, long int n2){
	return (n1>=n2)?n1:n2;
}
int solve(int rows, int cols, int curRow, int curCol, int state, int prevNum, int monoCount){
	if(curRow<0 || curRow>=rows || curCol<0 || curCol>=cols || monoCount<=0){
		return 0;
	}
	
	if(sol[curRow][curCol] != -1){
		return sol[curRow][curCol];
	}
	//cout<<"calling "<<curRow<<" "<<curCol<<" with mono "<<monoCount<<endl;
	if(state == INCREASING){
		//monoCount=(arr[curRow][curCol]>prevNum)?monoCount:monoCount--;	
		if(arr[curRow][curCol] < prevNum){
			state = DECREASING;	
			monoCount--;
		}
	}
	if(state == DECREASING){
		//monoCount=(arr[curRow][curCol]<prevNum)?monoCount:monoCount--;
		if(arr[curRow][curCol] > prevNum){
			monoCount--;
			state = INCREASING;
		}
	}

	sol[curRow][curCol] = monoCount; 
	if(monoCount<0){
		return 0;
	}
	//sol[curRow][curCol] = monoCount; 
	if(curRow == rows-1 && curCol == cols-1 && monoCount>0){
		//cout<<"reached the end successfully with count "<<monoCount<<endl;
		return 1;
	}
	else if(curRow == rows-1 && curCol == cols-1 && monoCount<=0){
		//cout<<"reached the end unsuccesfullly"<<endl;
		return 0;
	}
	/*
	return (solve(rows, cols, curRow,curCol+1, state, arr[curRow][curCol], monoCount )
			 ||  solve(rows, cols, curRow+1, curCol, state, arr[curRow][curCol], monoCount)
			);
*/

	return max(
			solve(rows, cols, curRow+1, curCol, state, arr[curRow][curCol], monoCount),
			solve(rows, cols, curRow, curCol+1, state, arr[curRow][curCol], monoCount)
			);

}
void printArray(int dimensions){
		for(int i=0;i<dimensions;i++){
			for(int j=0; j<dimensions; j++){
				cout<<sol[i][j]<<" ";
				if(j==dimensions-1){cout<<endl;}
			}
		}
}
int init(int rows, int cols, int monoCount)
{
	int state1 = (arr[0][1]>arr[0][0])?INCREASING:DECREASING;
	int state2 = (arr[1][0]> arr[0][0])?INCREASING:DECREASING;
	//return solve(rows, cols, 0, 0, DECREASING, arr[0][0], monoCount);
	return (solve(rows, cols, 0,1,state1, arr[0][0], monoCount)||
			solve(rows, cols, 1,0, state2, arr[0][0], monoCount));
}

int main(){
	int dimensions, maxSwitch;	
	cin>>dimensions>>maxSwitch;

	for(int i =0; i<dimensions;i++){
		for(int j=0; j<dimensions; j++){
			cin>>arr[i][j];
			sol[i][j] = -1;
		}
	}
	if(dimensions ==1){
		cout<<"Yes"<<endl;
		return 0;
	}	

	init(dimensions, dimensions, maxSwitch);
	string result = (sol[dimensions-1][dimensions-1]==0)?"No":"Yes";
	cout<<result<<endl;
	//cout<<"result "<<result<<endl;
	//printArray(dimensions);
	return 0;
}
