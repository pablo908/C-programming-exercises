#include <stdlib.h>
#include <stdio.h>

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

//sin revisar***********************************************************

void * lastDLL(DoublyLinkedList * list) {
    list->current = list->tail;
    return list->tail->data;
    
}

void * prevDLL(DoublyLinkedList * list) {
    list->current = list->current->prev;
    return list->current->data;
}

void pushBack(DoublyLinkedList * list, void * data) {
     if(list != NULL){
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
/*
	printf("\nCola lista: %d\n", *(int *)list->tail->data);

	Node *ptr;
	int x = 0;
	if (list != NULL) {
		for (ptr=list->head; ptr!=NULL; ) {
			printf("\nx=%d, Dato: %d\n", x++, *(int *)ptr->data);
			ptr = ptr->next;
		}

		for (ptr=list->tail; ptr!=NULL; ) {
			printf("\nx=%d, Dato: %d\n", x++, *(int *)ptr->data);
			ptr = ptr->prev;
		}

	}
*/

}

// *********************************************************************

void * firstDLL(DoublyLinkedList * list) {
    list->current = list->head;
    return list->head->data;
}

void * nextDLL(DoublyLinkedList * list) {
	//printf("\nDato prenext: %d\n", *(int *)list->current->data);
	list->current = list->current->next;
	//printf("\nDato next: %d\n", *(int *)list->current->data);
	return list->current->data;
}

int main(){

	int numeros[] = {1, 2, 3, 4, 5};
	DoublyLinkedList *list = createDLL();
	for(int i = 0 ; i < 5 ; i++){
		Node *nodo = (Node*)malloc(sizeof(Node));
		nodo->data = &(numeros[i]);
		if(i == 0){
			nodo->prev = NULL;
			nodo->next = NULL;
			list->head = nodo;
			list->current = nodo;
			list->tail = nodo;
		}
		else{
			nodo->prev = list->current;
			nodo->next = NULL;
			list->current->next = nodo;
			list->current = nodo;
			list->tail = nodo;
		}
	}
	int dato, dato1, dato2, dato3;

	dato1 = 6;
	pushBack(list,&dato1);
	dato2 = 7;
	pushBack(list,&dato2);
	dato3 = 8;
	pushBack(list,&dato3);



	Node *ptr;
	if (list != NULL) {
		for (ptr=list->head; ptr!=NULL; ) {
			printf("\nDato: %d\n", *(int *)ptr->data);
			ptr = ptr->next;
		}
	}
	//list->current = list->current->next;



	dato = *(int *)firstDLL(list);
	while (list->current->next != NULL ) {
		printf("\n%d\n",dato);
		dato = *(int *)nextDLL(list);
	}
	printf("\n%d\n",dato);

	dato = *(int *)lastDLL(list);
	while (list->current->prev != NULL ) {
		printf("\n%d\n",dato);
		dato = *(int *)prevDLL(list);
	}
	printf("\n%d\n",dato);

}
