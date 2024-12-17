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
int nombre_node(PAT* pat);

bool recherchePAT(PAT* A, char* mot);
bool recherchePAT_cpt(PAT* A, char* mot, int* cpt);

int ComptageMotsdansPAT(PAT* A);
int ComptageMotsdansPAT_cpt(PAT* A, int* cpt);

int comparemots(const void* a, const void* b);
void collecterMots(Node* racine, char* prefixe, char*** resultats, int* taille, int* capacite);
char** ListeMotsdansPAT(PAT* A);

void collecterMots_cpt(Node* racine, char* prefixe, char*** resultats, int* taille, int* capacite, int* cpt);
char** ListeMotsdansPAT_cpt(PAT* A, int* cpt);

int ComptageNildansNode(Node* n);
int ComptageNildansPAT(PAT* A);

int ComptageNildansNode_cpt(Node* n, int* cpt);
int ComptageNildansPAT_cpt(PAT* A, int* cpt);

int HauteurNode(Node* n);
int HauteurPAT(PAT* A);

int HauteurNode_cpt(Node* n, int* cpt);
int HauteurPAT_cpt(PAT* A, int* cpt);

void calculerProfondeursFeuilles(Node* A, int profondeur, int* somme, int* nb_feuilles);
int ProfondeurMoyennePAT(PAT* A);

void calculerProfondeursFeuilles_cpt(Node* A, int profondeur, int* somme, int* nb_feuilles, int* cpt);
int ProfondeurMoyennePAT_cpt(PAT* A, int* cpt);

void compterMotsDansSousArbre(Node* A, int* count);
void compterMotsPrefixe(Node* A, char* mot, int* count);
int PrefixedansPAT(PAT* A, char* mot);

void compterMotsDansSousArbre_cpt(Node* A, int* count, int* cpt);
void compterMotsPrefixe_cpt(Node* A, char* mot, int* count, int* cpt);
int PrefixedansPAT_cpt(PAT* A, char* mot, int* cpt);

char* concat(const char* a, const char* b);
Dic_enf* consDic_enf(char* cle, int val);
void libererDic_enf(Dic_enf* de);
int isValidKey(char* key) ;
void PATsuppressionRec(PAT** A, char* mot);
void PATsuppression(PAT** A, char* mot);

void PATsuppressionRec_cpt(PAT** A, char* mot, int* cpt);
void PATsuppression_cpt(PAT** A, char* mot, int* cpt);


PAT* PATfusion(PAT* A, PAT* B);
PAT* PATfusion_cpt(PAT* A, PAT* B, int* cpt);



#endif 