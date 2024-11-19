#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "Patricia_Tries.h"


/*****************************EX1*****************************/
// Question 1.2 Encoder les primitives de base concernant les Patricia-tries.

// Fonction pour créer un nœud vide
PAT* PATVide(){
    PAT* pat = (PAT*)malloc(sizeof(PAT));
    pat -> cle = NULL;
    for(int i = 0; i < TAILLE_PAT; i++){
        pat -> fils[i] = NULL;
    }
    return pat;
}

// Fonction pour créer un arbre avec un seul nœud
PAT* PATCons(char* m){
    PAT* A =PATVide();
    A -> cle = strdup(m);
    return A;
}




