#include "ArbolGeneral.h"

GBTree newNode(void* data) {
    GBTree* node = (GBTree*) malloc(sizeof(GBTree));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to perform an inorder traversal of the tree
void inorder(GBTree root, void (*printData)(void*)) {
    if (root == NULL) {
        return;
    }
    inorder(root->left, printData);
    printData(root->data);
    inorder(root->right, printData);
}

// Function to perform a preorder traversal of the tree
void preorder(GBTree root, void (*printData)(void*)) {
    if (root == NULL) {
        return;
    }
    printData(root->data);
    preorder(root->left, printData);
    preorder(root->right, printData);
}

// Function to perform a postorder traversal of the tree
void postorder(GBTree root, void (*printData)(void*)) {
    if (root == NULL) {
        return;
    }
    postorder(root->left, printData);
    postorder(root->right, printData);
    printData(root->data);
}

// Function to print an integer
void printInt(void* data) {
    printf("%d ", *(int*)data);
}

int main() {
    // Create a new tree
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    int data4 = 4;
    int data5 = 5;
    GBTree root = newNode(&data1);
    root->left = newNode(&data2);
    root->right = newNode(&data3);
    root->left->left = newNode(&data4);
    root->left->right = newNode(&data5);

    // Perform an inorder traversal of the tree
    printf("Inorder traversal: ");
    inorder(root, printInt);
    printf("\n");

    // Perform a preorder traversal of the tree
    printf("Preorder traversal: ");
    preorder(root, printInt);
    printf("\n");

    // Perform a postorder traversal of the tree
    printf("Postorder traversal: ");
    postorder(root, printInt);
    printf("\n");

    return 0;
}