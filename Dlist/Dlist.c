#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dlist.h"

Dlist* create_list(){
    Dlist *list = malloc(sizeof(Dlist));
    if (list !=NULL)
    {
        list->first = NULL;
        list->last = NULL;
    }
    return list;
}

Dlist *add_first(Dlist *list, int value){
    DNodo *Newnode = malloc(sizeof(DNodo));

    Newnode->data = value;
    list->first = Newnode;

    if (list->first->next == NULL)
    {
        list->last = Newnode;
        Newnode->next = NULL;
    }
    else {
        Newnode->next =list;
    }    
    return Newnode;
}

Dlist* add_last(Dlist *lista, int value) {
    DNodo *nuevoNodo = (DNodo *)malloc(sizeof(DNodo));

    nuevoNodo->data = value;
    nuevoNodo->next = NULL;

    if (lista->first == NULL) {
        lista->first = nuevoNodo;
        lista->last = nuevoNodo;
    } 
    else {
        lista->last->next = nuevoNodo;
        lista->last = nuevoNodo;
    }
    return lista;
}

void recorrer_lista(Dlist *list, VisitorFunc visit) {
    DNodo *node = list->first;
    while (node != list->last) {
        visit(node);
        node = node->next;
    }
}