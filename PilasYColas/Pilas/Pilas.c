#include <stdio.h>
#include <stdlib.h>
#include "Pilas.h"

Pila pila_crear(int capacidad) {
    Pila solution = malloc(sizeof(Pila));
    crear_arreglo_enteros(capacidad);
    return solution;
}

void pila_destruir(Pila stack) {
    destruir_arreglos_enteros(stack->arr);
    free(stack);
}

int pila_es_vacia(Pila stack) {
    return stack->last == -1;
}

int pila_tope(Pila stack) {
    return stack->arr->direccion[stack->last];
}

void pila_apilar(Pila stack, int value) {
    if (stack->last > stack->arr->capacidad)
    {
        arreglo_enteros_ajustar(stack->arr, (2*stack->arr->capacidad));
    }
    stack->last++;
    escribir_arreglos_enteros(stack->arr->direccion,stack->last, value);
}

void pila_desapilar(Pila stack) {
    if (stack->last == -1) {
        printf("Empty stack. error");
        return;
    }
    else {
    stack->last--;
    }
}

void imprimir_pila(Pila stack) {
    for (int i = stack->last; i >= 0; i--) {
        printf("%d\n", stack->arr->direccion[i]);
    }
}


// PILAS CON LISTAS GENERALES//


PilaGL crearPila() {
    PilaGL pila = (PilaGL)malloc(sizeof(PilaGL));
    pila->last = glist_crear();
    return pila;
}

void destruirPila(PilaGL pila, FuncionDestructora destruir) {
    glist_destruir(pila->last, destruir);
    free(pila);
}

void apilar(PilaGL pila, void* dato, FuncionCopia copiar) {
    pila->last = glist_agregar_inicio(pila->last, dato, copiar);
}


void* desapilar(PilaGL pila) {
    GNode* nodoAEliminar = pila->last;
    void* dato = nodoAEliminar->data;
    pila->last = pila->last->next;
    free(nodoAEliminar);
    return dato;
}


void imprimirUltimo(PilaGL pila, FuncionVisitante visit) {
    GNode* actual = pila->last;
    while (actual->next != NULL) {
        actual = actual->next;
    }
    visit(actual);
}



//Auxiliares para listas generales//

void* copiarEntero(void* dato) {
    int* nuevoEntero = (int*)malloc(sizeof(int));
    *nuevoEntero = *(int*)dato;
    return nuevoEntero;
}


void destruirEntero(void* dato) {
    free(dato);
}


void imprimirEntero(void* dato) {
    printf("%d ", *(int*)dato);
}



// EJERCICIO 3 //


GList revertirLista(GList lista, FuncionCopia copiar) {
    PilaGL pila = crearPila();
    GList listaInvertida = glist_crear();
    GNode* actual = lista;
    void* dato;

    while (actual != NULL) {
        apilar(pila, actual->data, copiar);
        actual = actual->next;
    }
    while ((dato = desapilar(pila)) != NULL) {
        listaInvertida = glist_agregar_inicio(listaInvertida, dato, copiar);
    }
    destruirPila(pila, destruirEntero);
    return listaInvertida;
}