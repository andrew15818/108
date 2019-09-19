//find the number of testcases possible in a given time
//given the program takes n x floor(sqrt(n)) x floor(log2(n))
#include<iostream>
#include<cstdio>
#include<cmath>
#define OPS 1000000000
#define PWR 1.5
using namespace std;
//Let's see if this is equivalent to the membership problem? 
double equation(const long long int& maxOps, const long long int& guess ){
	//return ((n*OPS) / (guess*pow(guess,PWR )*(log(guess)/log(2))));
	return ((maxOps) / ( floor(pow(guess, PWR)) * floor((log(guess) / log(2)))));
}
long long int biSearch(long long int maxOps, long long int low, /*long long int mid,*/ long long int high){
		long long int mid = low+ ((high - low)/2);		
			double result = equation(maxOps, mid);
			printf("low %lld\t mid: %lld,\t high:%lld,\t result is %f \n ", low, mid,high, result);
			if( result < 1 &&  (equation(maxOps, mid+1) >1)){
				return mid;
			}
			else if( result <1){
				return biSearch(maxOps, low,mid);
			}
			else{
				return biSearch(maxOps, mid, high);	
			}
		//}
		return 1;
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
			long long int result = equation(maxOps, currGuess );	
			if(result<=1){
				cout<<"We're breaking at "<<currGuess<<endl;
				break;	
			}
			cout<<result<<"and the guess is "<<currGuess<<endl;
			currGuess*=10;	
		}	
		cout<<currGuess<<" is the guesserino"<<endl;
		//biSearch(maxOps, 0, currGuess*10);
		printf("%f \t %f\n", equation(maxOps, 151320), equation(maxOps, 151321));
/*
		bool found = false;
		long long int low = currGuess/10, mid, high = currGuess, finalito = 0;
		while(!found){
			mid =  low + floor((high - low )/2);
			double current = equation(maxOps, mid);
			
			if( equation(maxOps, mid ) >= 1 current  >=1 && equation(maxOps, current + 1) <= 1){
				finalito = mid;
				found = true;
				break;
				//low = mid;
				//mid = floor((high - low)/2);
				
			} 
			//desired number is higher
			else if(current  <= 1){
				high = mid;
			}
			//desired number is lower
			else if (current >= 1){
				low = mid;
			}
		}
*/
		
	}
	return  0;
}
