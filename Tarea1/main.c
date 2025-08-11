#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "libreria.h"


int main()
{
	jugador player;
	bool flag = true;
	long identifier;
	char tipo_sala[5];
	char opcion;
	char *ptr = NULL;
	char linea[100];
	char *elemento = NULL;
	char archivo[100];
	FILE *parch;
	DoublyLinkedList *list2vs2;
	DoublyLinkedList *list5vs5;
	DoublyLinkedList *list2vs2Sala;
	DoublyLinkedList *list5vs5Sala;
    DoublyLinkedList *lista_sala;
    jugador *player_lista;
    DoublyLinkedList *lista_sala2;
    jugador *player_lista2;
    int cont;
    int sw1;

	while(true){
		if(flag == true){
			list2vs2 = createDLL((sizeof(jugador)+(2*sizeof(Node*))));
			list5vs5 = createDLL((sizeof(jugador)+(2*sizeof(Node*))));
			list5vs5Sala = createDLL((sizeof(jugador)+(2*sizeof(Node*))));
			flag = false;
		}
		mostrar_menu();
		scanf(" %c",&opcion);
		switch(opcion){
			case '1':
				printf("Ingrese el nombre del archivo\n");
				scanf("%s",archivo);
				if ((parch = fopen(archivo,"r")) != NULL) {
					printf("Leyendo el archivo: %s\n\n",archivo);
					while(fgets(linea,100,parch) != NULL){
						linea[strcspn(linea, "\r\n")] = 0;
						ptr = linea;
						fill_player(ptr,&player,elemento);
						if(strcmp(player.formato,"2vs2") == 0) {
							if (list2vs2->head != NULL && (lista_sala = (DoublyLinkedList *)firstDLL(list2vs2)) != NULL) {
                                while (lista_sala != NULL) {
									if ((player_lista = (jugador *)firstDLL(lista_sala)) != NULL) {
										cont = 0;
										while (player_lista != NULL) {
                                            int elo = abs(player.elo - player_lista->elo);
											if (elo <= 50) {
												cont++;
											} else {
												cont = -1;
												break;
											}
                                            player_lista = (jugador *)nextDLL(lista_sala);
										}
										switch (cont) {
										case -1:
											break;
										case 3:
                                            sala_ready(player,lista_sala,list2vs2,cont);
											break;
										default:
                                            agregar_jugador(player,cont,lista_sala,list2vs2);
											break;
										}
									}
                                    lista_sala = (DoublyLinkedList *)nextDLL(list2vs2);
								}

								if (cont==-1) {
                                    list2vs2Sala = createDLL((sizeof(jugador)+(2*sizeof(Node*))));
                                    redirigir_elo(player,list2vs2Sala,list2vs2);
								}
							} else {
                                crear_sala(list2vs2,list2vs2Sala,player);
							}
						}
						else{
                            if (list5vs5->head != NULL && (lista_sala2 = (DoublyLinkedList *)firstDLL(list5vs5)) != NULL) {
                                while (lista_sala2 != NULL) {
									if ((player_lista2 = (jugador *)firstDLL(lista_sala2)) != NULL) {
										cont = 0;
										while (player_lista2 != NULL) {
                                            int elo = abs(player.elo - player_lista2->elo);
											if (elo <= 50) {
												cont++;
											} else {
												cont = -1;
												break;
											}
                                            player_lista2 = (jugador *)nextDLL(lista_sala2);
										}
										switch (cont) {
										case -1:
											break;
										case 9:
                                            sala_ready(player,lista_sala2,list5vs5,cont);
											break;
										default:
                                            agregar_jugador(player,cont,lista_sala2,list5vs5);
											break;
										}
									}
                                    lista_sala2 = (DoublyLinkedList *)nextDLL(list5vs5);
								}

								if (cont==-1) {
                                    list5vs5Sala = createDLL((sizeof(jugador)+(2*sizeof(Node*))));
                                    redirigir_elo(player,list5vs5Sala,list5vs5);
								}
							} else {
                                crear_sala(list5vs5,list5vs5Sala,player);
							}
						}
					}
				} else {
					printf("Archivo %s no encontrado\n",archivo);
				}
				break;
			case '2':
                fflush(stdin);
                printf("Ingrese el formato del jugador que desea agregar:\n");
                while(getchar() != '\n');
                fgets(player.formato,7,stdin);
                printf("Ingrese el ID del jugador que desea agregar:\n");
                scanf(" %ld",&player.ID);
                printf("Ingrese el nombre del jugador que desea agregar:\n");
                while(getchar() != '\n');
                fgets(player.nombre,30,stdin);
                printf("Ingrese el elo del jugador que desea agregar:\n");
                scanf(" %d",&player.elo);
                player.formato[strcspn(player.formato, "\r\n")] = 0;
                player.nombre[strcspn(player.nombre, "\r\n")] = 0;
                if(ya_esta(list5vs5,lista_sala2,player_lista2,list2vs2,lista_sala,player_lista,player.ID) == 0){
                    if( strcmp(player.formato,"2vs2") == 0 ){
                        if (list2vs2->head != NULL && (lista_sala = (DoublyLinkedList *)firstDLL(list2vs2)) != NULL) {
                            while (lista_sala != NULL) {
                                if ((player_lista = (jugador *)firstDLL(lista_sala)) != NULL) {
                                    cont = 0;
                                    while (player_lista != NULL) {
                                        int elo = abs(player.elo - player_lista->elo);
                                        if (elo <= 50) {
                                            cont++;
                                        } else {
                                            cont = -1;
                                            break;
                                        }
                                        player_lista = (jugador *)nextDLL(lista_sala);
                                    }
                                    switch (cont) {
                                        case -1:
                                            break;
                                        case 3:
                                            sala_ready(player,lista_sala,list2vs2,cont);
                                            break;
                                        default:
                                            agregar_jugador(player,cont,lista_sala,list2vs2);
                                            break;
                                    }
                                }
                                lista_sala = (DoublyLinkedList *)nextDLL(list2vs2);
                            }
                            if (cont==-1) {
                                list2vs2Sala = createDLL((sizeof(jugador)+(2*sizeof(Node*))));
                                redirigir_elo(player,list2vs2Sala,list2vs2);
                            }
                        } else {
                            crear_sala(list2vs2,list2vs2Sala,player);
                        }
                    }else{
                        if( strcmp(player.formato,"5vs5") == 0 ){
                            if (list5vs5->head != NULL && (lista_sala2 = (DoublyLinkedList *)firstDLL(list5vs5)) != NULL) {
                                while (lista_sala2 != NULL) {
                                    if ((player_lista2 = (jugador *)firstDLL(lista_sala2)) != NULL) {
                                        cont = 0;
                                        while (player_lista2 != NULL) {
                                            int elo = abs(player.elo - player_lista2->elo);
                                            if (elo <= 50) {
                                                cont++;
                                            } else {
                                                cont = -1;
                                                break;
                                            }
                                            player_lista2 = (jugador *)nextDLL(lista_sala2);
                                        }
                                        switch (cont) {
                                        case -1:
                                            break;
                                        case 9:
                                            sala_ready(player,lista_sala2,list5vs5,cont);
                                            break;
                                        default:
                                            agregar_jugador(player,cont,lista_sala2,list5vs5);
                                            break;
                                        }
                                    }
                                    lista_sala2 = (DoublyLinkedList *)nextDLL(list5vs5);
                                }

                                if (cont==-1) {
                                    list5vs5Sala = createDLL((sizeof(jugador)+(2*sizeof(Node*))));
                                    redirigir_elo(player,list5vs5Sala,list5vs5);
                                }
                            } else {
                                crear_sala(list5vs5,list5vs5Sala,player);
                            }
                        }else{
                            printf("Cola de espera no valida");
                        }
                    }
                }
				break;
			case '3':
                sw1 = 0;
                printf("Ingrese el formato del jugador que desea borrar:\n");
                scanf("%s",tipo_sala);
                printf("Ingrese el ID del jugador que desea borrar:\n");
                scanf("%ld",&identifier);
                if(strcmp(tipo_sala,"2vs2") == 0){
                    if (list2vs2->head != NULL && (lista_sala = (DoublyLinkedList *)firstDLL(list2vs2)) != NULL) {
                        while (lista_sala != NULL && sw1 == 0) {
                            if ((player_lista = (jugador *)firstDLL(lista_sala)) != NULL) {
                                //cont = 0;
                                while (player_lista != NULL && sw1 == 0) {
                                    if(identifier == player_lista->ID){
                                        printf("Jugador eliminado: \n");
                                        printf("id: %ld\n",player_lista->ID);
                                        printf("nombre: %s\n",player_lista->nombre);
                                        printf("elo: %d\n",player_lista->elo);
                                        printf("formato: %s\n",player_lista->formato);
                                        player_lista = popCurrent_malloc(&lista_sala, player_lista, sizeof(*player_lista));

                                        if( lista_sala->head == NULL ){
                                            popCurrent2(&list2vs2);
                                        }
                                        sw1 = 1;
                                    } else {
                                        player_lista = (jugador *)nextDLL(lista_sala);
                                    }
                                }
                                lista_sala = (DoublyLinkedList *)nextDLL(list2vs2);
                            }
                        }
                    }
                    if (sw1 == 0){
                        printf("Error el jugador de ID %ld no existe en la cola 2vs2",identifier);
                    }

                }else{
                    if(strcmp(tipo_sala,"5vs5") == 0){
                        sw1 = 0;
                        if (list5vs5->head != NULL && (lista_sala2 = (DoublyLinkedList *)firstDLL(list5vs5)) != NULL) {
                            while (lista_sala2 != NULL && sw1 == 0) {
                                if ((player_lista2 = (jugador *)firstDLL(lista_sala2)) != NULL) {
                                    //cont = 0;
                                    while (player_lista2 != NULL && sw1 == 0) {
                                        if(identifier == player_lista2->ID){
                                            printf("Jugador eliminado: \n");
                                            printf("id: %ld\n",player_lista2->ID);
                                            printf("nombre: %s\n",player_lista2->nombre);
                                            printf("elo: %d\n",player_lista2->elo);
                                            printf("formato: %s\n",player_lista2->formato);
                                            player_lista2 = popCurrent_malloc(&lista_sala2, player_lista2, sizeof(*player_lista2));
                                            if( lista_sala2->head == NULL ){
                                                popCurrent2(&list5vs5);
                                            }
                                            sw1 = 1;
                                        } else {
                                            player_lista2 = (jugador *)nextDLL(lista_sala2);
                                        }
                                    }
                                }
                                lista_sala2 = (DoublyLinkedList *)nextDLL(list5vs5);
                            }
                        }
                        if(sw1 == 0){
                            printf("Error el jugador de ID %ld no existe en la cola 5vs5",identifier);
                        }
                    }else{
                        printf("Cola no valida\n");
                    }
                }
				break;
			case '4':
                printf(" Ingrese 2vs2 para ver la cola de espera 2vs2 \n");
                printf(" Ingrese 5vs5 para ver la cola de espera 5vs5 \n");
                scanf("%s",tipo_sala);
                if(strcmp(tipo_sala,"2vs2") == 0){
                    printf("\nCola de espera formato 2vs2\n");
                    mostrar_listas(list2vs2);
                }else{
                    if(strcmp(tipo_sala,"5vs5") == 0){
                        printf("\nCola de espera formato 5vs5\n");
                        mostrar_listas(list5vs5);
                    }
                    else{
                        printf("\nCola de espera no valida");
                    }
                }
				break;
			default:
                borrar_todo(list5vs5,lista_sala2,player_lista2,list2vs2,lista_sala,player_lista);
				printf("finaliza usando %c\n",opcion);
				return 0;
		}
	}
}
