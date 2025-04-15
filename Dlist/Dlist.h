#ifndef LISTA_ENLAZADA_H
#define LISTA_ENLAZADA_H

/*
 * Definición de la estructura de nodo para una lista enlazada.
 */
typedef struct _DNodo {
    int data;               // Datos almacenados en el nodo
    struct _DNodo *next;     // Puntero al siguiente nodo en la lista
    struct _DNodo *prev;    // puntero al nodo anterior en la lista
} DNodo;

/*
 * Definición de un puntero a una lista enlazada.
 */
typedef struct Dlist {
    DNodo *first;
    DNodo *last;
}Dlist;


typedef enum {
    DLIST_RECORRIDO_HACIA_ADELANTE,
    DLIST_RECORRIDO_HACIA_ATRAS
}DlistOrdenDeRecorrido;
/*
 * Definición de un puntero a una función de visita que toma un entero como argumento.
 */
typedef void (*VisitorFunc)(int dato);

typedef int (*ComparationFunc)(int dato1, int dato2);


Dlist* create_list();

Dlist *add_first(Dlist *list, int value);

Dlist* add_last(Dlist *lista, int value);

void recorrer_lista(Dlist *list, VisitorFunc visit);
#endif /* LISTA_ENLAZADA_H */
