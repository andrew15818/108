//Have to multiply by the matrix Hn = [Hn/2 Hn/2]
//									  [Hn/2 -Hn/2]
#include<iostream>
#include<cmath>
#define levels 13
#define max 4096
using namespace std;

int total[levels][max][max];
//building up the initial array
void init( int cuantos){
	total[0][0][0] = 1; //base case
	total[0][0][1] = 1;
	total[0][1][0] = 1;
	total[0][1][1] = -1;
	for(int i = 1;i < cuantos; i++){
		//cout<<"counting to "<<(2<<i)<<endl;
		int prev = 2 << i-1; 	
		for(int j=0;j < prev; j++){
			for(int k=0; k < prev; k++ ){
				total[i][j][k] = total[i-1][j][k];
				total[i][j + prev][k] = total[i-1][j][k];
				total[i][j][k + prev] = total[i-1][j][k];
				total[i][j + prev ][k + prev] = -total[i-1][j][k];
			}
		}	
	}
}
void print( int n){
	cout<<"The matrix for 2^"<<n<<": "<<endl;
	int lim = 2 << n-1;
	for(int i=0;i<lim;i++){
		for(int j=0;j<lim;j++){
			cout<<total[n-1][i][j]<<" ";	
			if(j==lim-1){cout<<endl;}
		}
	}
}

int main(){
	int n;
	
	int field[n][n], result[n][n];
	cout<<"about to init" <<endl;
	cin>>n;
	init(n);
	cout<<"inited!"<<endl;
	//print(n);	
	//input original matrix
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cin>>field[i][j];
			result[i][j] =0;
		}
	}
	//multiply by resulting matrix
	int trying = log(n)/log(2) - 1;
	cout<<"trying "<<trying<<endl;
	/*need to figure out the mult algorithm :(*/
	for(int a=0; a < n; a++){

		for(int b=0; b < n ;b++){
			int intermediate=0;
			cout<<" for result["<<a<<"]["<<b<<"]"<<endl <<"\t";
			for(int c=0; c < n; c++){
				intermediate += (total[n-1][a][c] * field[b][c]);
				cout<<total[n-1][a][c]<<" x "<<field[b][c]<<" = "<<intermediate<<endl;
			}
			result[a][b] = intermediate;
			//cout<<"result["<<a<<"]["<<b<<"] = "<<result[a][b]<<endl;
		}

	}

	return 0;
}
