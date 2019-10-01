/*still not anywhere near done, check carefully the recurrence, DC approach*/
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
long long int pairs(long long int*, long int, long int, long int, long long int*); //prototype
long long int gcd(const long long int& n1, const long long int& n2){
	/*	if((n1>n2) && (n1%n2)==0){
			return n2;
		}
		return gcd(n2, n1%n2);
	*/

	if(n2==0){
		//cout<<"the gcd is "<<n1<<endl;
		return n1;
	}
	return gcd(n2, n1%n2);

}
/*my attempt this time: 
 * we calculate the gcd of the left and right sides recursively,
 * if gcd(left, right)==1, we know all pairs starting at left will be 1, so we just add it
 * to our running total*/
/*What do I need to fix TODO:
 * 1. make the recursion work, this is mostly to do with indeces i think
 * 2. Figure out if indeed my approach works :'(*/

long long int helper(long long int* arr, long  int n)
{
	long long int* curr=0;
	printf("%lld\n",pairs(arr, 1, n, n, curr));
	return *curr;
}
long long int pairs(long long int* arr, long int low, long int high, long int n, long long int* curr)
{

	long int mid1 = floor((low+high)/2), mid2 = 1+((low+high)/2);
	printf("calcing for:\t%lld \t%lld \t%lld \t%lld\n", low, mid1,mid2,  high );	
	//printf("calcing for:\t%lld \t%lld \t%lld\n", arr[low], arr[mid], arr[high]);	

	
	if(low ==  high ){
		return arr[low];
	}

	pairs(arr, low, mid1, n,  curr);	
	pairs(arr, mid2, high, n, curr);
	
	if(gcd(arr[low], arr[high]) == 1){
		*curr+=(n-low );
	}
	return 0;
}
int main(){
	long int n;
	cin>>n;	

	long long int nums[n];
	for(long long int i=0; i<n; i++){
		cin>>nums[i];	
	}
	long long int puta = 0;
	pairs(nums, 0,n-1, n, &puta);
	printf("%lld\n", puta-1);
	//cout<<*puta<<endl;
	//helper(nums, n-1);
	return 0;
}
