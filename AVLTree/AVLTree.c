//
// Created by mikae on 03/11/2021.
//

#include "AVLTree.h"

//===================== PRIVATE FUNCTIONS ======================================
int empty(node *n);
//=============================================================================


//====================== PUBLIC FUNCTIONS =====================================
AVLTree * AVLtreeInitialized() {
    AVLTree * t = (AVLTree *) malloc(sizeof(AVLTree));
    t->root = NULL;
    t->height = 0;
    t->elementsQuantity = 0;
    return t;
}

node * nodeInitialized(node *n) {
    n = (node *) malloc(sizeof(node));
    n->type = '\0';
    n->element = NULL;
    n->left = NULL;
    n->right = NULL;
    n->balancingFactor = 0;
    return n;
}

int empty(node *n) {
    if (n == NULL) {
        return 1;
    }
    return 0;
}

node * freeNode(node * n){
    if(empty(n)){}
    else{
        n->left = freeNode(n->left);
        n->right = freeNode(n->right);
        free(n);
        n = NULL;
    }
    return n;
}

AVLTree * freeAVLTree(AVLTree * b){
    if(b->root == NULL){}
    else{
        b->root = freeNode(b->root);
        free(b);
    }
    return NULL;
}

node * rightRotation(node * n) {
    node * y = n;
    node * x = y->left;
    y->left = x->right;
    x->right = y;
    x->balancingFactor = 0;
    y->balancingFactor = 0;
    n = x;
    return n;
}

node * leftRotation(node *  n) {
    node * y = n;
    node * x = y->right;
    y->right=x->left;
    x->left=y;
    x->balancingFactor=0;
    y->balancingFactor=0;
    n = x;
    return  n;
}


node * leftRightRotation(node *  n) {
    node * y = n;//no *c=*r;
    node * e = y->left;//no *a=c->esq;
    node * d = e->right;//no *b=a->dir;
    //Rotação Esqueda -rot_esq(&(y->esq));
    e->right = d->left;
    d->left = e;
    //Rotação direita -- rot_dir(&y);
    y->left = d->right;
    d->right = y;
    //Atualização dos fbs
    switch (d->balancingFactor) {
        case -1:
            e->balancingFactor=0;
            y->balancingFactor=1;
            break;
        case 0:
            e->balancingFactor=0;
            y->balancingFactor=0;
            break;
        case 1:
            e->balancingFactor= -1;
            y->balancingFactor=0;
            break;
    }
    d->balancingFactor=0;
    n = d;
    return n;
}

node * rightLeftRotation (node * n) {
    node * y = n;//no *c=*r;
    node * d = y->right;//no *a=c->esq;
    node * e = d->left;//no *b=a->dir;
    //Rotação Direita
    d->left = e->right;
    e->right = d;
    //Rotação esquerda
    y->right = e->left;
    e->left = y;

    //Atualização dos fbs
    switch (e->balancingFactor) {
        case -1:
            y->balancingFactor=0;
            d->balancingFactor=1;
            break;
        case 0:
            y->balancingFactor=0;
            d->balancingFactor=0;
            break;
        case 1:
            y->balancingFactor= -1;
            d->balancingFactor=0;
            break;
    }
    e->balancingFactor = 0;
    n = e;
    return n;
}


int calculateHeight(node *n) {
    if (empty(n)) return 0;
    else if (empty(n->right) && empty(n->left)) return 0;
    else {
        int hLeft = calculateHeight(n->left);
        int hRight = calculateHeight(n->right);
        if (hLeft > hRight) {
            return 1 + hLeft;
        } else {
            return 1 + hRight;
        }
    }
}

node * AVLinsert(char type,  node *n, void *elem, int *growth, CMP_ALUNO){
    if(!empty(n)){
        if (comp(type, elem, n->element)) {
            n->right = AVLinsert(type, n->right, elem, growth, comp);
            if (n->right != NULL) {
                if (*growth) {
                    switch (n->balancingFactor) {
                        //Se o fb era -1 e cresceu a direita, agora é 0 e não precisa balancear
                        case -1:
                            n->balancingFactor = 0;;
                            *growth = 0; //interrompe propagação
                            break;
                        case 0:;
                            //Se o fb da raiz era zero agora é 1 pois cresceu a direita. Não precisa balancear
                            n->balancingFactor = 1;
                            *growth = 1; // propaga verificação
                            break;
                            //Como a árvore cresceu para a direita, o fb da raiz aumentou em 1
                            //Logo, se era 1, agora é 2! Assim, preciso balancear
                        case 1:
                            //Se o fb do filho direita for 1 faço rotação esquerda
                            if (n->right->balancingFactor == 1)
                                n = leftRotation(n);
                                //Se o fb do filho direita não for 1 faço rotação direita esquerda
                            else n = rightLeftRotation(n);
                            *growth = 0; //interrompe propagação
                            break;
                    }
                }
            }
        } else {
            n->left = AVLinsert(type, n->left, elem, growth, comp);
            if (n->left != NULL) {
                if (*growth) {
                    //Vou atualizar fb e balancear se necessário
                    switch (n->balancingFactor) {
                        //Como a árvore cresceu para a esquerda, o fb da raiz reduziu em 1
                        //Logo, se era -1, agora é -2! Assim, preciso balancear
                        case -1:
                            //Se o fb do filho esquerda for -1 faço rotação direita
                            if (n->left->balancingFactor == -1)
                                n = rightRotation(n);
                                // Se o fb do filho esquerdo não for -1, rotação esquerda direita
                            else n = leftRightRotation(n);
                            *growth = 0; //interrompe propagação
                            break;
                        case 0:
                            //Se o fb da raiz era zero agora é -1 pois cresceu a esquerda. Não precisa balancear
                            n->balancingFactor = -1;
                            *growth = 1; // propaga verificação
                            break;
                        case 1:
                            //Se o fb era 1 e cresceu a esquerda, agora é 0 e não precisa balancear
                            n->balancingFactor = 0;
                            *growth = 0; //interrompe propagação
                            break;
                    }
                }
            }
        }
    }else {
        n = nodeInitialized(n);
        n->type = type;
        n->element = elem;
        *growth = 1;
    }
    return n;
}

AVLTree * AVLgraft(char type,  AVLTree * t, void *elem, CMP_ALUNO) {
    int growth = 0;
    t->elementsQuantity++;
    t->root = AVLinsert(type, t->root, elem, &growth, comp);
    return t;
}


void AVLsearch(node *n, int key, CMP_REGISTRATION, PRINT){
    int traversedElements = 0;
    node * aux = n;
    while(!empty(aux)){
        traversedElements++;
        if(comp(aux->type, aux->element, key) == 1){
            aux = aux->right;
        }
        else if(comp(aux->type, aux->element, key) == -1){
            aux = aux->left;
        }
        else{
            print(aux->type, aux->element);
            printf("\nCOMPARATION NUMBER: %d\n", traversedElements);
            return;
        }
    }
    printf("\n\tSTUDENT DOES NOT EXIST!\n");
}

node * AVLprune(node * n, int key, CMP_REGISTRATION, PRINT){
    if (n == NULL) {
        printf("\n\tSTUDENT DOES NOT EXIST!\n");
        return NULL;
    }
    else if (comp(n->type, n->element, key) == -1)
        n->left = AVLprune(n->left, key, comp, print);
    else if (comp(n->type, n->element, key) == 1)
        n->right = AVLprune(n->right, key, comp, print);
    else {//Se chegar aqui achei o no a ser removido
        print(n->type, n->element);
        printf("\n\tEXCLUDED STUDENT!\n");

        // Se o nó não tem filhos só o desaloco
        if (n->left == NULL && n->right == NULL) {
            free (n);
            //Coloco NULL em r para retornar
            n = NULL;
        }
            // Se o nó só tem filho à direita, desaloco o nó e guardo o filho a direita para retornar
        else if (n->left == NULL) {
            node * d = n->right;
            free (n);
            n=d;
        }
            // Se o nó só tem filho à esquerda, desaloco o nó e guardo o filho a esquerda para retornar
        else if (n->right == NULL) {
            node * e = n->left;
            free (n);
            n=e;
        }
            // Se o nó tem os dois filhos, acho o elemento mais à direita da árvore a esquerda
            //Troco a informação da raiz pela desse elemento e o desaloco
        else {
            node * e = n->left;
            //Laço para encontrar o maior elemento da subarvore esquerda
            while (e->right != NULL) {
                e = e->right;
            }
            //Troco a informação do maior elemento da esquerda com a raiz
            void * aux = n->element;
            n->element = e->element;
            e->element = aux;
            //Agora chamo o método para remover a folha.
            n->left = AVLprune(n->left, key, comp, print);
        }
    }
    return n;
}
