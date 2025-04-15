#include "tablahash.h"
#include <assert.h>
#include <stdlib.h>

typedef struct Nodo {
    void *dato;
    struct Nodo *siguiente;
} Nodo;

typedef struct {
    Nodo *cabeza;
} CasillaHash;

typedef enum {
    ENCANDENAMIENTO,
    DIRECCIONAMIENTO_ABIERTO
} ModoColision;

struct _TablaHash {
    CasillaHash *elems;
    unsigned numElems;
    unsigned capacidad;
    FuncionCopiadora copia;
    FuncionComparadora comp;
    FuncionDestructora destr;
    FuncionHash hash;
    ModoColision modo;
};

typedef struct _TablaHash *TablaHash;

/**
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
TablaHash tablahash_crear(unsigned capacidad, FuncionCopiadora copia, FuncionComparadora comp, FuncionDestructora destr, FuncionHash hash, ModoColision modo) {
    TablaHash tabla = malloc(sizeof(struct _TablaHash));
    assert(tabla != NULL);
    tabla->elems = malloc(sizeof(CasillaHash) * capacidad);
    assert(tabla != NULL);
    tabla->numElems = 0;
    tabla->capacidad = capacidad;
    tabla->copia = copia;
    tabla->comp = comp;
    tabla->destr = destr;
    tabla->hash = hash;
    tabla->modo = modo;

    for (unsigned idx = 0; idx < capacidad; ++idx) {
        tabla->elems[idx].dato = NULL;
        tabla->elems[idx].ocupado = 0; // Solo se usa para direccionamiento abierto
    }

    return tabla;
}

/**
 * Retorna el numero de elementos de la tabla.
 */
int tablahash_nelems(TablaHash tabla) { return tabla->numElems; }

/**
 * Retorna la capacidad de la tabla.
 */
int tablahash_capacidad(TablaHash tabla) { return tabla->capacidad; }

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash tabla) {

  // Destruir cada uno de los datos.
  for (unsigned idx = 0; idx < tabla->capacidad; ++idx)
    if (tabla->elems[idx].dato != NULL)
      tabla->destr(tabla->elems[idx].dato);

  // Liberar el arreglo de casillas y la tabla.
  free(tabla->elems);
  free(tabla);
  return;
}

void encadenamiento_insertar(TablaHash tabla, void *dato){
    unsigned idx = tabla->hash(dato) % tabla->capacidad;

    Nodo *nodo =tabla->elems[idx].cabeza;
    while (nodo!=NULL) {
        if (tabla->comp(nodo->dato, dato) == 0) {
            tabla->destr(nodo->dato);
            nodo->dato = tabla->copia(dato);
            return;
        }
        nodo = nodo->siguiente;
    }
    Nodo *nuevo_nodo = malloc(sizeof(Nodo));
    nuevo_nodo->dato = tabla->copia(dato);
    nuevo_nodo->siguiente = tabla->elems[idx].cabeza;
    tabla->elems[idx].cabeza = nuevo_nodo;
    tabla->numElems++;
}

void *encadenamiento_buscar(TablaHash tabla, void* dato) {
    unsigned idx = tabla->hash(dato) % tabla->capacidad;

    Nodo *nodo = tabla->elems[idx].cabeza;
    while (nodo != NULL) {
        if (tabla->comp(nodo->dato,dato)== 0) {
            return nodo->dato;
        }
        nodo = nodo->siguiente;
    }
    return NULL;
}

void encadenamiento_eliminar(TablaHash tabla, void *dato) {
    unsigned idx = tabla->hash(dato) % tabla->capacidad;

    Nodo *nodo = tabla->elems[idx].cabeza;
    Nodo *anterior = NULL;
    while (nodo != NULL) {
        if (tabla->comp(nodo->dato,dato) == 0) {
            if (anterior == NULL) {
                tabla->elems[idx].cabeza = nodo->siguiente;
            }else {
                anterior->siguiente = nodo->siguiente;
            }
            tabla->destr(nodo->dato);
            free(nodo);
            tabla->numElems--;
            return;
        }
        anterior = nodo;
        nodo = nodo->siguiente;
    }   
}

void direccionamiento_abierto_insertar(TablaHash tabla, void *dato) {
    unsigned idx = tabla->hash(dato) % tabla->capacidad;

    for (unsigned i = 0; i < tabla->capacidad; ++i) {
        unsigned pos = (idx + i) %tabla->capacidad;

        if (tabla->elems[pos].ocupado != 1) {
            if (tabla->elems[pos].ocupado == 0) {
                tabla->numElems ++;
            } else if (tabla->elems[pos].ocupado == -1) {
                tabla->destr(tabla->elems[pos].dato)    
            }
            tabla->elems[pos].dato = tabla->copia(dato);
            tabla->elems[pos].ocupado = 1;
            return;
        } else if (tabla->comp(tabla->elems[pos].dato, dato) == 0) {
            tabla->destr(tabla->elems[pos].dato);
            tabla->elems[pos].dato = tabla->copia(dato);
            return;
        }
    }
}

void * direccionamiento_abierto_buscar(TablaHash tabla, void *dato) {
    unsigned idx = tabla->hash(dato) % tabla->capacidad;

    for (unsigned i = 0; i < tabla->capacidad; i++) {
        unsigned pos  = (idx + i) % tabla->capacidad;

        if (tabla->elems[pos].ocupado == 0)
        {
            return NULL;
        }else if(tabla->elems[pos].ocupado == 1 && tabla->comp(tabla->elems[pos].dato,dato) == 0) {
            return tabla->elems[pos].dato;
        }
        
    }
    return NULL;
}

void direccionamiento_abierto_eliminar(TablaHash tabla, void *dato) {
    unsigned idx = tabla->hash(dato) % tabla->capacidad;

    for (unsigned i = 0; i < tabla->capacidad; ++i) {
        unsigned pos = (idx + i) % tabla->capacidad;

        if (tabla->elems[pos].ocupado == 0) {
            return;
        } else if (tabla->elems[pos].ocupado == 1 && tabla->comp(tabla->elems[pos].dato, dato) == 0) {
            tabla->destr(tabla->elems[pos].dato);
            tabla->elems[pos].dato = NULL;
            tabla->elems[pos].ocupado = -1;
            tabla->numElems--;
            return;
        }   
    }   
}

void tablahash_redimencionar(TablaHash tabla) {
    unsigned nueva_capacidad = tabla->capacidad * 2;
    CasillaHash *nuevos_elems = malloc(sizeof(CasillaHash)*nueva_capacidad);
    assert(nuevos_elems != NULL);

    for (unsigned idx = 0; idx < nueva_capacidad; ++idx)
    {
        nuevos_elems[idx].cabeza = NULL;
    }
    
    for (unsigned idx = 0; idx < tabla->capacidad; ++idx) {
        Nodo *nodo = tabla->elems[idx].cabeza;
        while (nodo != NULL) {
            Nodo *siguiente = nodo->siguiente;
            unsigned nuevo_idx = tabla->hash(nodo->dato) % nueva_capacidad;

            nodo->siguiente = nuevos_elems[nuevo_idx].cabeza;
            nuevos_elems[nuevo_idx].cabeza = nodo;

            nodo = siguiente;
        }
    }
    free(tabla->elems);
    tabla->elems = nuevos_elems;
    tabla->capacidad = nueva_capacidad;
}


void tablahash_insertar(TablaHash tabla, void *dato) {
    if (tabla->modo == ENCANDENAMIENTO) {
        encadenamiento_insertar(tabla, dato);
    } else {
        direccionamiento_abierto_insertar(tabla, dato);
    }
}

void *tablahash_buscar(TablaHash tabla, void *dato) {
    if (tabla->modo == ENCANDENAMIENTO) {
        return encadenamiento_buscar(tabla, dato);
    } else {
        return direccionamiento_abierto_buscar(tabla, dato);
    }
}

void tablahash_eliminar(TablaHash tabla, void *dato) {
    if (tabla->modo == ENCANDENAMIENTO) {
        encadenamiento_eliminar(tabla, dato);
    } else {
        direccionamiento_abierto_eliminar(tabla, dato);
    }
}

