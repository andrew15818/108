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

//we want to do a binary search on the arr of the gcd and the pivot, see when
//gcd(arr[i],comp) == 1 && gcd(arr[i+1],comp) !=1 essentially,and add the remaining elements
long long int biSearch(long long int* arr, long long int comparator, long long int low,long long int high)
{	
	long long int mid = (low+high)/2;
	
	long long int result = gcd(arr[mid], comparator);
	if(high == low){
			return (result == 1)?mid: -1;
	}

	if(result == 1){
		arr[mid] = 1;
		if(mid -1 >= 0 && gcd(arr[mid-1],comparator) != 1 ){	
			return mid;	
		}	
		
		return biSearch(arr,comparator, low, mid);
	}
	else if( result > 1){
		return biSearch(arr, comparator, mid+1, high);	
	}
	return 0;
}
void solve(long long int* arr, long long int begin, long long int end, long long int* counter)
{

	if(begin == end){
		if(arr[begin] == 1){
			//printf("adding one here\n");
			(*counter)++;	
		}	
		return ;
	}

	long long int mid = (begin+ end)/2;



	//divide step 
	solve(arr,begin,mid,counter);
	solve(arr,mid+1,end,counter);

	//conquer step
	long long int temp[end + 1 - mid], temp_counter=0;
	temp[temp_counter] = gcd(arr[mid], arr[mid+1]);

	//setting up the array we will use for biSearch 
	for(long int i = mid + 2; i<=end; i++ ){
		temp_counter++;
		temp[temp_counter] = gcd(arr[i],temp[temp_counter-1]);	

	}
	for(long long int i=mid; i>=begin; i--){
		long long int result = biSearch(temp, arr[i], 0, end-mid );	
		if(result != -1){
			*counter+=( end - (mid+result+1) + 1  );	
		}

	}

}
int main(){
	long int n;
	cin>>n;
	long long int arr[n];
	for(long int i=0;i<n;i++){
		cin>>arr[i];	
	}
	long long int counter=0;
	solve(arr,0,n-1,&counter);
	printf("%lld\n", counter);
}

