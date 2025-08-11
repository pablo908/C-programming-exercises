#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int* poblar( int* cuentas , bool* flag);
void mostrar( int* collar );
int compara( const void *p , const void *q );

int main(){
    int *collar = NULL;
    int *copy = NULL;
    int cuentas = 0;
    int mitad;
    int aux = 0;
    int cont = 0;
    bool flag = false;
    while( flag == false ){
        collar = poblar(&cuentas , &flag);
	if ( cuentas % 2 == 0 ){
		mitad = cuentas/2;
	}
	else{
		mitad = ((cuentas/2) + 1);
	}
	copy = (int*)malloc(sizeof(int) * (mitad));
        qsort( collar , cuentas , sizeof(int) , &compara );
	for( int i = 0 ; i < cuentas ; i++ ){
		if( collar[i] == collar[i+1] ){
			cont++;
		}
		else{
			for( int j = aux ; j < mitad ; j++ ){
				copy[i] = collar[i]; 
			}
			aux += cont;
			cont = 0;
		}
	}
	for( int i = 0 ; i < mitad ; i++ ){
            collar[i] = copy[i];
        }
	cont = 1;
	int cont2 = 0;
	if( cuentas % 2 == 0 ){
		for( int i = mitad ; i < cuentas ; i++ ){
                        collar[mitad-1+cont] = collar[mitad-1-cont2];
                        cont++;
			cont2++;
                }
	}
	else{
		for( int i = mitad ; i < cuentas ; i++ ){
            		collar[mitad-1+cont] = collar[mitad-1-cont];
			cont++; 
        	}
	}
	cont = 1;
	cont2 = 0;
	if (cuentas % 2 == 0){
		for( int i = 0 ; i < cuentas ; i++ ){
			if(collar[mitad-1+cont] != collar[mitad-1-cont2]){
				printf("NO");
			}
			 else{
                                if( i == cuentas-1 ){
                                        for( int i = 0 ; i < cuentas ; i++ ){
                                                printf( "%d " , collar[i]);
                                        }

                                }
                        }

        	}
	}
	else{
		for( int i = 0 ; i < cuentas ; i++ ){
			if(collar[mitad-1+cont] != collar[mitad-1-cont]){
				printf("NO");
			}
			else{
				if( i == cuentas-1 ){
					for( int i = 0 ; i < cuentas ; i++ ){
            					printf( "%d " , collar[i]);
        				}

				}
			}
                }
	}
        /*for( int i = 0 ; i < cuentas ; i++ ){
            printf( "%d " , collar[i]);
        }*/
        printf("\n");
	for( int i = 0 ; i < mitad ; i++ ){
            printf( "%d " , copy[i]);
        }
	free(copy);
        free(collar);
        cuentas = 0;
	aux = 0;
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
    return((*(int *)p) < (*(int *)q));
}


