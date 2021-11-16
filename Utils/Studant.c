//
// Created by mikael on 03/11/2021.
//

//========== INCLUDES ============
#include "HeaderUtils/Studant.h"
//================================
/*
Função de menu, esta função chama as outras funções dependendo da resposta do usuário.
*/
void menu(AVLTree * b)
{
    int res = 5;
    while (res != 4)
    {
        printf("\n 0 - EXIBIR ESTATISTICAS;");
        printf("\n 1 - INCLUIR ALUNO;");
        printf("\n 2 - EFETUAR BUSCA POR MATRICULA;");
        printf("\n 3 - EXCLUIR POR MATRICULA;");
        printf("\n 4 - SAIR");

        printf("\nDigite o numero correspondente a funcao que deseja utilizar: ");
        scanf(" %d", &res);

        if(res==0){
            printf("\n\tTREE HEIGHT: %d\n", calculateHeight(b->root));
            printf("\n\tTOTAL ELEMENTS: %d\n", b->elementsQuantity);
        }
        if (res == 1)
        {
            newStudant(b);
        }
        if (res == 2)
        {
            studantSearch(b);
        }
        if (res == 3)
        {
            b = excludeStudant(b);
        }
    }
}

aluno * allocStudant()
{
    aluno *p = (aluno *)malloc(sizeof(aluno));
    p->matricula = 0;
    p->nota = 0;
    strcpy(p->nome, "\0");
    return p;
}

void newStudant(AVLTree * b)
{ //Caso o usuário queira inserir um aluno novo sem leitura de arquivos
    aluno *p = allocStudant();
    printf("\nDigite a matricula do aluno: ");
    scanf("%d", &p->matricula);
    printf("Digite o nome do aluno: ");
    scanf(" %31[^\n]", &p->nome);
    printf("Digite a nota do aluno: ");
    scanf("%d", &p->nota);
    insertStudant(b, p);
}

AVLTree * insertStudant(AVLTree *b, aluno *a)
{
    b = AVLgraft('A', b, a, studantCompare);
    return b;
}

int discoverType(char id)
{
    /*
Esta função pega o tipo de dado passado pelo variavel, neste caso
como quero trabalhar apenas com aluno, recdbo apenas o tipo 'A' ou 'a'
*/
    if (id == 'A' || id == 'a')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int registrationCompare(char id, void *n, int key){
    if(discoverType(id)){
        if(n!=NULL){
            aluno *p = n;
            if(key > p->matricula){
                return 1;
            }
            else if(key < p->matricula){
                return -1;
            }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }
    }
    else{
        printf("Insira outras verificações dos tipos de varáveis possíveis! ");
        return -1;
    }
}

int studantCompare(char id, void * n1, void *n2){ // Pega dois elementos, verifica maior menor.
    if(discoverType(id)){
        if(n2!=NULL){
            aluno *p1=n1;
            aluno *p2=n2;
            if(p1->matricula>p2->matricula){
                return 1;
            }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }
    }
    else{
        printf("Insira outras verificações dos tipos de varáveis possíveis! ");
        return -1;
    }
}

void studantSearch(AVLTree * b)
{ //Procura o aluno pela matricula
    int chave;
    printf("\nDigite a matricula da pessoa que voce quer procurar: ");
    scanf(" %d", &chave);
    AVLsearch(b->root, chave, registrationCompare, printStudant);
}

AVLTree * excludeStudant(AVLTree * b)
{//Função que exclui um determinado aluno da Lista
    int chave;
    printf("\nDigite a matricula da pessoa que voce quer excluir: ");
    scanf(" %d", &chave);
    b->root = AVLprune(b->root, chave, registrationCompare, printStudant);
    return b;
}

void printStudant(char id, void *elem)
{
    if (discoverType(id))
    {
        aluno *p = elem;
        printf("\nMatricula: %d", p->matricula);
        printf("\nNome: %s", p->nome);
        printf("\nNota: %d", p->nota);
        printf("\n");
    }
    else
    { //Caso a variavel não seja do tipo aluno
        printf("\nNao e possivel printar! ");
    }
}

int returnChave(void *elem, char id)
{
    if (discoverType(id))
    { // É do tipo aluno?
        aluno *a = elem;
        return a->matricula; //Se sim retorna a matricula do aluno, a "chave" para a inserção
    }
    else
    {
        printf("\nDigite mais setenças de tipos de chaves! \n");
        return 0;
    }
}
