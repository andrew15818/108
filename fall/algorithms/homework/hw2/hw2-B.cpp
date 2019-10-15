#include<iostream>
#include<cstdio>
using namespace std;
long long int min2(long long int n1, long long int n2)
{
	return (n1<=n2)?n1:n2;
}
long long int min(long long int n1, long long int n2, long long int n3)
{
	long long int temp = min2(n1, n2);
	return (temp<=n3)?temp:n3;
}

int main(){
	int cases,counter=0;
	cin>>cases;
	while(counter< cases){
			string s1, s2;

			int alpha, beta, gamma;	
			cin>>alpha>>beta>>gamma;
			cin>>s1>>s2;
		
			int length1 = s1.length(), length2 = s2.length(); 		
			long long int dp[length1][length2];
			dp[0][0] = (s1[0]==s2[0])?0:gamma:

			for(int come = 0; come < length1; come++){
				dp[come][0] =  	
			}

			for(int i=1;i<length1;i++){

				for(int j=1;j<length2;j++){

					if(s1[i]==s2[j]){
						dp[i][j] = dp[i-1][j-1];	
					}	
					else{
						dp[i][j] = min(dp[i-1][j-1]+alpha, dp[i][j-1]+ gamma, dp[i-1][j]+beta); //check gamma and beta	
																						//values
						//dp[i][j] = min(dp[i][j-1]+ beta, dp[i-1][j]+ gamma);
					}
				}
			}
			
		for(int hola = 0; hola< length1; hola++){
			for(int adios = 0; adios< length2; adios++){
				printf("%lld ",dp[hola][adios]);	
				if(adios == length2-1)printf("\n");
			}
		}
		
		printf("%lld\n",dp[length1-1][length2-1]);
		counter++;
	}
	return 0;
}
