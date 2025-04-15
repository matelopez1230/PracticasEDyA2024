#include <stdio.h>
#include <stdlib.h>
#include "Heaps.h"

BHeap bheap_crear(int cap,Funcioncomparadora comparadora) {
    BHeap heap = malloc(sizeof(BHeap));
    if (heap == NULL) {
        return NULL;
    }
    heap->capacidad = cap;
    heap->arr = (void *)(malloc(sizeof(void*)*heap->capacidad));
    heap->ultimo = 0;
    heap->comp = comparadora;
    return heap;
}

void bheap_destruir(BHeap heap) {
    if (heap == NULL) {
        return;
    }
    for (int i = 0; i <= heap->ultimo; i++) {
        free(heap->arr[i]);
    }
    free(heap->arr);
    free(heap);
}

int bheap_vacio(BHeap heap) {
    return (heap == NULL || heap->ultimo == -1)? 1:0;
}

void bheap_recorrer(BHeap heap, FuncionVisitante visit) {
    int nivel = 0;
    int pos = 0;
    while (pos <= heap->ultimo) {
        int inicio = pos;
        int fin = pos + (1 << nivel) - 1;
        if (fin > heap->ultimo) fin = heap->ultimo;
        for (int i = inicio; i <= fin; i++) {
            visit(heap->arr[i]);
        }
        pos = fin + 1;
        nivel++;
    }
}