#include "Hashmaps.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


TablaHash crear_tabla(unsigned capacidad, Funcion_copiadora copy, Funcion_comparadora compare, Funcion_destructora Destroy, Funcion_hash hash, ModoColision modo) {
    TablaHash tabla = malloc(sizeof(TablaHash));
    assert(tabla != NULL);
    tabla->elems   = malloc(sizeof(CasillaHash) * capacidad);
    assert(tabla != NULL);
    tabla->NumElems = 0;
    tabla->Capacidad = capacidad;
    tabla->cpy = copy;
    tabla->comp = compare;
    tabla->dstry = Destroy;
    tabla->hashing = hash;
    tabla->mode = modo;

    for (unsigned idx = 0; idx < capacidad; idx++){
        tabla->elems[idx].first= NULL;
    }
    return tabla;
}

int tablahash_nelems(TablaHash tabla) {return tabla->NumElems; }

int tablahash_capacidad(TablaHash tabla) {return tabla->Capacidad; }

void tablahash_destruir(TablaHash tabla) {
    if (tabla == NULL) {
        return;
    }

    for (unsigned idx = 0; idx < tabla->Capacidad; idx++) {
        Nodo* actual = tabla->elems[idx].first;

        while (actual != NULL)
        {
            Nodo * siguiente = actual->sig;
            tabla->dstry(actual->value);
            free(actual);
            actual = siguiente;
        }
        
    }
    free(tabla->elems);
    free(tabla);
    
}

void encadenamiento_insertar(TablaHash tabla, void* dato) {
    unsigned idx = tabla->hashing(dato) % tabla->Capacidad;
    Nodo* node = tabla->elems[idx].first;
    while (node != NULL) {

        if (tabla->comp(node->value, dato) == 0) {

            if (tabla->dstry != NULL) {
                tabla->dstry(node->value);
            }
            node->value = tabla->cpy(dato);
            return; 
        }
        node = node->sig;
    }
    Nodo* Newnode = (Nodo*)malloc(sizeof(Nodo));
    assert(Newnode != NULL); 
    Newnode->value = tabla->cpy(dato);
    Newnode->sig = tabla->elems[idx].first; 
    tabla->elems[idx].first = Newnode;    
    tabla->NumElems++;
}


void *encadenamiento_buscar(TablaHash tabla, void* dato) {
    unsigned idx = tabla->hashing(dato) % tabla->Capacidad;
    Nodo *node tabla->elems[idx].first;
    while (node != NULL) {
        if (tabla->comp(node->value,dato) == 0) {
            return node->value;
        }
        node = node->sig;
    }
    return NULL;
}