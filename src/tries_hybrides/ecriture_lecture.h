#ifndef ECRITURE_LECTURE_H
#define ECRITURE_LECTURE_H

#include "tries_hybrides.h"
#include <stdio.h>

/* Ecrit le trie hybride dans le format JSON */
int ecrire_trie(FILE* file, TrieH* arbre, int tabulation);

/* Modifie la valeur de cpt */
void setCpt(int valeur);

/* Construit le trie hybride depuis le format JSON */
TrieH* charger_trie(char *content, int *index);

#endif // ECRITURE_LECTURE_H