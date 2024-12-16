#ifndef FONCT_AVC_H
#define FONCT_AVC_H
#include <stdbool.h>
#include "Patricia_Tries.h"

typedef struct{
    char* cle;
    int val;
    PAT* enf;
} Dic_enf;

/*EX2*/
bool recherchePAT(PAT* A, char* mot);

int ComptageMotsdansPAT(PAT* A);

int comparemots(const void* a, const void* b);
void collecterMots(Node* racine, char* prefixe, char*** resultats, int* taille, int* capacite);
char** ListeMotsdansPAT(PAT* A);

int ComptageNildansNode(Node* n);
int ComptageNildansPAT(PAT* A);

int HauteurNode(Node* n);
int HauteurPAT(PAT* A);

void calculerProfondeursFeuilles(Node* A, int profondeur, int* somme, int* nb_feuilles);
int ProfondeurMoyennePAT(PAT* A);

void compterMotsDansSousArbre(Node* A, int* count);
void compterMotsPrefixe(Node* A, char* mot, int* count);
int PrefixedansPAT(PAT* A, char* mot);

char* concat(const char* a, const char* b);
Dic_enf* consDic_enf(char* cle, int val);
void libererDic_enf(Dic_enf* de);
int isValidKey(char* key) ;
void PATsuppressionRec(PAT** A, char* mot);
void PATsuppression(PAT** A, char* mot);


PAT* PATfusion(PAT* A, PAT* B);



#endif 