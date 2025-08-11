#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int* poblar( int* cuentas , bool* flag);
void mostrar( int* collar );
int compara( const void *p , const void *q );

int main(){
    int *collar = NULL;
    int cuentas = 0;
    int aux = 0;
    int cont = 0;
    bool flag = false;
    bool simetrico = true;
    while( flag == false ){
        collar = poblar(&cuentas , &flag);
	if ( flag == true ){
		return 0;
	} 
	if ( cuentas % 2 == 0 ){
		simetrico = false;
		printf("NO\n");
	}
        qsort( collar , cuentas , sizeof(int) , &compara );
	for( int i = 0 ; i < cuentas-1 && simetrico ; i++ ){
		if( i == 0 ){
			aux = collar[i];
			cont++;
		} 
		else{
			if( collar[i] == aux ){
				cont++;
			}
			else{
				if ( cont % 2 == 0 ){
					cont = 1;
					aux = collar[i];
				}
				else{
					printf("NO\n");
					simetrico = false;
					break;
				}
			}
		}
	}
	if ( simetrico ){
		for( int i = 0 ; i < cuentas ; i += 2 ){
			printf( "%d " , collar[i] );
		}
		for( int i = cuentas-2 ; i >= 1 ; i -= 2 ){
			printf( "%d " , collar[i] );
		}
		printf("\n");
	}
        free(collar);
        cuentas = 0;
	aux = 0;
	cont = 0;
	simetrico = true;
    }
}

int* poblar( int* cuentas , bool* flag ){
    int* ptr;
    ptr = (int*)malloc(sizeof(int));
    for( int i = 0 ; 1 ; i++ ){
        scanf("%d" , &ptr[i]);
        if ( ptr[i] == 0 ){
            if ( i == 0 ){
                *flag = true;
            }
            break;
        }
        *cuentas += 1; 
        ptr = (int*)realloc( ptr , (i+2) * sizeof(int) );
    }
    return ptr;
}

int compara( const void *p , const void *q ){
    return((*(int *)p) > (*(int *)q));
}


