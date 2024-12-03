#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PERSONAS 100
#define MAX_NOMBRE 50

typedef struct {
    int adyacencia[MAX_PERSONAS][MAX_PERSONAS];
    char personas[MAX_PERSONAS][MAX_NOMBRE];
    int cantidadPersonas;
} MatrizAdyacencia;

// Inicializa la matriz de adyacencia
void inicializarMatriz(MatrizAdyacencia *matriz) {
    matriz->cantidadPersonas = 0;
    for (int i = 0; i < MAX_PERSONAS; i++) {
        for (int j = 0; j < MAX_PERSONAS; j++) {
            matriz->adyacencia[i][j] = 0;
        }
    }
}

// Agrega una persona a la matriz de adyacencia y retorna su índice
int agregarPersona(MatrizAdyacencia *matriz, const char *nombre) {
    for (int i = 0; i < matriz->cantidadPersonas; i++) {
        if (strcmp(matriz->personas[i], nombre) == 0) {
            return i;
        }
    }
    strcpy(matriz->personas[matriz->cantidadPersonas], nombre);
    return matriz->cantidadPersonas++;
}

// Agrega una relación de afinidad a la matriz de adyacencia
void agregarAfinidad(MatrizAdyacencia *matriz, const char *persona1, const char *persona2) {
    int index1 = agregarPersona(matriz, persona1);
    int index2 = agregarPersona(matriz, persona2);
    matriz->adyacencia[index1][index2] = 1;
    matriz->adyacencia[index2][index1] = 1;
}

// Verifica si todos los elementos del conjunto son afines entre sí
int esConjuntoAfinidad(const MatrizAdyacencia *matriz, const int *conjunto, int tamañoConjunto) {
    for (int i = 0; i < tamañoConjunto; i++) {
        for (int j = i + 1; j < tamañoConjunto; j++) {
            if (matriz->adyacencia[conjunto[i]][conjunto[j]] == 0) {
                return 0;
            }
        }
    }
    return 1;
}

// Encuentra el conjunto maximal de afinidad
void encontrarConjuntoMaximal(const MatrizAdyacencia *matriz) {
    int mejorConjunto[MAX_PERSONAS];
    int mejorTamaño = 0;

    // Iterar sobre todos los subconjuntos posibles
    int totalSubconjuntos = 1 << matriz->cantidadPersonas;
    for (int i = 0; i < totalSubconjuntos; i++) {
        int conjuntoActual[MAX_PERSONAS];
        int tamañoConjuntoActual = 0;

        // Construir el conjunto actual
        for (int j = 0; j < matriz->cantidadPersonas; j++) {
            if (i & (1 << j)) {
                conjuntoActual[tamañoConjuntoActual++] = j;
            }
        }

        // Verificar si el conjunto actual es una afinidad completa
        if (tamañoConjuntoActual > mejorTamaño && esConjuntoAfinidad(matriz, conjuntoActual, tamañoConjuntoActual)) {
            memcpy(mejorConjunto, conjuntoActual, sizeof(int) * tamañoConjuntoActual);
            mejorTamaño = tamañoConjuntoActual;
        }
    }

    // Imprimir el conjunto maximal de afinidad
    printf("Conjunto maximal de afinidad:\n");
    for (int i = 0; i < mejorTamaño; i++) {
        printf("%s\n", matriz->personas[mejorConjunto[i]]);
    }
}

// Función para construir la estructura de datos a partir de una cadena
void construirMatrizDesdeCadena(MatrizAdyacencia *matriz, const char *cadena) {
    char persona1[MAX_NOMBRE], persona2[MAX_NOMBRE];
    const char *p = cadena;
    
    while (sscanf(p, "(%[^,], %[^)])", persona1, persona2) == 2) {
        agregarAfinidad(matriz, persona1, persona2);
        p = strchr(p, ')') + 1;
        while (*p == ' ' || *p == ',') p++;
    }
}

int main() {
    MatrizAdyacencia matriz;
    inicializarMatriz(&matriz);

    const char *cadena_afinidad = "(Juan Carlos, Luis Perez), (Luis Perez, Ana Oliva), (Juan Carlos, Roberto Muro), (Luis Perez, Roberto Muro), (Ana Oliva, Maria Luz)";
    
    construirMatrizDesdeCadena(&matriz, cadena_afinidad);

    encontrarConjuntoMaximal(&matriz);

    return 0;
}
