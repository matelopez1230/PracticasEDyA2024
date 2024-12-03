#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int numero;
    int cantidadMenores;
} Elemento;

typedef struct {
    Elemento *elementos;
    int tamaño;
    int capacidad;
} Secuencia;

void inicializarSecuencia(Secuencia *seq, int capacidadInicial) {
    seq->elementos = (Elemento *)malloc(sizeof(Elemento) * capacidadInicial);
    seq->tamaño = 0;
    seq->capacidad = capacidadInicial;
}

void redimensionarSecuencia(Secuencia *seq) {
    seq->capacidad *= 2;
    seq->elementos = (Elemento *)realloc(seq->elementos, sizeof(Elemento) * seq->capacidad);
}

void insertarEnPosicion(Secuencia *seq, int numero, int posicion) {
    if (seq->tamaño == seq->capacidad) {
        redimensionarSecuencia(seq);
    }

    int cantidadMenores = 0;
    for (int i = 0; i < posicion; i++) {
        if (seq->elementos[i].numero < numero) {
            cantidadMenores++;
        }
    }

    for (int i = seq->tamaño; i > posicion; i--) {
        seq->elementos[i] = seq->elementos[i - 1];
    }

    seq->elementos[posicion].numero = numero;
    seq->elementos[posicion].cantidadMenores = cantidadMenores;
    seq->tamaño++;

    for (int i = posicion + 1; i < seq->tamaño; i++) {
        if (seq->elementos[i].numero > numero) {
            seq->elementos[i].cantidadMenores++;
        }
    }
}

void borrarEnPosicion(Secuencia *seq, int posicion) {
    if (posicion < 0 || posicion >= seq->tamaño) {
        return;
    }

    int numeroEliminado = seq->elementos[posicion].numero;

    for (int i = posicion; i < seq->tamaño - 1; i++) {
        seq->elementos[i] = seq->elementos[i + 1];
    }

    seq->tamaño--;

    for (int i = posicion; i < seq->tamaño; i++) {
        if (seq->elementos[i].numero > numeroEliminado) {
            seq->elementos[i].cantidadMenores--;
        }
    }
}

Elemento *buscarPorCantidadMenores(Secuencia *seq, int cantidad, int *resultadoTamaño) {
    Elemento *resultado = (Elemento *)malloc(sizeof(Elemento) * seq->tamaño);
    *resultadoTamaño = 0;

    for (int i = 0; i < seq->tamaño; i++) {
        if (seq->elementos[i].cantidadMenores == cantidad) {
            resultado[*resultadoTamaño] = seq->elementos[i];
            (*resultadoTamaño)++;
        }
    }

    return resultado;
}

int compararPorCantidadMenores(const void *a, const void *b) {
    Elemento *elementoA = (Elemento *)a;
    Elemento *elementoB = (Elemento *)b;
    return (elementoA->cantidadMenores - elementoB->cantidadMenores);
}

void ordenarPorCantidadMenores(Secuencia *seq) {
    qsort(seq->elementos, seq->tamaño, sizeof(Elemento), compararPorCantidadMenores);
}

void imprimirSecuencia(Secuencia *seq) {
    for (int i = 0; i < seq->tamaño; i++) {
        printf("(%d, %d) ", seq->elementos[i].numero, seq->elementos[i].cantidadMenores);
    }
    printf("\n");
}

void liberarSecuencia(Secuencia *seq) {
    free(seq->elementos);
}

int main() {
    Secuencia seq;
    inicializarSecuencia(&seq, 4);

    insertarEnPosicion(&seq, 12, 0);
    insertarEnPosicion(&seq, 30, 1);
    insertarEnPosicion(&seq, 1, 2);
    insertarEnPosicion(&seq, 2, 3);

    imprimirSecuencia(&seq);
    // Output esperado: (12, 0) (30, 1) (1, 0) (2, 1)

    int resultadoTamaño;
    Elemento *resultado = buscarPorCantidadMenores(&seq, 1, &resultadoTamaño);
    for (int i = 0; i < resultadoTamaño; i++) {
        printf("(%d, %d) ", resultado[i].numero, resultado[i].cantidadMenores);
    }
    printf("\n");
    // Output esperado: (30, 1) (2, 1)

    free(resultado);

    borrarEnPosicion(&seq, 1);
    imprimirSecuencia(&seq);
    // Output esperado: (12, 0) (1, 0) (2, 1)

    ordenarPorCantidadMenores(&seq);
    imprimirSecuencia(&seq);
    // Output esperado: (12, 0) (1, 0) (2, 1)

    liberarSecuencia(&seq);
    return 0;
}