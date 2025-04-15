#include <stdio.h>
#include <stdlib.h>
#include "btree.h"


int altura(AVLT_Nodo *node) {
    if (node == NULL) {
        return 0;
    }
    return node->altura;
}

int maximo(int a, int b) {
    return a>b? a:b;
}


AVTree rotarDerecha(AVTree arbol) {
    AVTree temp = arbol->izq;
    AVTree temp2 = temp->der;

    //rotacion
    temp->der = arbol;
    arbol->izq = temp2;

    //update height
    arbol->altura = maximo(altura(arbol->izq),altura(arbol->der)) + 1;
    temp->altura = maximo(altura(temp->izq),altura(temp->der)) + 1;

    return temp;
}

AVTree rotarIzquierda(AVTree arbol) {
    AVTree temp = arbol->der;
    AVTree temp2 = temp->izq;

    //rotacion
    temp->izq = arbol;
    arbol->der = temp2;

    //update height
    arbol->altura = maximo(altura(arbol->izq),altura(arbol->der)) + 1;
    temp->altura = maximo(altura(temp->izq),altura(temp->der)) + 1;

    return temp;
}