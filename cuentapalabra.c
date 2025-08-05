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
	printf("comensamos la función\n");
	tipocadena *array;
	int aux = 0;
	bool flag = false;
	array = (tipocadena*)malloc(sizeof(tipocadena));
	for( int i = 0 ; !feof(entrada) ; i++ ){
		printf("entro al for\n");
		while( flag == false && !feof(entrada) ){
			printf("entro al while\n");
			memset(array[i].palabra,0,41);
			fscanf(entrada,"%s",array[i].palabra);
			//for( int j = 0 ; 1 ; j++ ){
			for( int j = 0 ; j<strlen(array[i].palabra) ; j++ ){
				printf("entro al segundo for\n");
				if( isalpha(array[i].palabra[j]) != 0 ){
					printf("si\n");
					flag = true;
					array[i].palabra[j] = tolower(array[i].palabra[j]);
/*
					if( j == ((sizeof(array[i].palabra)/sizeof(char))-1) ){
						flag = true;
						printf("si\n");
						break;
					}
*/
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
		printf("entra al tercer for");
		if(strcmp(array[i].palabra,array[i+1].palabra) == 0){
			cont++;
		}
		else{
			fprintf(*salida, "%s %d\n", array[i].palabra , cont);
			cont = 1;	
		}
	}
}
   /* int cont = 0;
    char *temp;
    temp = (char*)malloc(41*sizeof(char));
    while(!feof(entrada)){
        fgets(temp,41,entrada);
        cont++;
    }
    cont--;
    free(temp);
    rewind(entrada);
    tipocadena proceso[22];
    for( int i = 0 ; i < cont ; i++ ){
        memset( proceso[i].frase , 0 , 41 );
        fgets( proceso[i].frase , 41 , entrada );
        for( int j = 0 ; j < 41 ; j++ ){
            if( isalpha(proceso[i].frase[j])  ){
                if(j == 39){
                    printf("si\n");
                }
            }
            else{
                printf("no\n");
                break;
            }
  	}
    }*/

int main(){
	printf("comensamos\n");
	FILE *f;
	FILE *p;
	printf("intentaremos abrir archivo1\n");
	f = fopen("archivoinput.txt","r");
	if(f != NULL){
		printf("se abrio archivo1\n");
		p = fopen("archivooutput.txt","w");
		if(p != NULL){
			printf("se abrio archivo2\n");
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
