#include<stdio.h>
#include<cmath>
using namespace std;
int main()
{
	float y,m=3.8,n=-3.8;
	if(floor(m)<floor(n))
	y=floor(m);
	else y=floor(n);
	printf("y=等于不大于3.8或-3.8的最大整数=%d",(int)y);
	return 0;
	
	
	
}
