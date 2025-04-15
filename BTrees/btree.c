#include "btree.h"
#include <assert.h>
#include <stdlib.h>

/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear() { 
  return NULL; 
}

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo) {
  if (nodo != NULL) {
    btree_destruir(nodo->left);
    btree_destruir(nodo->right);
    free(nodo);
  }
}

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo) { return nodo == NULL; }

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(int dato, BTree left, BTree right) {
  BTree nuevoNodo = malloc(sizeof(struct BTnodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->dato = dato;
  nuevoNodo->left = left;
  nuevoNodo->right = right;
  return nuevoNodo;
}

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */


void RECORRIDO_EN_ORDEN(BTree arbol, FuncionVisitante visit) {
  RECORRIDO_EN_ORDEN(arbol->left, visit);
  visit(arbol->dato);
  RECORRIDO_EN_ORDEN(arbol->right, visit);
}

void RECORRIDO_PRE_ORDEN(BTree arbol, FuncionVisitante visit) {
  visit(arbol->dato);
  RECORRIDO_PRE_ORDEN(arbol->left, visit);
  RECORRIDO_PRE_ORDEN(arbol->right, visit);
}

void RECORRIDO_POST_ORDEN(BTree arbol, FuncionVisitante visit) {
  RECORRIDO_POST_ORDEN(arbol->left, visit);
  RECORRIDO_POST_ORDEN(arbol->right, visit);
  visit(arbol->dato);
}

void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitante visit) {
  if (arbol == NULL) {
    return;
  }
  
  switch (orden)
  {
  case BTREE_RECORRIDO_IN:
    RECORRIDO_EN_ORDEN(arbol,visit);
    break;
  case BTREE_RECORRIDO_PRE:
    RECORRIDO_PRE_ORDEN(arbol,visit);
    break;
  case BTREE_RECORRIDO_POST:
    RECORRIDO_POST_ORDEN(arbol,visit);
    break;

  default:
    break;
  }
  assert(0);
  return;
}

int btree_nnodos(BTree arbol) {
  if (arbol == NULL) {
    return 0;
  }
  return 1 + btree_nnodos(arbol->left) + btree_nnodos(arbol->right);
}

int btree_buscar(BTree arbol, int dato) {
  if (arbol== NULL) {
    return 0;
  }
  if (arbol->dato == dato) {
    return 1;
  }
  if (btree_buscar(arbol->left, dato)== 1) {
    return 1;
  }
  return btree_buscar(arbol->right, dato);
}

BTree copiarNodo(BTree nodo) {
    if (nodo == NULL) return NULL;
    return btree_unir(nodo->dato, copiarNodo(nodo->left), copiarNodo(nodo->right));
}

BTree btree_copiar(BTree arbol) {
    if (arbol == NULL) return NULL;
    return copiarNodo(arbol);
}

int btree_altura(BTree arbol) {
  int alturaIZQ = btree_altura(arbol->left);
  int alturaDER = btree_altura(arbol->right);
  if (arbol == NULL) {
    return 0;
  }
  return 1 + (alturaIZQ > alturaDER ? alturaIZQ: alturaDER);
}

int btree_nnodos_profundidad(BTree arbol, int profundidad) {
  if (arbol == NULL){
    return 0;
  }
  if (profundidad == 0) {
    return 1;
  }
  return btree_nnodos_profundidad(arbol->left,profundidad-1) +  btree_nnodos_profundidad(arbol->right,profundidad-1) 
}

int btree_profundidad_aux(BTree arbol, int dato, int profundidadActual) {
    if (arbol == NULL) {
        return -1;
    }
    if (arbol->dato == dato) {
        return profundidadActual;
    }
    int profundidadIzquierda = btree_profundidad_aux(arbol->left, dato, profundidadActual++);
    if (profundidadIzquierda != -1) {
        return profundidadIzquierda;
    }
    return btree_profundidad_aux(arbol->right, dato, profundidadActual++);
}

int btree_profundidad(BTree arbol, int dato) {
    return btree_profundidad_aux(arbol, dato, 0);
}

int btree_sumar(BTree arbol) {
  if (arbol == NULL)
  {
    return 0;
  }
  return arbol->dato + btree_sumar(arbol->left)+ btree_sumar(arbol->right);
}


void RECORRIDO_EN_ORDEN_EXTRA(BTree arbol, FuncionVisitanteExtra visit, void *extra) {
    if (arbol == NULL) return;
    RECORRIDO_EN_ORDEN_EXTRA(arbol->left, visit, extra);
    visit(arbol->dato, extra);
    RECORRIDO_EN_ORDEN_EXTRA(arbol->right, visit, extra);
}

void RECORRIDO_PRE_ORDEN_EXTRA(BTree arbol, FuncionVisitanteExtra visit, void *extra) {
    if (arbol == NULL) return;
    visit(arbol->dato, extra);
    RECORRIDO_PRE_ORDEN_EXTRA(arbol->left, visit, extra);
    RECORRIDO_PRE_ORDEN_EXTRA(arbol->right, visit, extra);
}

void RECORRIDO_POST_ORDEN_EXTRA(BTree arbol, FuncionVisitanteExtra visit, void *extra) {
    if (arbol == NULL) return;
    RECORRIDO_POST_ORDEN_EXTRA(arbol->left, visit, extra);
    RECORRIDO_POST_ORDEN_EXTRA(arbol->right, visit, extra);
    visit(arbol->dato, extra);
}
// Función principal para recorrer el árbol con función extra
void btree_recorrer_extra(BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitanteExtra visit, void *extra) {
    if (arbol == NULL) {
        return;
    }
    switch (orden) {
        case BTREE_RECORRIDO_IN:
            RECORRIDO_EN_ORDEN_EXTRA(arbol, visit, extra);
            break;
        case BTREE_RECORRIDO_PRE:
            RECORRIDO_PRE_ORDEN_EXTRA(arbol, visit, extra);
            break;
        case BTREE_RECORRIDO_POST:
            RECORRIDO_POST_ORDEN_EXTRA(arbol, visit, extra);
            break;
        default:
            assert(0); // No debería llegar aquí
    }
}

int BST_iterative(BTree arbol, int value) {
    int res = NULL;
    BTree cpy = arbol;
    if (!btree_empty(cpy)) {
        while (!btree_empty(cpy) && (cpy->dato!= value)) {
            if (cpy->dato > value) {
                cpy = cpy->left;
            }
            if (cpy->dato < value) {
                cpy = cpy->right;
            }
        }
        if (!btree_empty(cpy) && (cpy->right != NULL)) {
            res = cpy->right->dato;
        }
    }
    return res;
}

int BST_recursive(BTree arbol, int value) {
    if (arbol == NULL) {
        return 0;
    }
    if (arbol->dato < value){
        return BST_recursive(arbol->right, value);
    }
    if (arbol->dato > value){
        return BST_recursive(arbol->left, value);
    }
    else return 1;
}


void imprimir_dato(int val) {
  printf("%d, ", val);
}