#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

int main(void){
    char frase[22];
    char copy[22];
    char caso[12];
    while(1){
        bool camel = false;
        bool snake = false;
        bool kebab = false;
        scanf("%s" , frase);
        if( strcmp(frase,"FIN") == 0 ){
            return 0;
        }
        scanf("%s" , caso);
        if( frase[0] >= 'A' && frase[0] <= 'Z'){
            camel = true;
        }
        else{
            for( int i = 0 ; 1 ; i++ ){
                if( frase[i] == '_' ){
                    snake = true;
                    break;
                }
                if( frase[i] == '-' ){
                    kebab = true;
                    break;
                }
            }
        }
        if( strcmp(caso,"snake_case") == 0 ){
            if( snake == true ){
                printf("%s" , frase);
            if( kebab == true ){
                for( int i = 0 ; frase[i] != '\0' ; i++ ){
                    if( frase[i] == '-' ){
                        frase[i] = '_';
                    }
                }
                printf("%s" , frase);
            }
            if( camel == true ){
                int j = 0;
                for( int i = 0 ; i < 22 ; i++ ){
                    if( frase[i] >= 'a' && frase[i] <= 'z' ){
                        copy[j] = frase[i];
                        j++;
                    }
                    if( frase[i] >= 'A' && frase[i] <= 'Z' ){
                        if( i != 0 )
                        {
                            copy[j] = '_';
                            j++;
                            copy[j] = frase[i];
                            j++;
                        }
                        else{
                            copy[j] = frase[i];
                            j++;
                        }
                    }
                    if( frase[i] == '\0' ){
                        copy[j] = frase[i];
                        j++;
                    }
                }
                printf("%s" , copy);
            }
            
        }
        else{
            if( strcmp(caso,"kebab-case") == 0 ){
                if( snake == true ){
                    for( int i = 0 ; frase[i] != '\0' ; i++ ){
                        if( frase[i] == '_' ){
                            frase[i] = '-';
                        }
                    }
                    printf("%s" , frase);
                }
                if( kebab == true ){
                    printf("%s" , frase);
                }
                if( camel == true ){
                    int j = 0;
                    for( int i = 0 ; i < 22 ; i++ ){
                        if( frase[i] >= 'a' && frase[i] <= 'z' ){
                            copy[j] = frase[i];
                            j++;
                        }
                        if( frase[i] >= 'A' && frase[i] <= 'Z' ){
                            if( i != 0 )
                            {
                                copy[j] = '-';
                                j++;
                                copy[j] = frase[i];
                                j++;
                            }
                            else{
                                copy[j] = frase[i];
                                j++;
                            }
                        }
                        if( frase[i] == '\0' ){
                            copy[j] = frase[i];
                            j++;
                        }
                    }
                    printf("%s" , copy);
                }
            }
            else{
                if( snake == true || kebab == true ){
                    if( snake == true ){
                        frase[0] = toupper(frase[0]);
                        for( int i = 0 ; 1 ; i++ ){
                            if( frase[i] == '\0'){
                                break;
                            }
                            else{
                                if( frase[i] == '_' ){
                                    frase[i+1] = toupper(frase[i+1]);
                                }
                            }
                        }
                        int j = 0;
                        for( int i = 0 ; i < 22 ; i++ ){
                            if( frase[i] >= 'a' && frase[i] <= 'z' ){
                                copy[j] = frase[i];
                                j++;
                            }
                            if( frase[i] >= 'A' && frase[i] <= 'Z' ){
                                copy[j] = frase[i];
                                j++;
                            }
                            if( frase[i] == '\0' ){
                                copy[j] = frase[i];
                                j++;
                            }
                        }
                        printf("%s " , copy);
                    }
                    else{
                        frase[0] = toupper(frase[0]);
                        for( int i = 0 ; 1 ; i++ ){
                            if( frase[i] == '\0'){
                                break;
                            }
                            else{
                                if( frase[i] == '-' ){
                                    frase[i+1] = toupper(frase[i+1]);
                                }
                            }
                        }
                        int j = 0;
                        for( int i = 0 ; i < 22 ; i++ ){
                            if( frase[i] >= 'a' && frase[i] <= 'z' ){
                                copy[j] = frase[i];
                                j++;
                            }
                            if( frase[i] >= 'A' && frase[i] <= 'Z' ){
                                copy[j] = frase[i];
                                j++;
                            }
                            if( frase[i] == '\0' ){
                                copy[j] = frase[i];
                                j++;
                            }
                        }
                        printf("%s " , copy);
                    }
                }
                if(camel == true){
                    printf("%s " , frase);
                }
            }
        }
        printf("%s " , frase);
        printf("%s\n" , caso);
    }
return 0;
}
