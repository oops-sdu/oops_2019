#include<stdio.h>
#include<cmath>
#define PI 3.1415926
using namespace std;
int main()
{
	float y;
	y=pow(sin(PI/4),2)+(sin(PI/4))*(cos(PI/4))-pow(cos(PI/4),2);
	printf("y=sin^2(¦Ð/4)+sin£¨¦Ð/4)cos(¦Ð/4)-cos^2(¦Ð/4)=%f",y);
	return 0; 
}
