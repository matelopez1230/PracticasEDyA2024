#include "primerllamado.h"

void tablahash_redimensionar(TablaHash tabla) {
    unsigned capacidad_antigua = tabla->capacidad;
    CasillaHash *elems_antiguos = tabla->elems;
    unsigned nueva_capacidad = capacidad_antigua * 2;
    tabla->elems = (CasillaHash *)calloc(nueva_capacidad, sizeof(CasillaHash));
    tabla->capacidad = nueva_capacidad;
    tabla->numElems = 0;
    for (unsigned i = 0; i < capacidad_antigua; ++i) {
        Nodo *nodo = elems_antiguos[i].cabeza;
        while (nodo != NULL) {
            Nodo *siguiente = nodo->siguiente;
            unsigned nuevo_indice = tabla->hash(nodo->dato) % nueva_capacidad;
            nodo->siguiente = tabla->elems[nuevo_indice].cabeza;
            tabla->elems[nuevo_indice].cabeza = nodo;
            tabla->numElems++;
            nodo = siguiente;
        }
    }
    free(elems_antiguos);
}

unsigned hash_function(void* dato) {
    return (unsigned)(uintptr_t)dato;
}

void* copia_function(void* dato) {
    return dato;
}

int comp_function(void* a, void* b) {
    return a == b;
}

void destr_function(void* dato) {   
    //terminar (lo antes posible):D
}

int main() {
    TablaHash tabla = (TablaHash)malloc(sizeof(struct _TablaHash));
    tabla->capacidad = 4;
    tabla->elems = (CasillaHash *)calloc(tabla->capacidad, sizeof(CasillaHash));
    tabla->copia = copia_function;
    tabla->comp = comp_function;
    tabla->destr = destr_function;
    tabla->hash = hash_function;
    tabla->modo = ENCANDENAMIENTO;

    tablahash_redimensionar(tabla);

    free(tabla->elems);
    free(tabla);

    return 0;
}