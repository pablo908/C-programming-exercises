#include "SortedMap.h"
#include "Sources.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *get_csv_field (char * tmp, int k) {
    //se crea una copia del string tmp

    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }


    return NULL;
}

void show_app_menu(){
    printf("1- Ingresar una lista de peliculas\n");
    printf("2- Ver listas de peliculas en orden alfabetico\n");
    printf("3- Ver peliculas de una lista ordenadas por rating\n");
    printf("4- Ver informacion de un pelicula\n");
    printf("5- Marcar como favorita una pelicula\n");
    printf("6- Solicitar recomendaciones\n");
    printf("X- Si se ingresa otro caracter se finalizara la ejecucion del programa\n");
    printf("\n");
}

int id_cmp(const void*key1,const void*key2){
    const double *Key1 = key1;
    const double *Key2 = key2;
    if(*Key1 > *Key2){
     return -1;
    }else if(*Key1 < *Key2){
     return 1;
    }else{
     return 0;
    }
}

int key_cmp(const void*key1,const void*key2){
    const char *Key1 = key1;
    const char *Key2 = key2;
    if(strcmp(Key1 , Key2) < 0){
     return -1;
    }else if(strcmp(Key1 , Key2) > 0){
     return 1;
    }else{
     return 0;
    }
}

void opcionX(){
    printf("Gracias por usar la app.\n");
}

void opcion6(SortedMap *files_map, SortedMap *movies_map, movie *aux_movie){
    int maximum = -1;
    int cont = 0;
    SortedMap *maximum_map = NULL;
    movies_map = firstSortedMap(files_map);
    while(movies_map){
        aux_movie = firstSortedMap(movies_map);
        if(maximum < aux_movie->list_points){
            maximum_map = movies_map;
            maximum = aux_movie->list_points;
        }
        movies_map = nextSortedMap(files_map);
    }
    aux_movie = firstSortedMap(maximum_map);
    while(aux_movie){
        if(!aux_movie->fav){
            printf("%s\n", aux_movie->title);
            cont++;
        }
        if(cont > 10){
            break;
        }
        aux_movie = nextSortedMap(maximum_map);
    }
    getchar();
}

void opcion5(SortedMap *files_map, SortedMap *movies_map, movie *aux_movie){
    char id2[20];
    scanf("%s",id2);
    movies_map = firstSortedMap(files_map);
        while(movies_map)
        {
            aux_movie = firstSortedMap(movies_map);
            while(aux_movie)
            {
                if(!strcmp(aux_movie->id, id2))
                {
                    aux_movie->fav = 1;
                    aux_movie = firstSortedMap(movies_map);
                    (aux_movie->list_points)++;
                    break;
                }
                aux_movie = nextSortedMap(movies_map);
            }
            movies_map = nextSortedMap(files_map);
        }
    getchar();
}

void opcion4(SortedMap *files_map, SortedMap *movies_map, movie *aux_movie){
    int escrita = 0;
    char id[20];
    scanf("%s",id);
    movies_map = firstSortedMap(files_map);
    char* name = currentSortedMapKey(files_map);
    while(movies_map)
        {
            aux_movie = firstSortedMap(movies_map);
            while(aux_movie)
            {
                if(!strcmp(aux_movie->id, id))
                {
                      if(!escrita)
                      {
                        printf("Datos id %s:\n" , aux_movie->id);
                        printf("%s\n" , aux_movie->title);
                        printf("%d\n", aux_movie->year);
                        printf("%s\n", aux_movie->director);
                        printf("%lf\n", aux_movie->rating);
                        printf("%s\n", aux_movie->genres);

                        printf("\nlistas: \n");
                        escrita = 1;
                      }

                      printf("%s\n",name);

                      break;
                }
                aux_movie = nextSortedMap(movies_map);
            }
            movies_map = nextSortedMap(files_map);
            name = currentSortedMapKey(files_map);
        }
        getchar();
}

void opcion3(char* lista, movie *aux_movie, SortedMap *found, SortedMap *files_map){
    scanf("%s",lista);
    found = searchSortedMap(files_map,lista);
    aux_movie = firstSortedMap(found);
    while(aux_movie){
        printf("%s: " , aux_movie->id);
        printf("%lf\n", aux_movie->rating);
        aux_movie = nextSortedMap(found);
    }
    getchar();
}

void opcion2(char *files_map_key, SortedMap *files_map){
    files_map_key = firstSortedMapKey(files_map);
    while(files_map_key){
        printf("%s\n", files_map_key);
        files_map_key = nextSortedMapKey(files_map);
    }
    getchar();
}

void opcion1(FILE *parch, SortedMap *movies_map, SortedMap *files_map, char *archivo, int i, char *linea, char (*field)[1024]){
    movies_map = createSortedMap(id_cmp);
    printf("Ingrese el nombre de la lista .csv que desea ingresar\n");
    archivo = (char*)malloc(sizeof(char)*100);
    scanf("%s",archivo);
    if ((parch = fopen(archivo,"r")) != NULL) {
        printf("Leyendo el archivo: %s\n\n",archivo);
        fgets (linea, 1023, parch);
        for(i=0;i<13;i++){
            const char *aux = get_csv_field(linea, i); // Se obtiene el nombre
            strcpy(field[i], aux);
        }
        while (fgets (linea, 1023, parch) != NULL) { // Se lee la linea
            movie* pelicula = (movie*)malloc(sizeof(movie));
            pelicula->fav = 0;
            pelicula->list_points = 0;
            printf("\n");
            for(i=0;i<15;i++){
                const char *aux = get_csv_field(linea, i); // Se obtiene el nombre
                printf("%s: %s\n",field[i], aux);
                switch(i){
                    case 0:
                        pelicula->position = atoi(aux);
                        break;
                    case 1:
                        strcpy(pelicula->id,aux);
                        break;
                    case 2:
                        strcpy(pelicula->created,aux);
                        break;
                    case 3:
                        strcpy(pelicula->modified,aux);
                        break;
                    case 4:
                        strcpy(pelicula->description,aux);
                        break;
                    case 5:
                        strcpy(pelicula->title,aux);
                        break;
                    case 6:
                        strcpy(pelicula->url,aux);
                        break;
                    case 7:
                        strcpy(pelicula->title_type,aux);
                        break;
                    case 8:
                        pelicula->rating = atof(aux);
                        break;
                    case 9:
                        pelicula->runtime = atoi(aux);
                        break;
                    case 10:
                        pelicula->year = atoi(aux);
                        break;
                    case 11:
                        strcpy(pelicula->genres,aux);
                        break;
                    case 12:
                        pelicula->num_votes = atoi(aux);
                        break;
                    case 13:
                        strcpy(pelicula->relase_date,aux);
                        break;
                    default:
                        strcpy(pelicula->director,aux);
                        break;
                }
            }
            insertSortedMap(movies_map,&pelicula->rating,pelicula);
        }
    }
    insertSortedMap(files_map,archivo,movies_map);
    getchar();
}

