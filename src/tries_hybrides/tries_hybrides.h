#ifndef TRIES_HYBRIDES_H
#define TRIES_HYBRIDES_H

/*
struct Node {
    char l;
    int i;
    Node inf;
    Node eq;
    Node sup;
} Node;
*/
typedef struct TrieH {
    char l; // lettre
    int v;  // valeur
    struct TrieH *inf; // sous-arbre gauche
    struct TrieH *eq;  // sous-arbre central
    struct TrieH *sup; // sous-arbre droite
} TrieH;

/* construit une trie hybride */
TrieH* TrieHybride(char l, TrieH* inf, TrieH* eq, TrieH* sup, int v);


/* renvoie une trie hybride vide */
TrieH* TH_Vide();

/* renvoie 1 ssi le trie hybride A est vide, 0 sinon */
int EstVide(TrieH* A);

/* renvoie le caractère de la racine du trie hybride */
char Rac(TrieH* A);

/* renvoie l'entier de la racine du trie hybride, -1 sinon */
int Val(TrieH* A);

/* renvoie une copie du sous-arbre gauche de A */
TrieH* Inf(TrieH* A);

/* renvoie une copie du sous-arbre central de A */
TrieH* Eq(TrieH* A);

/* renvoie une copie du sous-arbre droite de A */
TrieH* Sup(TrieH* A);


/* renvoie le trie hybride resultant de l'insertion de c dans A */
TrieH* TH_Ajout(char* c, TrieH* A, int v);

#endif // TRIES_HYBRIDES_H