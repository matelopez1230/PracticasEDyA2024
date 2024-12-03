#ifndef __TABLAHASH_H__
#define __TABLAHASH_H__



typedef void *(*Funcion_copiadora) (void* value);
typedef int (*Funcion_comparadora) (void* value1, void* value2);
typedef void (*Funcion_destructora) (void* value);
typedef unsigned (*Funcion_hash) (void* value);

typedef struct Nodo_ {
    void *value;
    struct Nodo_ *sig;
}Nodo;

typedef struct Head {
    Nodo* first;
}CasillaHash;

typedef enum {
    ENCADENAMIENTO,
    DIRECCIONAMIENTO_ABIERTO
}ModoColision;

typedef struct HashT {
    CasillaHash *elems;
    unsigned NumElems;
    unsigned Capacidad;
    Funcion_copiadora cpy;
    Funcion_comparadora comp;
    Funcion_destructora dstry;
    Funcion_hash hashing;
    ModoColision mode;
}HashT;

typedef struct HashT *TablaHash;

#endif /*__TABLAHASH_H__*/