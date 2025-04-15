#include "Ej5.h"

// Creación de un árbol vacío
BTree btree_crear() {
    return NULL;
}

// Destrucción del árbol
void btree_destruir(BTree nodo) {
    if (nodo != NULL) {
        btree_destruir(nodo->left);
        btree_destruir(nodo->right);
        free(nodo);
    }
}

// Indica si el árbol es vacío
int btree_empty(BTree nodo) {
    return nodo == NULL;
}

// Crea un nuevo árbol con el dato dado en el nodo raíz, y los subárboles dados a izquierda y derecha
BTree btree_unir(int dato, BTree left, BTree right) {
    BTree nuevoNodo = malloc(sizeof(struct BTnodo));
    assert(nuevoNodo != NULL);
    nuevoNodo->dato = dato;
    nuevoNodo->left = left;
    nuevoNodo->right = right;
    return nuevoNodo;
}



Cola* crearCola() {
    Cola *cola = malloc(sizeof(Cola));
    cola->frente = cola->fondo = NULL;
    return cola;
}

void encolar(Cola *cola, BTree arbol) {
    NodoCola *nuevoNodo = malloc(sizeof(NodoCola));
    nuevoNodo->arbol = arbol;
    nuevoNodo->siguiente = NULL;
    if (cola->fondo == NULL) {
        cola->frente = cola->fondo = nuevoNodo;
    } else {
        cola->fondo->siguiente = nuevoNodo;
        cola->fondo = nuevoNodo;
    }
}

BTree desencolar(Cola *cola) {
    if (cola->frente == NULL) return NULL;
    NodoCola *nodoFrente = cola->frente;
    BTree arbol = nodoFrente->arbol;
    cola->frente = nodoFrente->siguiente;
    if (cola->frente == NULL) {
        cola->fondo = NULL;
    }
    free(nodoFrente);
    return arbol;
}

int colaVacia(Cola *cola) {
    return cola->frente == NULL;
}

void destruirCola(Cola *cola) {
    while (!colaVacia(cola)) {
        desencolar(cola);
    }
    free(cola);
}


void btree_recorrer_bfs(BTree arbol, FuncionVisitante visit) {
    if (arbol == NULL) return;

    Cola *cola = crearCola();
    encolar(cola, arbol);

    while (!colaVacia(cola)) {
        BTree nodoActual = desencolar(cola);
        visit(nodoActual->dato);

        if (nodoActual->left != NULL) {
            encolar(cola, nodoActual->left);
        }
        if (nodoActual->right != NULL) {
            encolar(cola, nodoActual->right);
        }
    }

    destruirCola(cola);
}


void imprimir(int dato) {
    printf("%d ", dato);
}

// Función principal para probar el código
int main() {
    // Crear un árbol de ejemplo
    BTree arbol = btree_unir(1, 
                             btree_unir(2, 
                                        btree_unir(4, btree_crear(), btree_crear()), 
                                        btree_unir(5, btree_crear(), btree_crear())), 
                             btree_unir(3, btree_crear(), btree_crear()));

    printf("Recorrido BFS: ");
    btree_recorrer_bfs(arbol, imprimir);
    printf("\n");

    // Liberar memoria del árbol
    btree_destruir(arbol);

    return 0;
}