#include<iostream>
using namespace std;
//in this approach just build the huge matrix and try
//to only have opne big matrix instead of several 
#define MAXSIZE 4096
int field[MAXSIZE][MAXSIZE];


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
			}
		}
	}
}
void print(int n){
	for(int i=0; i<n;i++){
		for(int j=0;j<n;j++){
			cout<<field[i][j]<<" ";
			if(j==n-1){cout<<endl;}
		}
	}
}
int main(){
	int n;
	cin>>n;
	init(n);
	long int input[n][n], result[n][n];
	for(int i =0;i<n;i++){
		for(int j=0; j<n; j++){
			cin>>input[i][j];
			result[i][j] = 0;
		}
	}
	//cout<<endl;
	//bout to multiply the bad boys
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			int intermediate = 0;
			for(int k=0; k<n; k++){
				intermediate += (field[i][k] * input[k][j]);
			
			}		
			result[i][j] = intermediate; 
			cout<<result[i][j]<<" ";
			if(j==n-1){cout<<endl;}
		}
	}
	//print(n);
	return 0;
}

