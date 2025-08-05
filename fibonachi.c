#include <stdio.h>

int fibonacci(int);

int main(void)
{
	int n;
	scanf("%d" , &n);
	printf("%d" , fibonacci(n));
}

int fibonacci(int n)
{
	if( n ==  1 )
	{
		return 1;
	}
	if( n == 0 )
	{
		return 0;
	}
	else
	{
		return fibonacci(n-1) + fibonacci(n-2);  
	}
}


