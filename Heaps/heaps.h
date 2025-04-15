#ifndef __HEAPS_H__
#define __HEAPS_H__

typedef int (*FuncionComparadora)(void *, void *);
typedef void (*Funcionvisitante)(void*);
typedef void *(*FuncionCopiar)(void *dato);

typedef struct _BHeap {
    void **arr;
    int capacidad;
    int ultimo;
    FuncionComparadora comp;
} *BHeap;

typedef struct {
    BHeap heap;
} PriorityQueue;


BHeap bheap_crear(int, FuncionComparadora);

void bheap_destruir(BHeap);

int bheap_vacio(BHeap);

void bheap_recorrer(BHeap,Funcionvisitante);

void bheap_insertar(BHeap, void*);

void bheap_eliminar(BHeap, void*);

#endif /*__HEAPS_H__*/