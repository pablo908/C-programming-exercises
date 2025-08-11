#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node Node;

typedef struct DoublyLinkedList DoublyLinkedList;

struct Node {
    void * data; // Puntero al dato
    Node * next; // Puntero al siguiente Node
    Node * prev; // Puntero al Node previo
};

struct DoublyLinkedList {
    Node * head; // Puntero al primer elemento
    Node * tail; // Puntero al ultimo elemento
    Node * current; // Puntero para poder recorrer la lista
};

DoublyLinkedList * createDLL() {
    DoublyLinkedList *dl = (DoublyLinkedList *)malloc(sizeof(DoublyLinkedList));
    dl->head = NULL;
    dl->current = NULL;
    dl->tail = NULL;
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

void pushBack(DoublyLinkedList * list, void * data) {
    if(list != NULL && list->tail != NULL){
        Node *nuevo = (Node*)malloc(sizeof(Node));
        Node *nodo = list->tail;
        if(nuevo != NULL){
            nuevo->data = data;
            nodo->next = nuevo;
            nuevo->next = NULL;
            nuevo->prev = nodo;
            list->tail = nuevo;
        }
    }
    else{
        Node* nuevo = (Node*)malloc(sizeof(Node));
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

void pushFront(DoublyLinkedList * list, void * data) {
     if(list != NULL && list->head != NULL){
        Node *nuevo = (Node*)malloc(sizeof(Node));
        Node *nodo = list->head;
        if(nuevo != NULL){
            nuevo->data = data;
            nodo->prev = nuevo;
            nuevo->prev = NULL;
            nuevo->next = nodo;
            list->head = nuevo;
        }
    }
    else{
        Node* nuevo = (Node*)malloc(sizeof(Node));
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

// FUNCIÓN MAIN
   
int main() {
  FILE * fp = fopen("Nombres.txt", "r");
  if(fp != NULL){
    DoublyLinkedList *list = createDLL();
    char str[100][100];
    int j = 0;
    while(fgets(str[j],100,fp)){
        str[j][(strlen(str[j]))-2] = '\0';
        pushBack(list,str[j]);
	j++;
    }
    char *ptr;
    ptr = firstDLL(list);
    while(list->current != list->tail){
        printf("%s\n",ptr);
        ptr = nextDLL(list);
    }
    printf("%s\n" , ptr);
  }
  return 0;
}
