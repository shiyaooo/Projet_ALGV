#ifndef PATRICIA_TRIES_H
#define PATRICIA_TRIES_H

#define END_OF_WORD '\x7F' // terminateur de mot d'un arbre de dictionnaire (patricia_trie)
#define EMPTY_WORD '\0'    // Représente un mot vide 

#defie TAILLE_PAT 128;


struct Patricia_Tries{
    char* cle; // le plus long prefixe commun
    struct Patricia_Tries *fils[TAILLE_PAT]; // Tableau de fils (pour chaque caractère de l'alphabet)
    struct Patricia_Tries **fils; // Liste dynamique des sous-fils
}PAT;

#endif