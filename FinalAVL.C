#include <stdio.h>
#include <stdlib.h>

// Definición del nodo del árbol AVL
typedef struct _Node {
    int valor;
    int cantidadMenores;
    int altura;
    struct _Node* izq;
    struct _Node* der;
} Node;

// Función para obtener la altura de un nodo
int height(Node* n) {
    if (n == NULL) return 0;
    return n->altura;
}

// Función para obtener el máximo de dos enteros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Función para obtener el factor de balance de un nodo
int getBalance(Node* n) {
    if (n == NULL) return 0;
    return height(n->izq) - height(n->der);
}

// Rotación hacia la derecha
Node* rightRotate(Node* y) {
    Node* x = y->izq;
    Node* T2 = x->der;

    x->der = y;
    y->izq = T2;

    y->altura = max(height(y->izq), height(y->der)) + 1;
    x->altura = max(height(x->izq), height(x->der)) + 1;

    return x;
}

// Rotación hacia la izquierda
Node* leftRotate(Node* x) {
    Node* y = x->der;
    Node* T2 = y->izq;

    y->izq = x;
    x->der = T2;

    x->altura = max(height(x->izq), height(x->der)) + 1;
    y->altura = max(height(y->izq), height(y->der)) + 1;

    return y;
}

// Crear un nuevo nodo
Node* createNode(int value, int cantidadMenores) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->valor = value;
    node->cantidadMenores = cantidadMenores;
    node->altura = 1;  // nuevo nodo es inicialmente una hoja
    node->izq = NULL;
    node->der = NULL;
    return node;
}

// Insertar un nodo en el árbol AVL
Node* insert(Node* node, int value, int* cantidadMenores) {
    if (node == NULL)
        return createNode(value, *cantidadMenores);

    if (value < node->valor) {
        node->izq = insert(node->izq, value, cantidadMenores);
    } else if (value > node->valor) {
        *cantidadMenores += 1 + (node->izq ? node->izq->cantidadMenores : 0);
        node->der = insert(node->der, value, cantidadMenores);
    } else {
        return node;  // No se permiten valores duplicados
    }

    node->altura = 1 + max(height(node->izq), height(node->der));

    int balance = getBalance(node);

    if (balance > 1 && value < node->izq->valor)
        return rightRotate(node);

    if (balance < -1 && value > node->der->valor)
        return leftRotate(node);

    if (balance > 1 && value > node->izq->valor) {
        node->izq = leftRotate(node->izq);
        return rightRotate(node);
    }

    if (balance < -1 && value < node->der->valor) {
        node->der = rightRotate(node->der);
        return leftRotate(node);
    }

    return node;
}

// Encontrar el nodo con el valor mínimo en un árbol
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->izq != NULL)
        current = current->izq;
    return current;
}

// Eliminar un nodo del árbol AVL
Node* deleteNode(Node* root, int value) {
    if (root == NULL)
        return root;

    if (value < root->valor)
        root->izq = deleteNode(root->izq, value);
    else if (value > root->valor)
        root->der = deleteNode(root->der, value);
    else {
        if ((root->izq == NULL) || (root->der == NULL)) {
            Node* temp = root->izq ? root->izq : root->der;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;

            free(temp);
        } else {
            Node* temp = minValueNode(root->der);
            root->valor = temp->valor;
            root->cantidadMenores = temp->cantidadMenores;
            root->der = deleteNode(root->der, temp->valor);
        }
    }

    if (root == NULL)
        return root;

    root->altura = 1 + max(height(root->izq), height(root->der));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->izq) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->izq) < 0) {
        root->izq = leftRotate(root->izq);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->der) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->der) > 0) {
        root->der = rightRotate(root->der);
        return leftRotate(root);
    }

    return root;
}

// Buscar elementos por cantidadMenores
void searchByCantidadMenores(Node* root, int cantidadMenores, int* results, int* count) {
    if (root != NULL) {
        searchByCantidadMenores(root->izq, cantidadMenores, results, count);
        if (root->cantidadMenores == cantidadMenores) {
            results[*count] = root->valor;
            (*count)++;
        }
        searchByCantidadMenores(root->der, cantidadMenores, results, count);
    }
}

// Recorrer el árbol en orden
void inOrder(Node* root, int* results, int* index) {
    if (root != NULL) {
        inOrder(root->izq, results, index);
        results[*index] = root->valor;
        (*index)++;
        inOrder(root->der, results, index);
    }
}

int main() {
    Node* root = NULL;
    int cantidadMenores = 0;

    root = insert(root, 12, &cantidadMenores);
    cantidadMenores = 0;
    root = insert(root, 30, &cantidadMenores);
    cantidadMenores = 0;
    root = insert(root, 1, &cantidadMenores);
    cantidadMenores = 0;
    root = insert(root, 2, &cantidadMenores);

    int results[4];
    int count = 0;
    searchByCantidadMenores(root, 1, results, &count);

    printf("Elements with cantidadMenores = 1: ");
    for (int i = 0; i < count; i++) {
        printf("%d ", results[i]);
    }
    printf("\n");

    int orderedResults[4];
    int index = 0;
    inOrder(root, orderedResults, &index);

    printf("Elements ordered by cantidadMenores: ");
    for (int i = 0; i < 4; i++) {
        printf("%d ", orderedResults[i]);
    }
    printf("\n");

    root = deleteNode(root, 1);
    index = 0;
    inOrder(root, orderedResults, &index);

    printf("Elements after deleting 1: ");
    for (int i = 0; i < 3; i++) {
        printf("%d ", orderedResults[i]);
    }
    printf("\n");

    return 0;
}
