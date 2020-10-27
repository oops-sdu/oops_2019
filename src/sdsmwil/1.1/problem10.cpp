#include<stdio.h>
#include<cmath>
using namespace std;

int main()
{
	float y,n=3.2,m=-3.2;
	if(ceil(n)>ceil(m))
	y=ceil(n);
	else y=ceil(m);
	printf("不小于3.2、-3.2的最小整数=%d",(int)y);
	return 0;
}
