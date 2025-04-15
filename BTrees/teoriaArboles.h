#ifndef _ARNOLES_H_
#define _ARBOLES_H_

/*
Un arbol se define como una coleccion de nodos organizados
de manera recursiva

cuando hay 0 (cero) nodos se dice que el arbol está vacío,
en caso contrario el árbol consiste en un nodo denominado raíz,
el cual tiene 0 (cero) o más referencias a otros árboles,
conocidos como subarboles. Las raíces de los subarboles se 
denominan hijos de la raíz, y consecuentemente la raíz se denomina
padre de las raíces de sus subárboles.


Los nodos que no poseen hijos se denominan hojas. 
Dos nodos que tienen el padre en común se denominan hermanos

Análogamente al concepto de árbol genealógico, podemos
definir el concepto de ancestro y descendiente pero, para esto,
necesitamos, previamente, darle forma a algunas ideas:

Un camíno entre un nodo n_1 y un nodo n_k está definido como
la secuencia de todos los nodos n_1,n_2...n_k tal que n_i es padre
de n_i+1 <= i < k.

El largo del camino es el número de referencias que componen
el camino.


convenimos que existe un camino desde cada nodo del arbol a si
mismo y es de largo 0 (cero)

Una caracteristica de los arboles que es que existe un UNICO
camino desde la raiz hasta cualquier otro nodo del arbol.

Ahora si podemos definir los conceptos de ancestro y descendiente:
un nodo n es ancestro de un nodo m si existe un camino desde n a m;
un nodo es descendiente de un nodo m si existe un camino desde m a n;

se define la profundidad del nodo n_K como el largo del camino
entre la raiz del arbol y el nodo n_K. Esto implica que la 
profundidad de la raiz es siempre 0 (cero)

La altura de un nodo n_k es el maximo largo de camino desde n_k 
hasta alguna hoja. Esto implica que la altura de toda hoja es 0 (cero)

La altura de un arbol es igual a la altura de la raiz, y tiene
el mismo valor que la profundidad de la hoja más profunda.
La altura de un arbol vacio se define como -1.


ARBOLES BINARIOS:

Un arbol binario es un arbol en donde cada nodo posee exactamente 2
referencias a subarboles. En general, dichas referencias se denominan
izquierda y derecha, y consecuentemente se define el subarbol
izquiero y el sibarbol derecho del arbol 
*/

typedef struct _BTNode {
    int value;
    struct _BTNode *left;
    struct _BTNode *right;      /*La estructura se define*/
}BTNode;

typedef BTNode *BTree;

/*
vemos que, en este caso, la informacion a almacenar
es un entero y tengo dos punteros, uno al subarbol 
izquierdo y otro al derecho.


Un arbol binario de altura K esta completo si esta lleno hasta 
la altura k-1, es decir, cada nodo tiene sus dos hijos y, el último
nivel esta ocupado de izquierda a derecha.


Los nodos en si que confirman un arbol binario se denominan nodos
internos, y todas las referencias que son NULL las llamamos nodos 
Externos.

*/

#endif /*_ARBOLES_H_*/