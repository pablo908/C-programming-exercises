#include <stdio.h>
#include <math.h>

int invertir(int , int);

int digitos(int);

int main()
{
	int n;
	int digito;
	scanf("%d" , &n);
	digito = pow(10,(digitos(n)-1));
	printf("%d" , invertir(n , digito));
}

int digitos(int n)
{
	int cont = 0;
	if ( n == 0 )
	{
		return 1;
	}
	while( n != 0 )
	{
		cont++;
		n /= 10;
	}
	return cont;
}

int invertir(int n , int digito)
{
	if( n < 10 )
	{
		return n;
	}
	else
	{
		return(n % 10) * digito + invertir((n/10) % 10 * digito/10); 
	}
}

