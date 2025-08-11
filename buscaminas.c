#include <stdio.h>
#include <stdbool.h>
#define maxc 100
#define maxf 100

int main()
{
    int n;
    int m;
    int cont = 0;
    while(n != 0 && m != 0);
    {
        scanf("%d" , &n);
        scanf("%d" , &m);
        char A[maxf][maxc];
        for( int i = 0 ; i <= n ; i++ )
        {
            for( int j = 0 ; j < m ; j++ )
            {
                scanf("%c" , &A[i][j]);
            }
        }
        for( int i = 0 ; i <= n ; i++ )
        {
            for( int j = 0 ; j < m ; j++ )
            {
                printf("%c" , A[i][j]);
            }
        }
        for( int i = 1 ; i < n ; i++ )
        {
            for( int j = 1 ; j < m-1 ; j++ )
            {
		if ( A[i][j] == '-' )
		{
                	if( A[i-1][j] == '*' )
                	{
                    		cont++;
                	}
                	if( A[i+1][j] == '*' )
                	{
                   		cont++;
                	}
                	if( A[i][j-1] == '*' )
                	{
                      		cont++;
                	}
                	if( A[i][j+1] == '*' )
                	{
                    	cont++;
                	}
                	if( A[i-1][j-1] == '*' )
                	{
                   	cont++;
                	}
                	if( A[i-1][j+1] == '*' )
                	{
                   	cont++;
                	}
			if( A[i+1][j+1] == '*' )
                	{
                   	cont++;
                	}
			if( A[i+1][j-1] == '*' )
                	{
                   	cont++;
                	}
		}
            }
        }
    }
}
