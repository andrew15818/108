//find the number of testcases possible in a given time
//given the program takes n x floor(sqrt(n)) x floor(log2(n))
//still TLE on 3 testcases
#include<iostream>
#include<cstdio>
#include<cmath>
#define OPS 1000000000
#define PWR 1.5
#define LOGO log(2)
using namespace std;

long long int equation(const long long int& maxOps, const long long int& guess ){
	//return ((maxOps)/(guess * floor(sqrt(guess)) * floor(log(guess)/LOGO) ));
	long long int tmp  = maxOps;
	tmp/=guess;
	tmp/=floor(sqrt(guess));
	tmp/=floor(log(guess)/LOGO);
	return tmp;
}

//regular binary search on an array of size maxOps
long long int biSearch(long long int maxOps, long long int low, /*long long int mid,*/ long long int high){
		long long int mid = low+ ((high - low)>>1);		
			long long int result = equation(maxOps, mid);
			if(result > 0){ 
				//return biSearch(maxOps,mid,high);	
				long long int next = equation(maxOps,mid+1);
				//(next==0)?return mid:return biSearch(maxOps,mid,high);	
				if(next == 0){return mid;}
				return biSearch(maxOps,mid+1,high);
			}
			else if (result == 0){
				return biSearch(maxOps,low,mid);	
				//return mid;
			}
/*
			if( result > 1 &&  (equation(maxOps, mid+1) < 1)){	
				return mid;
			}
			else if( result < 1){
				return biSearch(maxOps, low,mid);
			}
			else{
				return biSearch(maxOps, mid, high);	
			}
*/
}
int main(){
	int cases;
	long long int seconds;
	cin>>cases;

	for(int i=0;i<cases;i++){	
		cin>>seconds;

		long long unsigned int maxOps = OPS * seconds;
		long long int currGuess = 100000,result =1;
		//cout<<equation(OPS*seconds,151320)<<endl;
			
		while(result>0){
			result = equation(maxOps, currGuess );	
			if(result==0){
				break;	
			}
			currGuess*=10;	
		}	
				
		printf("%lld\n", biSearch(OPS * seconds, 100000,currGuess*10));	
	}
	
	return  0;
}
