#include <stdio.h>

int digitos(int);

int main()
{
	int n;
	scanf("%d" , &n);
	int suma = digitos(n);
	printf("%d\n" , suma);
}

int digitos(int n)
{
	if (n < 10)
	{
		return n;
	}
	else
	{
		return (n % 10) + digitos(n/10);
	}		
}
