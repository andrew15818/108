#include<iostream>
#include<cstdio>
using namespace std;
long long int gcd(long long int n1,long long int n2){
	if(n2==0){
		return n1;	
	}
	return gcd(n2,n1%n2);
}

int main(){
	long int n;
	cin>>n;
	long long int elements[n];

	for(long int i=0;i<n;i++){
		cin>>elements[i];	
	}
	long long int tuples=0;	
	for(long int i=0;i<n;i++){
		for(long int j=i;j<n;j++){
			
			if( gcd(elements[i],elements[j]) == 1)	{
				tuples++;			
			}
			
			//printf("gcd(%lld,%lld)= %lld\n",elements[i],elements[j],gcd(elements[i],elements[j]));
		}
	}
	printf("%lld\n",tuples);
	return 0;
}
