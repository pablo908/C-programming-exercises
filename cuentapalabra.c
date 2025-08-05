#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct{
    char palabra[41];
    int cont;
}tipocadena;

int compara(const void *p , const void *q){
	return( strcmp( ((tipocadena*)p)->palabra , ((tipocadena*)q)->palabra ) );
}

void mostrarPalabrasFrecuencia(FILE *entrada,FILE **salida){
	tipocadena *array;
	int aux = 0;
	bool flag = false;
	array = (tipocadena*)malloc(sizeof(tipocadena));
	for( int i = 0 ; !feof(entrada) ; i++ ){
		while( flag == false && !feof(entrada) ){
			memset(array[i].palabra,0,41);
			fscanf(entrada,"%s",array[i].palabra);
			for( int j = 0 ; j<strlen(array[i].palabra) ; j++ ){
				if( isalpha(array[i].palabra[j]) != 0 ){
					printf("si\n");
					flag = true;
					array[i].palabra[j] = tolower(array[i].palabra[j]);

				}
				else{
					flag = false;
					printf("no\n");
					break;
				}
			}
		}	 		
		array = (tipocadena*)realloc(array,sizeof(tipocadena)*(i+2));
		flag = false;
		aux = i+1;
	}
	for( int i = 0 ; i < aux ; i++ ){
		printf("%s\n",array[i].palabra);
	}
	qsort(array,aux-1,sizeof(tipocadena),&compara);
	for( int i = 0 ; i < aux ; i++ ){
                printf("%s\n",array[i].palabra);
        }
	int cont = 1;
	for( int i = 0 ; i < aux ; i++ ){
		if(strcmp(array[i].palabra,array[i+1].palabra) == 0){
			cont++;
		}
		else{
			fprintf(*salida, "%s %d\n", array[i].palabra , cont);
			cont = 1;	
		}
	}
}

int main(){
	FILE *f;
	FILE *p;
	f = fopen("archivoinput.txt","r");
	if(f != NULL){
		p = fopen("archivooutput.txt","w");
		if(p != NULL){
			mostrarPalabrasFrecuencia(f,&p);
			fclose(p);
		}
		else{
			printf("fallo en abrir archivo2\n");
		}
        	fclose(f);	
	}
	else{
		printf("fallo en abrir archivo1\n");
	}
}
