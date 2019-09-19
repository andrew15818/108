//find the number of testcases possible in a given time
//given the program takes n x floor(sqrt(n)) x floor(log2(n))
//still TLE on 3 testcases
#include<iostream>
#include<cstdio>
#include<cmath>
#define OPS 1000000000
#define PWR 1.5
using namespace std;
//Let's see if this is equivalent to the membership problem? 
double equation(const long long int& maxOps, const long long int& guess ){
	return ((maxOps)/(guess * floor(sqrt(guess)) * floor(log(guess)/log(2)) ));
}
long long int biSearch(long long int maxOps, long long int low, /*long long int mid,*/ long long int high){
		long long int mid = low+ ((high - low)/2);		
			double result = equation(maxOps, mid);
			if( result > 1 &&  (equation(maxOps, mid+1) < 1)){
				return mid;
			}
			else if( result < 1){
				return biSearch(maxOps, low,mid);
			}
			else{
				return biSearch(maxOps, mid, high);	
			}
}
int main(){
	int cases;
	long long int seconds;
	cin>>cases;

	for(int i=0;i<cases;i++){	
		cin>>seconds;
		long long unsigned int maxOps = OPS * seconds;
		long long int currGuess = 10;
		while(1){
			currGuess*=10;
			long long int result = equation(maxOps, currGuess );	
			if(result<=1){

				break;	
			}	
		}	
		//cout<<biSearch(maxOps, 0, currGuess*10)<<endl;
		printf("%lld\n", biSearch(maxOps, 0, currGuess*10));	
	}
	return  0;
}
