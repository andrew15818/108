#include<iostream>
#include<cstdio>
using namespace std;
long long int gcd(long long int n1,long long int n2){
	if(n2==0){
		return n1;	
	}
	return gcd(n2,n1%n2);
}

long long int tuples(long long int* arr, long long int lower, long long int upper ){
	if(upper<0 || lower<0){
		return 1;
	}
	if(upper  == lower){
		//return gcd(arr[lower], arr[upper] ); //base case
		return lower;
	}
		
	//printf("Calcing the tuples for :  %lld and %lld \n", lower, upper);
	long long int mid = lower + (upper - lower) >> 1, result = 1;	
	if( gcd(tuples(arr, lower, mid), tuples(arr, mid, upper))  == 1 ){
			return upper*lower;
	}
	return result;
}

int main(){
	long int n;
	cin>>n;
	long long int arr[n];

	for(long int i=0;i<n;i++){
		cin>>arr[i];	
	}
	//regular O(n^2) way
	for(long int i=0;i<n;i++){
		for(long int j=i;j<n;j++){
			if(gcd(arr[i],arr[j]) == 1){
				printf("(%lld,%lld)\n", arr[i], arr[j]);
			}
		}
	}
	//we have to think of a way to split the array recursively, and if the gcd is one between the pairs, 
	//then we multiply the number of elements in each pair, since it means that they all have gcd=1
	//
	tuples(arr, 0, n-1);
	return 0;
}
