#ifndef COLA_H
#define COLA_H

#include "lista.h"

// Definición de la cola
typedef struct {
    Lista* lista;
} Cola;

// Funciones de la cola
Cola* cola_crear();
void cola_destruir(Cola* cola, void (*destruir_dato)(void*));
int cola_es_vacia(Cola* cola);
void* cola_inicio(Cola* cola);
void cola_encolar(Cola* cola, void* dato);
void* cola_desencolar(Cola* cola);
void cola_imprimir(Cola* cola, void (*imprimir_dato)(void*));

#endif // COLA_H
