#include "Colas.h"
#include <stdlib.h>

Cola* cola_crear() {
    Cola* cola = (Cola*)malloc(sizeof(Cola));
    cola->lista = lista_crear();
    return cola;
}

void cola_destruir(Cola* cola, void (*destruir_dato)(void*)) {
    lista_destruir(cola->lista, destruir_dato);
    free(cola);
}

int cola_es_vacia(Cola* cola) {
    return lista_es_vacia(cola->lista);
}

void* cola_inicio(Cola* cola) {
    return lista_primero(cola->lista);
}

void cola_encolar(Cola* cola, void* dato) {
    lista_insertar_al_final(cola->lista, dato);
}

void* cola_desencolar(Cola* cola) {
    return lista_eliminar_primero(cola->lista);
}

void cola_imprimir(Cola* cola, void (*imprimir_dato)(void*)) {
    lista_imprimir(cola->lista, imprimir_dato);
}
