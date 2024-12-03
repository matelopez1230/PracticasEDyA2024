#ifndef _PRIMERLLAMADO_H_
#Define _PRIMERLLAMADO_H_
#include <stdlib.h>
#include <stdio.h>

typedef void* (*FuncionCopiadora)(void*);
typedef int (*FuncionComparadora)(void*, void*);
typedef void (*FuncionDestructora)(void*);
typedef unsigned (*FuncionHash)(void*);

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


#endif //_PRIMERLLAMADO_H_