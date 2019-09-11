//creating a newly y-good sequence from one that is 
//x-good sequence
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
void swap(long int *n1, long int *n2){	
	//printf("Swapping: %ld, %ld\n", *n1, *n2);
	long int temp = *n1;
	*n1 = *n2;
	*n2 = temp;
}
int main(){
	int n,k,y;	
	cin>>n>>k>>y;
	long int nums[n];
	for(int i=0;i<n;i++){
		cin>>nums[i];
	}
	//sort(nums, nums+n);
	for(int i=0;i<=n-y-1;i++){

		if(nums[i] > nums[i+y] ){

			swap(&nums[i], &nums[i+y]);
		}
	}
	for(int i=0;i<n;i++){
		printf("%ld ", nums[i]);
	}
	printf("\n");
	return 0;
}

