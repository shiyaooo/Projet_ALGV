#ifndef PATRICIA_TRIES_H
#define PATRICIA_TRIES_H
#include <stdbool.h>

#define END_OF_WORD "\x20"    // terminateur de mot d'un arbre de dictionnaire (patricia_trie)
#define MAX_SIZE 1000


typedef struct PAT PAT;

typedef struct _Node{
    char* cle; // le plus long prefixe commun
    int valeur; //nb de cle;
    PAT* fils;
} Node;

typedef struct PAT{
    Node** node;
} PAT;

//typedef struct Patricia_Tries PAT;
/*EX1*/
Node* Nodevide();
PAT* PATVide();
Node* NodeCons(char* m);
PAT* creer_PAT();
PAT* PATCons(Node* n);
int EstVideNode(Node* A);
int EstVide(PAT* A);
char* Rac(Node* A);
int Val(Node* A);
void printNode(Node* A, int indentation);
void printPAT(PAT* P);
void libererNode(Node* A);
void libererPAT(PAT* A);
void ajouter_fils(Node* A, Node* fil );
void ajouter_racine(PAT** P, Node* r);
void PATinsertion(PAT** A, char* m) ;
int estPrefixe (char*c , char* m);
int prefixe(char* c, char* m);
void splitSentence(char *sentence) ;
char* concat(const char* a, const char* b);






#endif