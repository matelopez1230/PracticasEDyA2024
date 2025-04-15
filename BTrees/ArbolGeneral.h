#ifndef __GBTree_H__
#define __GBTree_H__

#include <stdio.h>
#include <stdlib.h>

// Define the tree node
typedef struct node {
    void* data;
    struct Node *left;
    struct Node *right;
} Node;

typedef Node *GBTree;

#undef /*__GBTree_H__*/