#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
long long int gcd(const long long int& n1, const long long int& n2)
{
	if(n2==0){
		return n1;
	}
	return gcd(n2, n1%n2);
}
/*I think this approach will be too slow and I misunderstood the TAs advice :'(*/
void pairs(long long int* arr, long long int tail, long long int head, long long int* counter, long long int size)
{
	//printf("entering the function for :%lld\t %lld\t \n", tail, head);
	long long int mid = floor((tail + head)>>1);	
	//initial setup
	if(head==tail){
		(gcd(arr[head], arr[tail])==1)?(*counter++):*counter;
		return;
	}
	else if(head-1 ==  tail){
		(gcd(arr[head], arr[tail])==1)?(*counter++):*counter;
		//printf("doig\n");
		return;
	}
	
	for(long long int i= mid+1; i<=head;i++){
		if(gcd(arr[mid],arr[i]) == 1 ){
			//printf("(%lld ... %lld): adding %lld\n",arr[mid], arr[i], 1);
			(*counter)++;
		}
	}
	
	for(long long int j = mid;j>=tail;j--){
		if(gcd(arr[j], arr[mid]) ==1 ){
			//printf("(%lld...%lld): adding %lld\n", arr[j], arr[mid], head-mid);
			(*counter)+=(head-mid+1);
		}	
	}
		
	pairs(arr, tail, mid,counter, size );	
	pairs(arr, mid, head,counter ,size);
}
int main(){

	long long int n;
	cin>>n;	
	long long int arr[n];
	for(long long int  i=0;i<n;i++){
		cin>>arr[i];
	}
	long long int counterino=0;
	pairs(arr, 0, n-1, &counterino, n);
	cout<<counterino<<endl;
	return 0;
}
