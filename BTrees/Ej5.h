#ifndef BTREE_H
#define BTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Definición del nodo del árbol binario
typedef struct BTnodo {
    int dato;
    struct BTnodo *left;
    struct BTnodo *right;
} BTNodo;

// Definición del tipo de árbol binario
typedef BTNodo* BTree;

// Implementación de la cola
typedef struct NodoCola {
    BTree arbol;
    struct NodoCola *siguiente;
} NodoCola;

typedef struct Cola {
    NodoCola *frente;
    NodoCola *fondo;
} Cola;


// Definición de la función visitante
typedef void (*FuncionVisitante)(int);

// Funciones para gestionar el árbol binario
BTree btree_crear();
void btree_destruir(BTree nodo);
int btree_empty(BTree nodo);
BTree btree_unir(int dato, BTree left, BTree right);

// Función de recorrido BFS
void btree_recorrer_bfs(BTree arbol, FuncionVisitante visit);

#endif // BTREE_H