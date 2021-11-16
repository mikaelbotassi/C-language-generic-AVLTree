#include <stdio.h>
#include "Utils/HeaderUtils/Studant.h"
#include "Utils/HeaderUtils/controleArquivo.h"

int main() {
    AVLTree *b = NULL;
    setvbuf(stdout, NULL, _IONBF, 0);
    b = AVLtreeInitialized();
    b = readTreeAlunoFromFile(b);
    menu(b);
    writeMenu(b);
    freeAVLTree(b);

    return 0;
}
