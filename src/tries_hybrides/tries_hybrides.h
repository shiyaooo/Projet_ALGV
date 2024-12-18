#ifndef TRIES_HYBRIDES_H
#define TRIES_HYBRIDES_H

typedef struct TrieH {
    char l; // lettre
    int v;  // valeur
    struct TrieH *inf; // sous-arbre gauche
    struct TrieH *eq;  // sous-arbre central
    struct TrieH *sup; // sous-arbre droite
    int hauteur; // Ajout d'un champ pour la hauteur
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


/* renvoie la première lettre de la chaine de caractères */
char prem(char* c);

/* renvoie le reste de la chaine de caractères 
    privée de la première lettre */
char* reste(char* c);

/* renvoie le trie hybride resultant de l'insertion de c dans A */
TrieH* TH_Ajout(char* c, TrieH* A, int v);

/* libère la mémoire allouée pour un noeud de trie hybride */
void free_TH(TrieH* A);

/* libère la mémoire allouée pour une chaîne de caractères */ 
void free_chaine(char* chaine);

#endif // TRIES_HYBRIDES_H