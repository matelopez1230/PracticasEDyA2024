#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArreglosEnteros.h"



ArregloEnteros *crear_arreglo_enteros(int capacidad) {
    ArregloEnteros *arr = malloc(sizeof(ArregloEnteros)); // Asigna memoria para la estructura
    arr->capacidad = capacidad; // Asigna la capacidad al arreglo
    arr->direccion = malloc(sizeof(int) * capacidad); // Asigna memoria para almacenar los enteros
    return arr; // Retorna el puntero al arreglo creado
}


void destruir_arreglos_enteros(ArregloEnteros *arr) {
    if (arr != NULL) { // Verifica si el arreglo existe
        free(arr->direccion); // Libera la memoria asignada para los enteros
        arr->direccion = NULL; // Asigna NULL al puntero de dirección para evitar errores
        free(arr); // Libera la memoria asignada para la estructura del arreglo
    }
}


int leer_arreglos_enteros(ArregloEnteros *arr, int pos) {
    if (arr == NULL || arr->direccion == NULL || pos < 0 || pos >= arr->capacidad) {
        return -1; // Retorna -1 si hay un error en los parámetros o la posición está fuera de rango
    }
    return arr->direccion[pos]; // Retorna el valor del dato en la posición especificada
}


void escribir_arreglos_enteros(ArregloEnteros *arr, int pos, int dato) {
    arr->direccion[pos] = dato; // Asigna el valor del dato en la posición especificada
}


int capacidad_arreglos_enteros(ArregloEnteros *arr) {
    return arr->capacidad; // Retorna la capacidad del arreglo
}


void imprimir_arreglos_enteros(ArregloEnteros *arr) {
    for (int i = 0; i < arr->capacidad; i++) { // Itera sobre cada elemento del arreglo
        printf("%d, ", arr->direccion[i]); // Imprime el elemento
    }
    printf("\n"); // Imprime un salto de línea al final
}

void arreglo_enteros_ajustar(ArregloEnteros* arreglo, int nueva_capacidad) {
    int* nuevo_direccion = realloc(arreglo->direccion, sizeof(int) * nueva_capacidad);// Reasignar memoria para el arreglo con la nueva capacidad

    if (nueva_capacidad == arreglo->capacidad) {
        return; // Si la nueva capacidad es igual a la capacidad actual, no hay nada que hacer
    }
    if (nueva_capacidad < arreglo->capacidad) {
        // Si la nueva capacidad es menor que la capacidad actual, se trunca el contenido
        arreglo->capacidad = nueva_capacidad; // Actualiza la capacidad del arreglo
    }

    arreglo->direccion = nuevo_direccion; // Actualiza el puntero de dirección del arreglo
}
