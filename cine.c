#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int** dimensionarSalaCine( int filas , int butacas ){
    int *ptr;
    int **arraid;
    int length;
    //ptr = (int**)malloc(sizeof(int[filas][butacas]));
    length = sizeof(int *) * filas + sizeof(int) * butacas * filas;	
    arraid = (int**)malloc(length);
    ptr = (int *)(arraid + filas);
    for(int i = 0; i < filas; i++){
	 arraid[i] = (ptr + butacas * i);
    } 
    return arraid;
}

void leerEstadoSala( int** salaCine , int filas , int butacas ){
//printf("salaCine: %d\n", (int)salaCine);
	for( int i = 0 ; i < filas ; i++ ){
		for( int j = 0 ; j < butacas ; j++ ){
			//printf("Leyendo estado fila: %d, columna: %d\n", i, j);
			scanf("%d", &(salaCine[i][j])); 
		}
	}
}

void mostrarEstadoSala( int** salaCine, int filas , int butacas ){
    printf("ESTADO DE LA SALA DE CINE\n");
    printf("BUTACAS OCUPADAS ##\n");
    printf("BUTACAS LIBRES   []\n\n");
    printf("   ----------\n");
    printf("  | PANTALLA |\n");
    printf("   ----------\n");
    for( int i = 0 ; i < filas ; i++ ){
        for( int j = 0 ; j < butacas ; j++ ){
            if ( salaCine[i][j] == 1 ){
                printf(" ## ");
            }
            else{
                printf(" [] ");
            }
        }
        printf("\n");
    }
}

bool esPosible( int** salaCine , int filas , int butacas , int totalAmig){
    int cont = 0;
    bool flag = false;
    for( int i = 0 ; i < filas ; i++ ){
        for( int j = 0 ; j < butacas ; j++ ){
            if (salaCine[i][j] == 0){
                cont++;
            }
            else{
                cont = 0;
            }
            if (cont == totalAmig){
                flag = true;
            }
        }
        cont = 0;
    }
    free(salaCine);
    return flag;
}

int main(void)
{
    int filas, butacas; 
    scanf("%d%d",&filas,&butacas);
 //printf("filas: %d, butacas: %d\n", filas, butacas);
    int **salaCine = NULL;
    //int salaCine[1][1];
//printf("salaCine: %d\n", (int)salaCine);
    salaCine = dimensionarSalaCine(filas , butacas);
//printf("salaCine: %d\n", (int)salaCine);
    if (salaCine == NULL) return 1;
    
    leerEstadoSala(salaCine,filas,butacas);
//printf("Ya lei estados\n");
    mostrarEstadoSala(salaCine,filas,butacas);
    
    int totalAmig;
    scanf("%d",&totalAmig);
    
    if (esPosible(salaCine,filas,butacas,totalAmig)) {
        printf("PAZ IR AL CINE CON TUS %d AMIG@S ES POSIBLE\n",totalAmig-1);
    }
    else {
        printf("PAZ IR AL CINE CON TUS %d AMIG@S ES IMPOSIBLE\n",totalAmig-1);
    }
    return 0;
}
