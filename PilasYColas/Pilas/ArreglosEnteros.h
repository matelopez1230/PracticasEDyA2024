#ifndef ARREGLOS_ENTEROS_H
#define ARREGLOS_ENTEROS_H

// Definición de la estructura ArregloEnteros que representa un arreglo dinámico de enteros
typedef struct {
    int* direccion; 
    int capacidad; 
} ArregloEnteros;

// Función para crear un arreglo de enteros con la capacidad especificada
// Parámetros:
// - capacidad: entero que representa la capacidad máxima del arreglo a crear
// Retorna:
// - Puntero a la estructura ArregloEnteros creada
ArregloEnteros *crear_arreglo_enteros(int capacidad);

// Función para liberar la memoria asignada a un arreglo de enteros
// Parámetros:
// - arr: puntero al arreglo de enteros que se va a destruir
void destruir_arreglos_enteros(ArregloEnteros *arr);

// Función para leer un elemento del arreglo de enteros en una posición específica
// Parámetros:
// - arr: puntero al arreglo de enteros del cual se va a leer el dato
// - pos: entero que representa la posición del dato que se desea leer
// Retorna:
// - El valor del dato en la posición especificada, o -1 si hay un error
int leer_arreglos_enteros(ArregloEnteros *arr, int pos);

// Función para escribir un dato en una posición específica del arreglo de enteros
// Parámetros:
// - arr: puntero al arreglo de enteros en el cual se va a escribir el dato
// - pos: entero que representa la posición donde se va a escribir el dato
// - dato: entero que representa el valor que se va a escribir en la posición especificada
void escribir_arreglos_enteros(ArregloEnteros *arr, int pos, int dato) ;

// Función para obtener la capacidad máxima del arreglo de enteros
// Parámetros:
// - arr: puntero al arreglo de enteros del cual se va a obtener la capacidad
// Retorna:
// - La capacidad máxima del arreglo de enteros
int capacidad_arreglos_enteros(ArregloEnteros *arr);

// Función para imprimir todos los elementos del arreglo de enteros
// Parámetros:
// - arr: puntero al arreglo de enteros que se va a imprimir
void imprimir_arreglos_enteros(ArregloEnteros *arr);

void arreglo_enteros_ajustar(ArregloEnteros* arreglo, int nueva_capacidad);

#endif /* ARREGLOS_ENTEROS_H */