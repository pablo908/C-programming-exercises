#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

typedef struct{
    char tweet[282];
    int cont;
}tipohashtag;

int compara(const void *p , const void *q){
	return( strcmp( ((tipohashtag*)p)->tweet , ((tipohashtag*)q)->tweet ) );
}

/*void trendingTopic(FILE *entrada){
	tipohashtag *array;
	int tamano = 0;
	bool gato = false;
	array = (tipohashtag*)malloc(sizeof(tipohashtag));
	for( int i = 0 ; !feof(entrada) ; i++ ){
		while( !feof(entrada) && gato == false ){
			memset(array[i].tweet,0,282);
			fscanf(entrada,"%s",array[i].tweet);
			if( array[i].tweet[0] == '#' ){
				gato = true;
			}	
		}
		array = (tipohashtag*)realloc(array,sizeof(tipohashtag)*(i+2));
		gato = false;
		tamano++;
	}
	for( int i = 0 ; i < tamano ; i++ ){
		printf("%s" , array[i].tweet);
	}
	
}*/

void trendingTopic(FILE *entrada){
        int tamano = 0;
        tipohashtag *array;
        array = (tipohashtag*)malloc(sizeof(tipohashtag));
        for( int i = 0 ; !feof(entrada) ; i++ ){
                fscanf(entrada,"%s",array[i].tweet);
                tamano++;
                array = (tipohashtag*)realloc(array,sizeof(tipohashtag)*(i+2));
        }
        qsort( array , tamano-1 , sizeof(tipohashtag) , &compara );
        int contar = 1;
        for( int i = 0 ; i < tamano-1 ; i++ ){
                if( strcmp (array[i].tweet , array[i+1].tweet) == 0 ){
                        contar++;
                        array[i].tweet[0] = '0';
                }
                else{
                        array[i].cont = contar;
                        contar = 1;
                }
        }
        for( int i = 0 ; i < tamano-1 ; i++ ){
                if( array[i].tweet[0] != '0' ){
                        printf("%10d | " , array[i].cont);
                        printf("%s\n" , array[i].tweet);
                }
        }
}


int main(){
	FILE *f;
	fopen("hashtag.txt","r");
	if( f != NULL ){
		trendingTopic(f);
		fclose(f);
	}
}
