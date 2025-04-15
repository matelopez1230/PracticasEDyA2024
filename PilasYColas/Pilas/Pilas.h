#ifndef PILAS_H
#define PILAS_H
#include "ArreglosEnteros.h"
#include "ListasGenerales.h"

struct _Pila {
    ArregloEnteros *arr;
    int last;
};

struct _PilaGL {
    GList *last;
};


typedef struct _Pila *Pila;

typedef struct _PilaGL *PilaGL;

Pila pila_crear(int capacidad);

void pila_destruir(Pila stack);

int pila_es_vacia(Pila stack);

int pila_tope(Pila stack);

void pila_apilar(Pila stack, int value);

void pila_desapilar(Pila stack);

void imprimir_pila(Pila stack);

PilaGL crearPila();

void destruirPila(PilaGL pila, FuncionDestructora destroy);

void apilar(PilaGL pila, void* dato, FuncionCopia copiar);

void* desapilar(PilaGL pila)

void imprimirUltimo(PilaGL pila, FuncionVisitante visit);


GList revertirLista(GList lista, FuncionCopia copiar);
#endif /* PILAS_H */
