//
// Created by mikael on 03/11/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _BINARYTREE_H
#define _BINARYTREE_H

//========================= CONSTANTS ===============================
#define CMP_ALUNO int (*comp)(char, void *, void *) //int cmp(char id, void * n1, void *n2)
#define CMP_REGISTRATION int (comp)(char, void *, int)
#define PRINT void (* print)(char, void *) //printStudant
//===========================================================================

typedef struct Node{
    struct Node * right;
    struct Node *left;
    void * element;
    char type;
    int balancingFactor;
}node;

typedef struct AVLTree{
    node * root;
    int height;
    int elementsQuantity;
}AVLTree;

AVLTree * AVLtreeInitialized();

node * nodeInitialized(node * n);

node * freeNode(node * n);

AVLTree * freeAVLTree(AVLTree * b);

int calculateHeight(node *n);

node * rightRotation(node * n);

node * leftRotation(node *  n);

node * leftRightRotation(node *  n);

node * rightLeftRotation (node * n);

node * AVLinsert(char type,  node *n, void *elem, int *growth, CMP_ALUNO);

AVLTree * AVLgraft(char type,  AVLTree * t, void *elem, CMP_ALUNO);

void AVLsearch(node *n, int key, CMP_REGISTRATION, PRINT);

node * AVLprune(node * n, int key, CMP_REGISTRATION, PRINT);

#endif //_BINARYTREE_H