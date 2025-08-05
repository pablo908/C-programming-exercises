#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(){
    char frase[102];
    while(1){
        bool pa = true;
        int cont = 0;
        for( int i = 0 ; i < 102 ; i++ ){
            frase[i] = '0';
        }
        fgets( frase , 102 , stdin );
        if( frase[0] == 'X' && frase[1] == 'X' && frase[2] == 'X' ){
            printf("---FIN ANALISIS DE PALINDROMAS---");
            return 0;
        }
        for( int i = 0 ; i < 102 ; i++ ){
            frase[i] = tolower(frase[i]);
            if( frase[i] >= 'a' && frase[i] <= 'z' ){
                cont++;
            }
        }
        int j = 0;
        char copy[cont+1];
        char copy2[cont+1];
	//printf("%d" , cont+1);
        for( int i = 0 ; i < 102 ; i++ ){
            if( (frase[i] >= 'a' && frase[i] <= 'z') || frase[i] == '\0' ){
                copy[j] = frase[i];
                j++;
            }
            if( frase[i] == '\0' ){
                break;
            }
        }
        j = 0;
        for( int i = cont-1 ; i >= 0 ; i-- ){
            if( frase[i] != '\0' ) {
                copy2[j] = copy[i];
                j++;
            }
        }
        copy2[cont] = '\0';
        for( int i = 0 ; pa == true ; i++ ){
            if( copy[i] == copy2[i]){
                if( i == cont-1 ){
                    printf("SI\n");
                    break;
                }
            }
            else{
                printf("NO\n");
                break;
            }
        }
    }
}

