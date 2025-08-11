#include <stdio.h>
#include <stdlib.h>
#define max 100

typedef struct {
    int codigo;
    int reproduccion;
}tipocancion;



int compara( const void *p , const void *q);
void encabezado();
void mostrar( tipocancion cancion[] , int numero );

int main(){
    int numero;
    tipocancion cancion[max];
    scanf( "%d" , &numero );
    for( int i = 0 ; i < numero ; i++ ){
        scanf( "%d" , &cancion[i].codigo );
        scanf( "%d" , &cancion[i].reproduccion);
    }
    qsort( cancion , numero , sizeof(tipocancion) , &compara );
    encabezado();
    /*for( int i = 0 ; i < numero ; i++ ){
        printf( "|%22d " , cancion[i].codigo );
        printf( "|%23d |\n" , cancion[i].reproduccion);
    }*/
    mostrar( cancion , numero );
    printf("|_______________________|________________________|");
}

int compara( const void *p , const void *q){
    return(((tipocancion *)p)->reproduccion < ((tipocancion *)q)->reproduccion); 
}

void encabezado(){
    printf(" _______________________ ________________________\n");
    printf("|    CODIGO CANCION     |  TOTAL REPRODUCCIONES  |\n");
    printf("|_______________________|________________________|\n");
    printf("|                       |                        |\n");
}

void mostrar( tipocancion cancion[] , int numero ){
    for( int i = 0 ; i < numero ; i++ ){
        printf( "|%22d " , cancion[i].codigo );
        printf( "|%23d |\n" , cancion[i].reproduccion);
    }
}
