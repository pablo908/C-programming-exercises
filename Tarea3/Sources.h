#ifndef SOURCES_H_INCLUDED
#define SOURCES_H_INCLUDED

#include<stdio.h>

typedef struct{
    int position;
    char id[12];
    char created[12];
    char modified[12];
    char description[100];
    char title[100];
    char url[100];
    char title_type[100];
    double rating;
    int runtime;
    int year;
    char genres[100];
    int num_votes;
    char relase_date[20];
    char director[100];
    int fav;
    int list_points;
}movie;

const char *get_csv_field (char * tmp, int k);

void show_app_menu();

int id_cmp(const void*key1,const void*key2);

int key_cmp(const void*key1,const void*key2);

void opcionX();

void opcion6(SortedMap *files_map, SortedMap *movies_map, movie *aux_movie);

void opcion5(SortedMap *files_map, SortedMap *movies_map, movie *aux_movie);

void opcion4(SortedMap *files_map, SortedMap *movies_map, movie *aux_movie);

void opcion3(char* lista, movie *aux_movie, SortedMap *found, SortedMap *files_map);

void opcion2(char *files_map_key, SortedMap *files_map);

void opcion1(FILE *parch, SortedMap *movies_map, SortedMap *files_map, char *archivo, int i, char *linea, char (*field)[1024]);

#endif
