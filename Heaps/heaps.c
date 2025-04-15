#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heaps.h"

void swap(void **a, void **b) {
    void *temp = *a;
    *a = *b;
    *b = temp;
}

BHeap bheap_crear(int capacidad, FuncionComparadora comp) {
    BHeap heap = (BHeap)malloc(sizeof(struct _BHeap));
    if (heap == NULL) {
        return NULL;
    }
    heap->arr = (void **)malloc(sizeof(void *) * capacidad);
    if (heap->arr == NULL) {
        free(heap);
        return NULL;
    }
    heap->capacidad = capacidad;
    heap->ultimo = -1;
    heap->comp = comp;
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
    return (heap == NULL || heap->ultimo == -1) ? 1 : 0;
}

void bheap_recorrer(BHeap heap, Funcionvisitante visit) {
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

void bheap_insertar(BHeap heap, void *val) {
    if (heap->ultimo == (heap->capacidad - 1)) {
        heap->capacidad *= 2;
        heap->arr = realloc(heap->arr, sizeof(void *) * heap->capacidad);
        if (heap->arr == NULL) {
            return;
        }
    }
    heap->arr[++heap->ultimo] = val;

    int pos = heap->ultimo;
    while (pos > 0) {
        int padrepos = (pos - 1) / 2;
        if (heap->comp(heap->arr[padrepos], heap->arr[pos]) >= 0) {
            break;
        }
        swap(&heap->arr[padrepos], &heap->arr[pos]);
        pos = padrepos;
    }
}

void heapify(BHeap heap, int pos) {
    int izq = 2 * pos + 1;
    int der = 2 * pos + 2;
    int mayor = pos;

    if (izq <= heap->ultimo && heap->comp(heap->arr[izq], heap->arr[mayor]) > 0) {
        mayor = izq;
    }
    if (der <= heap->ultimo && heap->comp(heap->arr[der], heap->arr[mayor]) > 0) {
        mayor = der;
    }
    if (mayor != pos) {
        swap(&heap->arr[pos], &heap->arr[mayor]);
        heapify(heap, mayor);
    }
}

void bheap_eliminar(BHeap heap, void *elemento) {
    int pos = -1;
    for (int i = 0; i <= heap->ultimo; i++) {
        if (heap->arr[i] == elemento) {
            pos = i;
            break;
        }
    }
    if (pos == -1) {
        printf("Elemento no encontrado en el heap\n");
        return;
    }
    heap->arr[pos] = heap->arr[heap->ultimo--];
    heapify(heap, pos);
    heap->capacidad = heap->ultimo + 1;
    heap->arr = realloc(heap->arr, sizeof(void *) * heap->capacidad);
}



BHeap bheap_crear_desde_arreglo(void **arr, int largo, FuncionCopiar cpy, FuncionComparadora comp) {
    BHeap heap = bheap_crear(largo, comp);
    if (heap == NULL) {
        return NULL;
    }

    for (int i = 0; i < largo; i++) {
        heap->arr[i] = cpy(arr[i]);
    }

    heap->ultimo = largo - 1;

    for (int i = largo / 2 - 1; i >= 0; i--) {
        heapify(heap, i);
    }

    return heap;
}

void *bheapEliminarRaiz(BHeap heap) {
    if (bheap_vacio(heap)) {
        return NULL;
    }

    void *raiz = heap->arr[0];
    heap->arr[0] = heap->arr[heap->ultimo--];
    heapify(heap, 0);

    return raiz;
}

void heapSort(void **arr, int largo, int (*comp)(void *, void *)) {
    BHeap heap = bheap_crear(largo, comp);
    if (heap == NULL) {
        return;
    }

    for (int i = 0; i < largo; i++) {
        bheap_insertar(heap, arr[i]);
    }
    for (int i = largo - 1; i >= 0; i--) {
        arr[i] = bheapEliminarRaiz(heap);
    }

    bheap_destruir(heap);
}

PriorityQueue* pq_crear(int capacidad, FuncionComparadora comp) {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    if (pq == NULL) {
        return NULL;
    }
    pq->heap = bheap_crear(capacidad, comp);
    if (pq->heap == NULL) {
        free(pq);
        return NULL;
    }
    return pq;
}

void pq_insertar(PriorityQueue* pq, void* val) {
    bheap_insertar(pq->heap, val);
}

void* pq_eliminar(PriorityQueue* pq) {
    return bheapEliminarRaiz(pq->heap);
}

int pq_vacio(PriorityQueue* pq) {
    return bheap_vacio(pq->heap);
}

void pq_destruir(PriorityQueue* pq) {
    bheap_destruir(pq->heap);
    free(pq);
}

void pq_recorrer(PriorityQueue* pq, Funcionvisitante visit) {
    bheap_recorrer(pq->heap, visit);
}

void printArray(void **arr, int largo) {
    for (int i = 0; i < largo; i++) {
        printf("%d ", *(int *)arr[i]);
    }
    printf("\n");
}

int compare(void *a, void *b) {
    return (*(int *)a - *(int *)b);
}
