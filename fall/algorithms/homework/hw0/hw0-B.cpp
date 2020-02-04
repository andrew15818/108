//Alice stands at (0,0) and has to figure out in what
//order to visit n cats standing at coords x,y
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
struct point{
	int x,y,id;
	int distance; //distance between Alice and cat
};
double disFormula(const point& curr){
	//double in_between = (pow((0-curr.x),2)) + pow((0-curr.y),2); 
	//return sqrt(in_between);

	return curr.x+curr.y;
}
bool compare(const point& p1, const point& p2){
	if(p1.x == p2.x && p1.y == p2.y){
		return (p1.id<p2.id);	
	}
	return (p1.distance < p2.distance); //boolean function we will use to sort values
}
int main(){
	long int n;
	cin>>n;
	point points[n+1];
	for(long int i=1; i<=n; i++){
		cin>>points[i].x>>points[i].y;
		points[i].id=i;
		points[i].distance = disFormula(points[i]);
		//printf("The distance between Alice and point %ld is: %d\n",i,points[i].distance);
	}
	sort(points+1,points+n+1,compare);
	for(long int i =1;i<=n;i++){
		printf("%d\n",points[i].id);	
	}
	return 0;
}
