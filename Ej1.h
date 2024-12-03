#ifndef __BTREE_H__
#define __BTREE_H__

typedef enum Color {Rojo, Azul, Neutro} Color;

typedef struct Nodo_ {
    char * cdato;
    Color colorNodo;
    struct Nodo_ *der, *izq;
}Nodo;

typedef Nodo* ArbolBinarioColoreado;

void color_auxiliar(ArbolBinarioColoreado inicio, int* color_r, int* color_a);

Color color(ArbolBinarioColoreado inicio);

void hojas_puras_auxiliar(Nodo* inicio, Color color_ancestros, int* contador);

int CantidadPuras(ArbolBinarioColoreado inicio);

#endif /* __BTREE_H__ */
