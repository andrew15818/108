#include<iostream>
using namespace std;
int min(int n1, int n2, int n3, int n4){
	int temp1 = (n1<=n2)?n1:n2;
	int temp2 = (n3<=n4)?n3:n4;
	return (temp1<=temp2)?temp1:temp2;
}
int main(){
	string s1, s2;
	int alpha, beta, gamma, delta;	
	cin>>alpha>>beta>>gamma>>delta;
	cout<<"gotem"<<endl;
	cin>>s1;
	cin>>s2;
	cout<<"s1"<<s1<<" s2"<<s2<<endl;
	int dp[s1.length()][s2.length()];
	//preprocessing
	(s1[0] == s2[0])?dp[0][0] = 0: dp[0][0] = 1;
	int length1 = s1.length(), length2 = s2.length();
	for(int i=1;i<length1;i++){
		dp[0][i] = dp[0][i-1]+1;
	}
	for(int j=1; j<length2; j++){
		dp[j][0] = dp[j-1][0]+1;
	}

	for(int i=0;i<length1;i++){
		for(int j=0;j<length2;j++){
			cout<<dp[i][j]<<" ";
			if(j==length2-1){cout<<endl;}
		}
	}
	return 0;
}
