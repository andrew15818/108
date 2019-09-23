#include<iostream>
using namespace std;
//in this approach just build the huge matrix and try
//to only have opne big matrix instead of several 
#define MAXSIZE 4096
int field[MAXSIZE][MAXSIZE] , result[MAXSIZE][MAXSIZE], input[MAXSIZE][MAXSIZE];


void init(int count){
field[0][0] = 1; field[0][1] = 1; field[1][0] = 1;
field[1][1] = -1;
	for(int i=2;i<count;i*=2){
		int lim = i;
		//check the math is correct
		for(int j=0;j<lim;j++){
			for(int k=0;k<lim;k++){
				//field[j][k] = field[j][	
				field[j][k+lim] = field[j][k];
				field[j+lim][k] = field[j][k];
				field[j+lim][k+lim] = -field[j][k];
				//result[j][k] += (input[j][k] * field[j][k]);
				//if(i==count>>1){
				//		long int intermediate = (field[]);
				//}
			}	
		}
	}
}
void print(int n){
	for(int i=0; i<n;i++){
		for(int j=0;j<n;j++){
			cout<<result[i][j]<<" ";
			if(j==n-1){cout<<endl;}
		}
	}
}
int main(){
	int n;
	cin>>n;
	init(n);
	//long int input[n][n], result[n][n];
	for(int i =0;i<n;i++){
		for(int j=0; j<n; j++){
			cin>>input[i][j];
			result[i][j] = 0;
		}
	}
	//cout<<endl;
	//bout to multiply the bad boys
	//going to loop over just half of the matrix
	int lim = n/2;
/*
	for(int i=0;i<n;i++){
		for(int j=0; j<lim;j++){
			
		}
	}
*/
	//Don't know what to fix to get it under the time limit :(	
	for(int i=0;i<lim;i++){
		for(int j=0;j<lim;j++){
			//int intermediate = 0, interDown = 0, interRight = 0, interDiag = 0; // we have to calc values under, right, and diag
			int upperLeft=0,lowerLeft=0, upperRight=0,lowerRight=0;
			//cout<<"for "<<i+lim<<","<<j<<endl;
			for(int k=0; k<lim; k++){
				upperLeft += ((field[i][k] * input[k][j]) + (field[i+lim][k] * input[k+lim][j]));	
				upperRight += ((field[i][k] * input[k][j+lim]) + (field[i][k+lim] * input[k+lim][j+lim]));
				lowerLeft +=((field[i+lim][k] * input[k][j]) + (field[i+lim][k+lim] * input[k+lim][j]) );				
				lowerRight +=((field[i+lim][k] * input[k][j+lim]) + (field[i+lim][k+lim] * input[k+lim][j+lim]));
			}		
			result[i][j] = upperLeft; 
			result[i][j+lim] = upperRight;
			result[i+lim][j] = lowerLeft;
			result[i+lim][j+lim] = lowerRight;
			if(j==n-1){cout<<endl;}
		}
	}

	print(n);
	return 0;
}

