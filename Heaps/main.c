#include <stdio.h>
#include "heaps.c"
#include <stdlib.h>


int main() {
    srand(time(NULL));
    int largo = 10000;
    int **arr = (int **)malloc(sizeof(int *) * largo);

    for (int i = 0; i < largo; i++) {
        arr[i] = (int *)malloc(sizeof(int));
        *arr[i] = rand() % largo;
    }

    printf("Arreglo original:\n");
    printArray((void **)arr, largo);

    heapSort((void **)arr, largo, compare);

    printf("Despues de heapSort:\n");
    printArray((void **)arr, largo);

    for (int i = 0; i < largo; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}

