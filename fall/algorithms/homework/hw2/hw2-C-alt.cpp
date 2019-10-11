#include<iostream>
#include<algorithm>
#include<cstdio>
#include<string.h>
using namespace std;
struct doll
{
	long long int weight,value;
};

bool compare( doll d1, doll d2)
{
	return (d1.weight<=d2.weight);
}
long long int max(long long int n1, long long int n2)
{
	return (n1>=n2)?n1:n2;
}
long long int knap(long long int* best,const  doll* dolls, long long int index,
				long long int weight, long long int prevWeight)
{
	if(index<0){
		return 0;	
	}
	//printf("Now looking at : %lld\n",index);
		
	if(best[index] != -1 && prevWeight/2 > dolls[index].weight){
	//	printf("%lld already calculated, so returning %lld\n",index, best[index]);
		return best[index];
	}
		
	if(prevWeight/2 < dolls[index].weight){
		return knap(best,dolls, index-1, weight, prevWeight);	
	}
	//return max( knap(dolls,index-1, weight-dolls[index].weight, dolls[index].weight)+dolls[index].value,
	//			knap(dolls,index-1, weight, prevWeight);
	/*long long int temp = max(knap(best,dolls, index-1, weight-dolls[index].weight, dolls[index].weight )
					+dolls[index].value
	
					, knap(best, dolls, index-1, weight,prevWeight));
					*/
	long long int test1 = knap(best, dolls, index-1, weight-dolls[index].weight,dolls[index].weight)
			+dolls[index].value;
	long long int test2 = knap(best,dolls, index-1, weight, prevWeight);
	long long int temp = max(test1, test2);
	/*
	printf("for %lld %lld: if we include it: %lld \t if we dont include it: %lld\n",dolls[index].weight,
						dolls[index].value,test1, test2);	
	*/
	//printf("The best we can do for %lld is %lld\n",index, temp);
	best[index] = temp;
}
int main(){
	long long int n,k;
	cin>>n>>k;
	doll dolls[n];
	long long int best[n];
	//memset(best,n,-1);
	for(long long int i =0; i<n; i++){
		cin>>dolls[i].weight>>dolls[i].value;
		best[i] = -1;
	}
	
	sort(dolls,dolls+n,compare);
/*	
		cout<<"in sorted order"<<endl;
	for(long long int i =0; i<n; i++){
		cout<<dolls[i].weight<<" "<<dolls[i].value<<endl;	
	}
*/	
	cout<<knap(best,dolls, n-1, k, dolls[n-1].weight*2+1)<<endl;
}
