#include<iostream>
#include<cstdio>
using namespace std;
long long int min(long long int n1, long long int n2, long long int n3){
	long long int temp = (n1<=n2)?n1:n2;
	return (temp<=n3)?temp:n3;
}
int main(){
	int cases, counter=0;
	cin>>cases;
	while(counter<cases){
		int insertion, deletion, substitution;
		string s1, s2;
		cin>>insertion>>deletion>>substitution;
		cin>>s1>>s2;
		int s1length = s1.length(), s2length = s2.length();
		long long int dp[s1length][s2length];
	
		//dp[0][0] = (s1[0] == s2[0])?0:substitution;
		dp[0][0] = 0 ;
		for(int i=1;i<s1length;i++){
			dp[i][0] = dp[i-1][0] + deletion;
		}
		for(int j=1; j<s2length; j++){
			dp[0][j] = dp[0][j-1] + insertion;
		}
		for(int i=1; i<s1length; i++){
			for(int j=1; j<s2length; j++){
				if(s1[i] == s2[j]){
					dp[i][j] = dp[i-1][j-1];
				}	
				else{
					dp[i][j] = min(dp[i-1][j-1]+substitution, dp[i-1][j]+deletion, dp[i][j-1]+insertion); //check for correct procedure
				}


			}
		}
		printf("%lld\n", dp[s1length-1][s2length-1]);
		counter++;
	}
	return 0;
}
