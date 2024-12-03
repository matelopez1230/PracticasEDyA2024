#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Ej1.h"

void color_auxiliar(ArbolBinarioColoreado inicio, int* color_r, int* color_a){
    if (inicio == NULL) {
        return;
    }
    if (inicio->colorNodo == Rojo) {
        *color_r += 1;
    }
    if (inicio->colorNodo == Azul) {
        *color_a += 1;
    }
    color_auxiliar(inicio->izq,color_r,color_a);
    color_auxiliar(inicio->der,color_r,color_a);
    return;
}

Color color(ArbolBinarioColoreado inicio) {
    int color_r = 0;
    int color_a = 0;
    color_auxiliar(inicio, &color_r,&color_a);

    if (color_r ==color_a) {
        return Neutro;
    }
    if (color_r < color_a) {
        return Azul;
    }
    if (color_r > color_a) {
        return Rojo;
    }
    return 0;
}

void hojas_puras_auxiliar(Nodo* inicio, Color color_ancestros, int* contador) {
    if (inicio == NULL) {
        return;
    }

    if (inicio->izq == NULL && inicio->der == NULL) {
        if (inicio->colorNodo == color_ancestros) {
            *contador += 1;
        }
        return;
    }

    if (inicio->colorNodo == color_ancestros) {
        hojas_puras_auxiliar(inicio->izq, color_ancestros, contador);
        hojas_puras_auxiliar(inicio->der, color_ancestros, contador);
    }
}


int CantidadPuras(ArbolBinarioColoreado inicio) {
    if (inicio == NULL) {
        return 0;
    }
    int* contador = malloc(sizeof(int));
    *contador = 0;
    hojas_puras_auxiliar(inicio, inicio->colorNodo, contador);
    int resultado = *contador;
    free(contador);
    return resultado;
}

int main() {
    Nodo hoja1 = { "Hoja1", Azul, NULL, NULL };
    Nodo hoja2 = { "Hoja2", Azul, NULL, NULL };
    Nodo hoja3 = { "Hoja3", Rojo, NULL, NULL };
    Nodo hoja4 = { "Hoja4", Azul, NULL, NULL };

    Nodo nodoIntermedio1 = { "NodoIntermedio1", Azul, &hoja1, &hoja2 };
    Nodo nodoIntermedio2 = { "NodoIntermedio2", Rojo, &hoja3, &hoja4 };
    Nodo raiz = { "Raiz", Azul, &nodoIntermedio1, &nodoIntermedio2 };

    ArbolBinarioColoreado arbol = &raiz;

    Color c = color(arbol);
    printf("Color del arbol: ");
    switch (c) {
        case Rojo: printf("Rojo\n"); break;
        case Azul: printf("Azul\n"); break;
        case Neutro: printf("Neutro\n"); break;
    }
    int puras = CantidadPuras(arbol);
    printf("Cantidad de hojas puras: %d\n", puras);


    hoja1.colorNodo = Rojo;  
    puras = CantidadPuras(arbol);
    printf("Cantidad de hojas puras (despues de cambiar Hoja1 a Rojo): %d\n", puras);

    raiz.colorNodo = Rojo;
    c = color(arbol);
    printf("Color del arbol (despues de cambiar la raiz a Rojo): ");
    switch (c) {
        case Rojo: printf("Rojo\n"); break;
        case Azul: printf("Azul\n"); break;
        case Neutro: printf("Neutro\n"); break;
    }

    puras = CantidadPuras(arbol);
    printf("Cantidad de hojas puras (despues de cambiar la raiz a Rojo): %d\n", puras);

    return 0;
}