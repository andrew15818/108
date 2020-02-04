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
	long int nums[n],good[n];
	for(int i=0;i<n;i++){
		cin>>nums[i];
	}
	sort(nums, nums+n);

	int i = 0,count=0;
	while(count<n && i<n){
		int j = count;
		while(j<n){
			good[j] = nums[i];	
			//printf("good[%d] = nums[%d] = %ld\n",j,i,nums[i]);
			j+=y;
			i++;
		}	
		count++;
	}
	for(int i=0;i<n;i++){
		printf("%ld ", good[i]);
	}
	printf("\n");
	return 0;
}

