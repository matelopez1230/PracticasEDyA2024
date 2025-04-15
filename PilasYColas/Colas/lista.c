#include "lista.h"
#include <stdlib.h>
#include <stdio.h>

Lista* lista_crear() {
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    if (!lista) return NULL;
    lista->cabeza = NULL;
    lista->cola = NULL;
    lista->longitud = 0;
    return lista;
}

void lista_destruir(Lista* lista, void (*destruir_dato)(void*)) {
    Nodo* actual = lista->cabeza;
    while (actual != NULL) {
        Nodo* siguiente = actual->siguiente;
        if (destruir_dato) destruir_dato(actual->dato);
        free(actual);
        actual = siguiente;
    }
    free(lista);
}

int lista_es_vacia(Lista* lista) {
    return lista->longitud == 0;
}

void lista_insertar_al_final(Lista* lista, void* dato) {
    Nodo* nuevo_nodo = (Nodo*)malloc(sizeof(Nodo));
    if (!nuevo_nodo) return;
    nuevo_nodo->dato = dato;
    nuevo_nodo->siguiente = NULL;
    nuevo_nodo->anterior = lista->cola;
    if (lista->cola) {
        lista->cola->siguiente = nuevo_nodo;
    } else {
        lista->cabeza = nuevo_nodo;
    }
    lista->cola = nuevo_nodo;
    lista->longitud++;
}

void* lista_eliminar_primero(Lista* lista) {
    if (lista_es_vacia(lista)) return NULL;
    Nodo* eliminado = lista->cabeza;
    void* dato = eliminado->dato;
    lista->cabeza = eliminado->siguiente;
    if (lista->cabeza) {
        lista->cabeza->anterior = NULL;
    } else {
        lista->cola = NULL;
    }
    free(eliminado);
    lista->longitud--;
    return dato;
}

void* lista_primero(Lista* lista) {
    if (lista_es_vacia(lista)) return NULL;
    return lista->cabeza->dato;
}

void lista_imprimir(Lista* lista, void (*imprimir_dato)(void*)) {
    Nodo* actual = lista->cabeza;
    while (actual != NULL) {
        imprimir_dato(actual->dato);
        actual = actual->siguiente;
    }
}
