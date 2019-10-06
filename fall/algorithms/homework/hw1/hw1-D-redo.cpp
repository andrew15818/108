#include<iostream>
#include<cstdio>
using namespace std;
long long int gcd(long long int n1, long long int n2)
{
	if(n2==0){
		return n1;
	}
	return gcd(n2, n1%n2);
}
void helper(long long int* arr, long long int start, long long int end)
{
		if(start == end){
			return arr[start];
		}
		long long int mid = (start+end)>>1;
		helper(arr, start, mid);
		helper(arr, mid+1, end);
		//pairs();
	
}
void tuples(long long int* arr, long long int start, long long int end, long long int* counter)
{
	if(start== (end-1) ){
		(gcd(arr[start], arr[end])==1)?(*counter)++:counter;
		return;
	}

	long long int mid = 1+((start+end)>>1);
	if(gcd( tuples(arr, start, mid), tuples(arr, mid+1, end)) ==1){
					
	}
}
int main(){
	long long int n;
	cin>>n;
	long long int arr[n];

	for(long long int i=0; i<n; i++){
		cin>>arr[i];		
	}
	return 0;
}
