#ifndef __HEAPS_H__
#define __HEAPS_H__ 

typedef int(*Funcioncomparadora)(void *,void *);
typedef void(*FuncionVisitante)(void*);

typedef struct _BHeap {
    void ** arr;
    int capacidad;
    int ultimo;
    FuncionComparadora comp;
}*BHeap;


BHeap bheap_crear(int, Funcioncomparadora);

void bheap_destruir(BHeap);

int bheap_vacio(BHeap);

void bheap_recorrer(BHeap, FuncionVisitante);
#endif /*__HEAPS_H__*/