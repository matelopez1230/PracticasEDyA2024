#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

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
    void *(*copia)(void *);
    int (*comp)(void *, void *);
    void (*destr)(void *);
    unsigned (*hash)(void *);
    ModoColision modo;
};

typedef struct _TablaHash *TablaHash;

TablaHash tablahash_crear(unsigned capacidad, void *(*copia)(void *), int (*comp)(void *, void *), void (*destr)(void *), unsigned (*hash)(void *), ModoColision modo) {
    TablaHash tabla = malloc(sizeof(struct _TablaHash));
    assert(tabla != NULL);
    tabla->elems = malloc(sizeof(CasillaHash) * capacidad);
    assert(tabla->elems != NULL);
    tabla->numElems = 0;
    tabla->capacidad = capacidad;
    tabla->copia = copia;
    tabla->comp = comp;
    tabla->destr = destr;
    tabla->hash = hash;
    tabla->modo = modo;

    for (unsigned idx = 0; idx < capacidad; ++idx) {
        tabla->elems[idx].cabeza = NULL;
    }

    return tabla;
}

int tablahash_nelems(TablaHash tabla) { return tabla->numElems; }

int tablahash_capacidad(TablaHash tabla) { return tabla->capacidad; }

void tablahash_destruir(TablaHash tabla) {
    for (unsigned idx = 0; idx < tabla->capacidad; ++idx) {
        Nodo *nodo = tabla->elems[idx].cabeza;
        while (nodo != NULL) {
            Nodo *temp = nodo;
            nodo = nodo->siguiente;
            tabla->destr(temp->dato);
            free(temp);
        }
    }
    free(tabla->elems);
    free(tabla);
}

void encadenamiento_insertar(TablaHash tabla, void *dato) {
    unsigned idx = tabla->hash(dato) % tabla->capacidad;

    Nodo *nodo = tabla->elems[idx].cabeza;
    while (nodo != NULL) {
        if (tabla->comp(nodo->dato, dato) == 0) {
            tabla->destr(nodo->dato);
            nodo->dato = tabla->copia(dato);
            return;
        }
        nodo = nodo->siguiente;
    }
    Nodo *nuevo_nodo = malloc(sizeof(Nodo));
    nuevo_nodo->dato = tabla->copia(dato);
    nuevo_nodo->siguiente = tabla->elems[idx].cabeza;
    tabla->elems[idx].cabeza = nuevo_nodo;
    tabla->numElems++;
}

void *encadenamiento_buscar(TablaHash tabla, void *dato) {
    unsigned idx = tabla->hash(dato) % tabla->capacidad;

    Nodo *nodo = tabla->elems[idx].cabeza;
    while (nodo != NULL) {
        if (tabla->comp(nodo->dato, dato) == 0) {
            return nodo->dato;
        }
        nodo = nodo->siguiente;
    }
    return NULL;
}

void encadenamiento_eliminar(TablaHash tabla, void *dato) {
    unsigned idx = tabla->hash(dato) % tabla->capacidad;

    Nodo *nodo = tabla->elems[idx].cabeza;
    Nodo *anterior = NULL;
    while (nodo != NULL) {
        if (tabla->comp(nodo->dato, dato) == 0) {
            if (anterior == NULL) {
                tabla->elems[idx].cabeza = nodo->siguiente;
            } else {
                anterior->siguiente = nodo->siguiente;
            }
            tabla->destr(nodo->dato);
            free(nodo);
            tabla->numElems--;
            return;
        }
        anterior = nodo;
        nodo = nodo->siguiente;
    }
}

typedef struct {
    char *nombre1;
    char *nombre2;
} ParAfinidad;

TablaHash *construir_afinidades(char *secuencia, unsigned capacidad, void *(*copia)(void *), int (*comp)(void *, void *), void (*destr)(void *), unsigned (*hash)(void *)) {
    TablaHash *tabla = tablahash_crear(capacidad, copia, comp, destr, hash, ENCANDENAMIENTO);

    char *token = strtok(secuencia, "{(, )}");
    while (token != NULL) {
        char *nombre1 = token;
        token = strtok(NULL, "{(, )}");
        char *nombre2 = token;

        ParAfinidad *par = malloc(sizeof(ParAfinidad));
        par->nombre1 = strdup(nombre1);
        par->nombre2 = strdup(nombre2);
        encadenamiento_insertar(tabla, par);

        token = strtok(NULL, "{(, )}");
    }

    return tabla;
}

typedef struct {
    Nodo *cabeza;
} HashSet;

HashSet *hashset_crear() {
    HashSet *set = malloc(sizeof(HashSet));
    set->cabeza = NULL;
    return set;
}

void hashset_insertar(HashSet *set, char *dato) {
    Nodo *nuevo_nodo = malloc(sizeof(Nodo));
    nuevo_nodo->dato = dato;
    nuevo_nodo->siguiente = set->cabeza;
    set->cabeza = nuevo_nodo;
}

int hashset_contiene(HashSet *set, char *dato) {
    Nodo *nodo = set->cabeza;
    while (nodo != NULL) {
        if (strcmp((char *)nodo->dato, dato) == 0) {
            return 1;
        }
        nodo = nodo->siguiente;
    }
    return 0;
}

unsigned hashset_nelems(HashSet *set) {
    unsigned count = 0;
    Nodo *nodo = set->cabeza;
    while (nodo != NULL) {
        count++;
        nodo = nodo->siguiente;
    }
    return count;
}

void hashset_destruir(HashSet *set) {
    Nodo *nodo = set->cabeza;
    while (nodo != NULL) {
        Nodo *temp = nodo;
        nodo = nodo->siguiente;
        free(temp);
    }
    free(set);
}

void dfs(TablaHash *tabla, char *nombre, HashSet *visitados, HashSet *conjunto) {
    if (hashset_contiene(visitados, nombre)) return;

    hashset_insertar(visitados, nombre);
    hashset_insertar(conjunto, nombre);

    Nodo *nodo = encadenamiento_buscar(tabla, nombre);
    while (nodo != NULL) {
        ParAfinidad *par = (ParAfinidad *)nodo->dato;
        if (strcmp(par->nombre1, nombre) == 0) {
            dfs(tabla, par->nombre2, visitados, conjunto);
        } else {
            dfs(tabla, par->nombre1, visitados, conjunto);
        }
        nodo = nodo->siguiente;
    }
}

HashSet *obtener_conjunto_maximal(TablaHash *tabla) {
    HashSet *visitados = hashset_crear();
    HashSet *conjunto_maximal = hashset_crear();

    for (unsigned i = 0; i < tabla->capacidad; ++i) {
        Nodo *nodo = tabla->elems[i].cabeza;
        while (nodo != NULL) {
            ParAfinidad *par = (ParAfinidad *)nodo->dato;
            if (!hashset_contiene(visitados, par->nombre1)) {
                HashSet *conjunto = hashset_crear();
                dfs(tabla, par->nombre1, visitados, conjunto);
                if (hashset_nelems(conjunto) > hashset_nelems(conjunto_maximal)) {
                    hashset_destruir(conjunto_maximal);
                    conjunto_maximal = conjunto;
                } else {
                    hashset_destruir(conjunto);
                }
            }
            nodo = nodo->siguiente;
        }
    }

    hashset_destruir(visitados);
    return conjunto_maximal;
}

int main() {
    // Ejemplo de uso
    char secuencia[] = "{(Juan Carlos, Luis Perez), (Luis Perez, Ana Oliva), (Juan Carlos, Roberto Muro), (Luis Perez, Roberto Muro), (Ana Olvia, Maria Luz)}";

    unsigned capacidad = 10;

    // Funciones para manejar los datos
    void *copiar_par(void *dato) {
        ParAfinidad *par = (ParAfinidad *)dato;
        ParAfinidad *nuevo_par = malloc(sizeof(ParAfinidad));
        nuevo_par->nombre1 = strdup(par->nombre1);
        nuevo_par->nombre2 = strdup(par->nombre2);
        return nuevo_par;
    }

    int comparar_par(void *dato1, void *dato2) {
        ParAfinidad *par1 = (ParAfinidad *)dato1;
        ParAfinidad *par2 = (ParAfinidad *)dato2;
        int cmp1 = strcmp(par1->nombre1, par2->nombre1);
        int cmp2 = strcmp(par1->nombre2, par2->nombre2);
        return (cmp1 == 0 && cmp2 == 0) ? 0 : 1;
    }

    void destruir_par(void *dato) {
        ParAfinidad *par = (ParAfinidad *)dato;
        free(par->nombre1);
        free(par->nombre2);
        free(par);
    }

    unsigned hash_par(void *dato) {
        ParAfinidad *par = (ParAfinidad *)dato;
        unsigned hash = 5381;
        char *str = par->nombre1;
        while (*str) {
            hash = ((hash << 5) + hash) + *str++;
        }
        str = par->nombre2;
        while (*str) {
            hash = ((hash << 5) + hash) + *str++;
        }
        return hash;
    }

    TablaHash *tabla = construir_afinidades(secuencia, capacidad, copiar_par, comparar_par, destruir_par, hash_par);

    HashSet *conjunto_maximal = obtener_conjunto_maximal(tabla);

    // Imprimir el conjunto maximal
    Nodo *nodo = conjunto_maximal->cabeza;
    printf("Conjunto maximal de afinidad:\n");
    while (nodo != NULL) {
        printf("%s\n", (char *)nodo->dato);
        nodo = nodo->siguiente;
    }

    // Liberar memoria
    tablahash_destruir(tabla);
    hashset_destruir(conjunto_maximal);

    return 0;
}
