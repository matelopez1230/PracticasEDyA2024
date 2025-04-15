#ifndef _AVL_H_
#define _AVL_H_

typedef void *(*FuncionCopiadora)(void *dato);
typedef int (*FuncionComparadora)(void *, void *);
typedef void (*FuncionDestructora)(void *dato);
typedef void (*FuncionVisitanteExtra)(void *dato, void *extra);

typedef enum {
  BTREE_RECORRIDO_IN,  /** Inorden */
  BTREE_RECORRIDO_PRE, /** Preorden */
  BTREE_RECORRIDO_POST /** Postorden */
} BSTreeRecorrido;

typedef struct AVLTree {
  void *dato;
  struct AVLTree *izq, *der;
  int altura;
} AVLT_Nodo;

typedef struct AVLTree *AVTree;
#endif //_AVL_H_