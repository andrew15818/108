#include<iostream>
#include<string>
//should we make the hash table that big?
#define MAX_SIZE 10000
using namespace std;
//should we just do a regular hash table with linked lists for
//every scope?
struct Type{
	
};
int hash(const string& input)
{
	unsigned int returnValue = 0;
	for(int i =0; i < input.size(); i++)
	{
		returnValue ^= (returnValue<<5)+(returnValue>>2)+input[i];			
	}
	returnValue%=MAX_SIZE;
	return returnValue;
}
class Table{
		
};
int main(){

}
