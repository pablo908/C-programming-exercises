#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
    char frase[40];
    char apellido[12];
    char adn[22];
    char prima;
    int letras;
    float porcentaje;
}tipoadn;

int compara(const void *p , const void *q);

int main(){
    char cadena[22];
    bool ninguno = false;
    bool uno = false;
    bool varios = false;
    int casos;
    scanf("%s " , cadena);
    for( int i = 0 ; i < 22 ; i++ ){
        cadena[i] = toupper(cadena[i]);
    }
    scanf("%d " , &casos);
    tipoadn str[casos];
    for( int i = 0 ; i < casos ; i++ ){
        memset (str[i].frase, 0, 40);
        memset (str[i].apellido, 0, 12);
        memset (str[i].adn, 0, 22);
        scanf("%s" , str[i].frase);
        for( int j = 0 ; j < 40 ; j++ ){
            str[i].frase[j] = toupper(str[i].frase[j]);
        }
        int k = 0;
        for( int j = 0 ; j < 40 ; j++ ){
            str[i].apellido[k] = str[i].frase[j];
            k++;
            if(str[i].frase[j+1] == ','){
                k = j+2;
                break;
            }
        }
        for( int j = 0 ; j < 22 ; j++ ){
            str[i].adn[j] = str[i].frase[k];
            k++;
        }
        int cont = 0;
        str[i].letras = 0;
        for( int j = 0 ; j < 20 ; j++ ){
            if(cadena[j] >= 'A' && cadena[j] <= 'Z'){
                cont++;
            }
        }
        for( int j = 0 ; j < cont ; j++ ){
            if( cadena[j] == str[i].adn[j] ){
                (str[i].letras)++;
            }
        }
        str[i].porcentaje = (((float)str[i].letras)*100/((float)cont));
        str[i].prima = str[i].apellido[0];
    }
    printf("INFORMACION CANDIDATOS ORDENADOS DE MAYOR A MENOR COINCIDENCIA\n");
    printf("--------------------------------------------------------------\n");
    qsort( str , casos , sizeof(tipoadn) , &compara );
    for( int i = 0 ; i < casos ; i++ ){
        printf("%10s" , str[i].apellido);
        printf("%21s" , str[i].adn);
        printf("%3d" , str[i].letras);
        if(str[i].porcentaje < 10){
            printf("   ");
        }
        else{
            if( str[i].porcentaje > 10 && str[i].porcentaje < 100 ){
                printf("  ");
            }
            else{
                printf(" ");
            }
        }
        printf("%.2f%c\n" , str[i].porcentaje , 37 );
    }
    printf("--------------------------------------------------------------\n");
    if( str[0].porcentaje == 0 ){
        ninguno = true;
    }
    if( ninguno == false ){
        if( str[0].porcentaje == str[1].porcentaje ){
            varios = true;
        }
        else{
            uno = true;  
        }
    }
    if( ninguno == true ){
        printf("LOS ADNs DE TODOS LOS CANDIDATOS TIENEN UN 0%c DE COINCIDENCIA CON LA SECUENCIA DE ADN DE LA MUESTRA" , 37);
    }
    else{
        if( uno == true ){
            printf("SOLO %s TIENE EL PORCENTAJE DE COINCIDENCIA MAS ALTO CON LA SECUENCIA DE ADN DE LA MUESTRA = %.2f%c" , str[0].apellido , str[0].porcentaje , 37);
        }
        else{
            if( varios == true ){
                printf("LOS SIGUIENTES CANDIDATOS EN ORDEN ALFABETICO\n");
                printf("TIENEN EL PORCENTAJE DE COINCIDENCIA MAS ALTO\n");
                printf("CON LA SECUENCIA DE ADN DE LA MUESTRA = %.2f%c :\n" , str[0].porcentaje , 37);
                printf("--------------------------------------------------------------\n");
                for( int i = 0 ; i < casos ; i++ ){
                    if(str[0].porcentaje == str[i].porcentaje){
                        printf("%s\n" , str[i].apellido);
                    }
                }    
            }
        }
    }
}

int compara(const void *p , const void *q){
    if((((tipoadn *)p)->porcentaje != ((tipoadn *)q)->porcentaje)){
        return(((tipoadn *)p)->porcentaje < ((tipoadn *)q)->porcentaje);
    }
    else{
        //return(((tipoadn *)p)->apellido > ((tipoadn *)q)->apellido);
        return(strcmp(((tipoadn *)p)->apellido, ((tipoadn *)q)->apellido));
    }
}


