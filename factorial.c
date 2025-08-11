#include <stdio.h>

long long factorial(int);

int main(void)
{
	int n;
	do
	{
		scanf("%d" , &n);
	}while(n <= 0 || n > 20);
	printf("%lld \n" , factorial(n));
}

long long factorial(int n)
{
	if( n == 1 )
	{
		return 1;
	}
	else
	{
		return n * factorial(n-1);
	}
}
