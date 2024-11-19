#include <stdio.h>
#include <stdlib.h>
#include "Patricia_Tries.h"

int main() {
    /*****************************EX1*****************************/

    // Q1.1 Déterminer un caractère parmi les 128 du code ASCII pour indiquer la fin d'un mot.
    printf("Q.1.1 Déterminer un caractère parmi les 128 du code ASCII pour indiquer la fin d'un mot.\n\n");
    printf("En général, le caractère '\\0' est utilisé pour indiquer la fin ");
    printf("d'une chaîne de caractères en C. Cependant, dans l'implémentation ");
    printf("d'un arbre de dictionnaire (patricia_trie), pour éviter tout ");
    printf("conflit avec le caractère de fin de chaîne en C, nous pouvons ");
    printf("choisir d'utiliser d'autres caractères ASCII peu courants, ");
    printf("comme DEL (ASCII 127 ou '\\x7F'), comme marqueur de fin de mot. ");
    printf("Le caractère '\\0' peut alors être utilisé pour représenter un mot vide (mot vide).\n ");

    return 0;
}
