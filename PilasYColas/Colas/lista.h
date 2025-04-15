#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>

// Definición del nodo
typedef struct Nodo {
    void* dato;
    struct Nodo* siguiente;
    struct Nodo* anterior;
} Nodo;

// Definición de la lista enlazada doblemente
typedef struct {
    Nodo* cabeza;
    Nodo* cola;
    size_t longitud;
} Lista;

// Funciones de la lista
Lista* lista_crear();
void lista_destruir(Lista* lista, void (*destruir_dato)(void*));
int lista_es_vacia(Lista* lista);
void lista_insertar_al_final(Lista* lista, void* dato);
void* lista_eliminar_primero(Lista* lista);
void* lista_primero(Lista* lista);
void lista_imprimir(Lista* lista, void (*imprimir_dato)(void*));

#endif // LISTA_H
