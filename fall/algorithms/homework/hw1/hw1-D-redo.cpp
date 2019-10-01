/*still not anywhere near done, check carefully the recurrence, DC approach*/
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int counter = 0;
void pairs(long long int*, long int, long int, long int, long long int*); //prototype
long long int gcd(const long long int& n1, const long long int& n2){

	if(n2==0){
		return n1;
	}
	return gcd(n2, n1%n2);
}
long long int helper(long long int* arr, long  int n)
{
	long long int curr=0;
	for(long long int i=0;i<n;i++){
		pairs(arr,i,n-1,n,&curr);	
	}
	return curr;
}
/*Divide and Conquer, compare the result of the two different halves*/
/* this function might require just a bit of tweaking , want to try a function that 
 * actually returns an int value
void pairs(long long int* arr, long int low, long int high, long int n, long long int* curr)
{
	printf("Times entered the pairs function: %d\t",++counter);	
	long int mid1 = floor((low+high)/2), mid2 = 1+((low+high)/2);
	printf("calcing for:\t%lld \t%lld \t%lld \t%lld\n", low, mid1,mid2,  high );	

	
	if(low ==  high ){
		((low ==1 & high ==1))?(*curr++):*curr;
		return;	
	}

	if(gcd(arr[low], arr[high]) == 1){
		(*curr)+=(high-low);
		return;
	}

	pairs(arr, low, mid1, n,  curr);	
	pairs(arr, mid2, high, n, curr);	
		return;
}
*/
int main(){
	long int n;
	cin>>n;	

	long long int nums[n];
	for(long long int i=0; i<n; i++){
		cin>>nums[i];	
	}
	//long long int puta = helper(nums,n),putamierda=0;
	//cout<<puta<<endl;
	//pairs(nums, 0,n-1, n, &putamierda);
	printf("%lld\n",helper(nums,n));
	//printf("with helper: %lld, just pairs: %lld\n", puta,putamierda);
	
	//cout<<*puta<<endl;
	//helper(nums, n-1);

}
