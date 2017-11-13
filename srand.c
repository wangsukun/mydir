#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
 int i = 0;
 srand(time(0));
 for(; i < 10; i ++)
	printf("%4d\n",rand()%1000+2000);
 return 0;
}

