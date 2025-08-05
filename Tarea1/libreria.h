#ifndef LIBRERIA_H_INCLUDED
#define LIBRERIA_H_INCLUDED

typedef struct{
    long ID;
    char nombre[30];
    int elo;
    char formato[7];
}jugador;

typedef struct Node Node;

typedef struct DoublyLinkedList DoublyLinkedList;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct DoublyLinkedList {
    Node * head;
    Node * tail;
    Node * current;
    int tamano_data;
};

DoublyLinkedList * createDLL(int tamano_data) {
    DoublyLinkedList *dl = (DoublyLinkedList *)malloc(sizeof(DoublyLinkedList));
    dl->head = NULL;
    dl->current = NULL;
    dl->tail = NULL;
    dl->tamano_data = tamano_data;
    return dl;
}

void * firstDLL(DoublyLinkedList * list) {
    if(list != NULL && list->head != NULL) {
        Node *nodo = list->head;
        list->current = nodo;
        return nodo->data;
    }
    else{
        return NULL;
    }
}

void * nextDLL(DoublyLinkedList * list) {
    if( list != NULL && list->current != NULL){
        Node *nodo = list->current;
        if (nodo->next != NULL ){
            nodo = nodo->next;
            list->current = nodo;
            return nodo->data;
        }
        else{
            return NULL;
        }
    }
    else{
        return NULL;
    }
}

void * lastDLL(DoublyLinkedList * list) {
    if( list != NULL && list->tail != NULL ){
        Node *nodo = list->tail;
        list->current = nodo;
        return nodo->data;
    }
    else{
        return NULL;
    }
}

void * prevDLL(DoublyLinkedList * list) {
    if( list != NULL && list->current != NULL){
        Node *nodo = list->current;
        if (nodo->prev != NULL ){
            nodo = nodo->prev;
            list->current = nodo;
            return nodo->data;
        }
        else{
            return NULL;
        }
    }
    else{
        return NULL;
    }
}

void mostrar_listas(DoublyLinkedList *list2vs2) {
    DoublyLinkedList *lista_sala;
    //int cont=1;
    //printf("\nMostrar listas\n");
    if ((lista_sala = (DoublyLinkedList *)firstDLL(list2vs2)) != NULL) {
        while (lista_sala != NULL) {
            //printf("Sala: %d\n", cont++);
            jugador *player_lista;
            if ((player_lista = (jugador *)firstDLL(lista_sala)) != NULL) {
                while (player_lista != NULL) {
                    printf("%ld,",player_lista->ID);
                    printf("%s,",player_lista->nombre);
                    printf("%d,",player_lista->elo);
                    printf("%s\n",player_lista->formato);
                    player_lista = (jugador *)nextDLL(lista_sala);
                }
            }
            lista_sala = (DoublyLinkedList *)nextDLL(list2vs2);
        }
    } else {
        printf("NULL\n");
    }
}

void pushBack(DoublyLinkedList * list, void * data) {
    Node *nuevo;
    Node *nodo;

    if(list != NULL && list->tail != NULL){

        nuevo = (Node*)malloc(sizeof(Node));
        nodo = list->tail;
        if(nuevo != NULL){
            nuevo->data = data;
            nodo->next = nuevo;
            nuevo->next = NULL;
            nuevo->prev = nodo;
            list->tail = nuevo;
        }
    } else {

        nuevo = (Node*)malloc(sizeof(Node));
        if(nuevo != NULL){
            nuevo->data = data;
            nuevo->next = NULL;
            nuevo->prev = NULL;
            list->head = nuevo;
            list->current = nuevo;
            list->tail = nuevo;
        }
    }
}

void mostrar_jugadores_lista(DoublyLinkedList * list) {
    Node *nodo = list->head;
    printf("\nMostrando jugadores sala\n");
    while (nodo != NULL) {
        printf("nombre: %s\n", ((jugador *)(nodo->data))->nombre);
        nodo = nodo->next;
    }
    printf("\n");
}


void pushBack_malloc(DoublyLinkedList * list, void * data) {
    Node *nuevo;
    Node *nodo;

    if(list != NULL && list->tail != NULL){
        nuevo = (Node*)malloc(sizeof(Node));
        nodo = list->tail;
        if(nuevo != NULL){
            nuevo->data = (void*)malloc(list->tamano_data);
            *(jugador *)(nuevo->data) = *(jugador *)data;
            nodo->next = nuevo;
            nuevo->next = NULL;
            nuevo->prev = nodo;
            list->tail = nuevo;
        }
    } else {
        nuevo = (Node*)malloc(sizeof(Node));
        if(nuevo != NULL){
            nuevo->data = (void*)malloc(list->tamano_data);
            *(jugador *)(nuevo->data) = *(jugador *)data;
            nuevo->next = NULL;
            nuevo->prev = NULL;
            list->head = nuevo;
            list->current = nuevo;
            list->tail = nuevo;
        }
    }
}

void pushFront(DoublyLinkedList * list, void * data) {
     if(list != NULL && list->head != NULL){
        Node *nuevo = (Node*)malloc(sizeof(Node));
        Node *nodo = list->head;
        if(nuevo != NULL){
            nuevo->data = (void*)malloc(list->tamano_data);
            *(jugador *)(nuevo->data) = *(jugador *)data;
            nodo->prev = nuevo;
            nuevo->prev = NULL;
            nuevo->next = nodo;
            list->head = nuevo;
        }
    }
    else{
        Node* nuevo = (Node*)malloc(sizeof(Node));
        if(nuevo != NULL){
            nuevo->data = (void*)malloc(list->tamano_data);
            *(jugador *)(nuevo->data) = *(jugador *)data;
            nuevo->next = NULL;
            nuevo->prev = NULL;
            list->head = nuevo;
            list->current = nuevo;
            list->tail = nuevo;
        }
    }
}

void * popCurrent(DoublyLinkedList * list) {
    if(list != NULL && list->current != NULL){
        Node* nodo = list->current;
        if( nodo->prev != NULL ){
            if( nodo->next != NULL ){
                nodo->prev->next = nodo->next;
                nodo->next->prev = nodo->prev;
                list->current = nodo->next;
            }
            else {
                list->current = nodo->prev;
                list->tail = nodo->prev;
                nodo->prev->next = NULL;
            }
        }
        else {
            if( nodo->next != NULL ){
                list->current = nodo->next;
                list->head = nodo->next;
                nodo->next->prev = NULL;
            }
            else{
                list->head = NULL;
                list->current = NULL;
                list->tail = NULL;
            }
        }
        nodo->next = NULL;
        nodo->prev = NULL;
        return nodo->data;
    }
    else{
        return NULL;
    }
}

void * popCurrent2(DoublyLinkedList ** list) {
    void *ptr = NULL;
    if(*list != NULL && (*list)->current != NULL){
        Node* nodo = (*list)->current;
        if( nodo->prev != NULL ){
            if( nodo->next != NULL ){
                nodo->prev->next = nodo->next;
                nodo->next->prev = nodo->prev;
                (*list)->current = nodo->next;
            }
            else {
                (*list)->current = nodo->prev;
                (*list)->tail = nodo->prev;
                nodo->prev->next = NULL;
            }
        }
        else {
            if( nodo->next != NULL ){
                (*list)->current = nodo->next;
                (*list)->head = nodo->next;
                nodo->next->prev = NULL;
            }
            else{
                (*list)->head = NULL;
                (*list)->current = NULL;
                (*list)->tail = NULL;
            }
        }
        //nodo->next = NULL;
        //nodo->prev = NULL;
        ptr = nodo->data;
        free(nodo);
        return ptr;
    }
    else{
        return NULL;
    }
}

void *popCurrent_malloc(DoublyLinkedList ** list, void *data, int size) {
    if(*list != NULL && (*list)->current != NULL){
        Node* nodo = (*list)->current;
        if( nodo->prev != NULL ){
            if( nodo->next != NULL ){
                nodo->prev->next = nodo->next;
                nodo->next->prev = nodo->prev;
                (*list)->current = nodo->next;
            }
            else {
                (*list)->current = nodo->prev;
                (*list)->tail = nodo->prev;
                nodo->prev->next = NULL;
            }
        }
        else {
            if( nodo->next != NULL ){
                (*list)->current = nodo->next;
                (*list)->head = nodo->next;
                nodo->next->prev = NULL;
            }
            else{
                (*list)->head = NULL;
                (*list)->current = NULL;
                (*list)->tail = NULL;
            }
        }
        //nodo->next = NULL;
        //nodo->prev = NULL;
        memcpy(data, nodo->data, size);
        free(nodo->data);
        free(nodo);
        return (data);
    }
    return (NULL);
}

void liberar_lista(DoublyLinkedList *list2vs2,DoublyLinkedList *list2vs2sala){
    int acu = 0;
    char str_sala[500] = "";
    char str_jugador[100];
    jugador *aux = (jugador*)firstDLL(list2vs2sala);
    while((aux = (jugador*)popCurrent(list2vs2sala)) != NULL) {
        sprintf(str_jugador,"%s\n",aux->nombre);
        strcat(str_sala, str_jugador);
        acu += aux->elo;
        free(aux);
    }


    printf("Emparejamiento Listo\n");
    printf("Elo Promedio :%d\n",(int)acu/4);
    printf("Jugadores:\n");
    printf("%s",str_sala);
    printf("\n");

    popCurrent(list2vs2);
}

void crear_sala(DoublyLinkedList *list2vs2,DoublyLinkedList *list2vs2Sala,jugador player){
	list2vs2Sala = createDLL((sizeof(jugador)+(2*sizeof(Node*))));
	pushBack_malloc(list2vs2Sala,(void*)&player);
	pushBack(list2vs2,(void*)list2vs2Sala);
}

void sala_ready(jugador player , DoublyLinkedList *lista_sala , DoublyLinkedList *list2vs2 , int cont){
	pushBack_malloc(lista_sala, (void*)&player);
    liberar_lista(list2vs2, lista_sala);
    lastDLL(list2vs2);
}

void agregar_jugador( jugador player , int cont , DoublyLinkedList *lista_sala , DoublyLinkedList *list2vs2 ){
    pushBack_malloc(lista_sala, (void*)&player);
    lastDLL(list2vs2);
}

void redirigir_elo(jugador player,DoublyLinkedList *list2vs2Sala,DoublyLinkedList *list2vs2){
    pushBack_malloc(list2vs2Sala,(void*)&player);
    pushBack(list2vs2,(void*)list2vs2Sala);
}

void mostrar_menu(){
    printf("\n    Ingrese su opcion\n");
    printf(" 1- Ingresar jugadores desde un archivo \n");
    printf(" 2- Ingresar manualmente a un nuevo jugador \n");
    printf(" 3- Quitar de la cola de espera a un jugador \n");
    printf(" 4- Mostrar el contenido de la cola ingresada \n");
    printf(" En otro caso se terminará el programa\n");
}

void fill_player(char *ptr,jugador *player,char *elemento){
    for(int i = 0 ; i < 4 ; i++ ){
        if((elemento = strtok_r(ptr, ",", &ptr)) != NULL){
            switch(i){
                case 0:
                    (*player).ID = atol(elemento);
                    break;
                case 1:
                    strcpy((*player).nombre,elemento);
                    break;
                case 2:
                    (*player).elo = atoi(elemento);
                    break;
                case 3:
                    strcpy((*player).formato,elemento);
                    break;
            }
        }
    }
}

int ya_esta(DoublyLinkedList *list5vs5 , DoublyLinkedList *lista_sala2 , jugador *player_lista2 , DoublyLinkedList *list2vs2 , DoublyLinkedList *lista_sala , jugador *player_lista , long ID ){
    int sw1 = 0;
    if (list5vs5->head != NULL && (lista_sala2 = (DoublyLinkedList *)firstDLL(list5vs5)) != NULL) {
        while (lista_sala2 != NULL) {
            if ((player_lista2 = (jugador *)firstDLL(lista_sala2)) != NULL) {
                while (player_lista2 != NULL) {
                    if(ID == player_lista2->ID){
                        printf("El ID: %ld ya existe en una cola de espera\n",ID);
                        sw1 = 1;
                    }
                    player_lista2 = (jugador *)nextDLL(lista_sala2);
                }
            }
            lista_sala2 = (DoublyLinkedList *)nextDLL(list5vs5);
        }
    }
    if(sw1 == 0){
        if (list2vs2->head != NULL && (lista_sala = (DoublyLinkedList *)firstDLL(list2vs2)) != NULL) {
            while (lista_sala != NULL) {
                if ((player_lista = (jugador *)firstDLL(lista_sala)) != NULL) {
                    while (player_lista != NULL) {
                        if(ID == player_lista->ID){
                            printf("El ID: %ld ya existe en una cola de espera\n",ID);
                            sw1 = 1;
                        }
                        player_lista = (jugador *)nextDLL(lista_sala);
                    }
                }
                lista_sala = (DoublyLinkedList *)nextDLL(list2vs2);
            }
        }
    }
    return sw1;
}

void borrar_todo(DoublyLinkedList *list5vs5 , DoublyLinkedList *lista_sala2 , jugador *player_lista2 , DoublyLinkedList *list2vs2 , DoublyLinkedList *lista_sala , jugador *player_lista){
    if (list5vs5->head != NULL && (lista_sala2 = (DoublyLinkedList *)firstDLL(list5vs5)) != NULL) {
        while (lista_sala2 != NULL) {
            if ((player_lista2 = (jugador *)firstDLL(lista_sala2)) != NULL) {
                while (player_lista2 != NULL) {
                    player_lista2 = popCurrent_malloc(&lista_sala2, player_lista2, sizeof(*player_lista2));
                    //player_lista2 = (jugador *)nextDLL(lista_sala2);
                }
            }
            lista_sala2 = popCurrent2(&list5vs5);
            //lista_sala2 = (DoublyLinkedList *)nextDLL(list5vs5);
        }
    }
    if (list2vs2->head != NULL && (lista_sala = (DoublyLinkedList *)firstDLL(list2vs2)) != NULL) {
        while (lista_sala != NULL) {
            if ((player_lista = (jugador *)firstDLL(lista_sala)) != NULL) {
                while (player_lista != NULL) {
                    player_lista = popCurrent_malloc(&lista_sala, player_lista, sizeof(*player_lista));
                    //player_lista = (jugador *)nextDLL(lista_sala);
                }
            }
            lista_sala = popCurrent2(&list2vs2);
            //lista_sala = (DoublyLinkedList *)nextDLL(list2vs2);
        }
    }
}

#endif // LIBRERIA_H_INCLUDED
