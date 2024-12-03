#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char persona1[50];
    char persona2[50];
}ParAfinidad;

typedef struct {
    ParAfinidad *pares;
    int cantidad;
}ConjuntoAfinidad;


void InicializarConjuntoAfinidad(ConjuntoAfinidad *set){
    set->pares = NULL;
    set->cantidad = 0;
}

void agregarParAfinidad(ConjuntoAfinidad *set, const char *p1,const char *p2) {
    set->pares = realloc(set->pares, (set->cantidad +1) *sizeof(ParAfinidad));
    strcpy(set->pares[set->cantidad].persona1 = p1);
    strcpy(set->pares[set->cantidad].persona2 = p2);
    set->cantidad++;
}

void LiberarConjuntoAfinidad(ConjuntoAfinidad *set) {
    free(set->pares);
}

/*
Punto B
*/

typedef struct {
    char **personas;
    int cantidad;
}ConjuntoAfinidadMaxima;


void InicializarConjuntoMaximal(ConjuntoAfinidadMaxima *set) {
    set->personas = NULL;
    set->cantidad = 0;  
}

void AgregarPersonasAfinidadMaximal(ConjuntoAfinidadMaxima *set, const char *persona) {
    set->personas = realloc(set->personas, (set->cantidad + 1) * sizeof(char*));
    set->personas[set->cantidad] = malloc(strlen(persona) + 1);
    strcpy(set->personas[set->cantidad], persona);
    set->cantidad++;
}

void LiberarConjuntoMaximal(ConjuntoAfinidadMaxima *set) {
    for (int i = 0; i < set->cantidad; i++) {
        free(set->personas[i]);
    }
    free(set->personas);
}

/*
 Punto C
 */

void ConstruirAfinidad(ConjuntoAfinidad *set, const char *cadena) {
    char * cadenaCopia = strup(cadena);
    char *par = strtok(cadenaCopia,"),");

    while(par != NULL){
        char persona1[50],persona2[50];
        sscanf(par,"(%[^,],%[^)])",persona1,persona2);
        agregarParAfinidad(set,persona1,persona2);
        par = strtok(NULL, "),");
    }
    free(cadenaCopia);
}

/*
 Punto D
*/

int sonAfines(ParAfinidad *pares, int cantidad, const char *persona1, const char *persona2) {
    for (int i = 0; i < cantidad; i++) {
        if ((strcmp(pares[i].persona1, persona1) == 0 && strcmp(pares[i].persona2, persona2) == 0) ||
            (strcmp(pares[i].persona1, persona2) == 0 && strcmp(pares[i].persona2, persona1) == 0)) {
            return 1;
        }
    }
    return 0;
}

void encontrarConjuntoMaximal(ConjuntoAfinidad *afinidad, ConjuntoAfinidadMaximal *maximal) {
    for (int i = 0; i < afinidad->cantidad; i++) {
        int esAfineConTodos = 1;
        for (int j = 0; j < maximal->cantidad; j++) {
            if (!sonAfines(afinidad->pares, afinidad->cantidad, maximal->personas[j], afinidad->pares[i].persona1) ||
                !sonAfines(afinidad->pares, afinidad->cantidad, maximal->personas[j], afinidad->pares[i].persona2)) {
                esAfineConTodos = 0;
                break;
            }
        }
        if (esAfineConTodos) {
            agregarPersonaAfinidadMaximal(maximal, afinidad->pares[i].persona1);
            agregarPersonaAfinidadMaximal(maximal, afinidad->pares[i].persona2);
        }
    }
}


int main() {
    ConjuntoAfinidad afinidad;
    inicializarConjuntoAfinidad(&afinidad);

    const char *cadena_afinidad = "(Juan Carlos, Luis Perez), (Luis Perez, Ana Oliva), (Juan Carlos, Roberto Muro), (Luis Perez, Roberto Muro), (Ana Oliva, Maria Luz)";
    construirAfinidad(&afinidad, cadena_afinidad);

    ConjuntoAfinidadMaxima conjuntoMaximal;
    inicializarConjuntoMaximal(&conjuntoMaximal);

    encontrarConjuntoMaximal(&afinidad, &conjuntoMaximal);

    printf("Conjunto maximal de afinidad:\n");
    for (int i = 0; i < conjuntoMaximal.cantidad; i++) {
        printf("%s\n", conjuntoMaximal.personas[i]);
    }

    liberarConjuntoAfinidad(&afinidad);
    liberarConjuntoMaximal(&conjuntoMaximal);

    return 0;
}