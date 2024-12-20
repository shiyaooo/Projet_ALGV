#ifndef EXPERIMANTALE_H
#define EXPERIMANTALE_H
#include "../Patricia-Tries/Patricia_Tries.h"
#include "../Patricia-Tries/fonct_avc.h"
#include "../Patricia-Tries/patricia_json.h"
#include <dirent.h>

typedef struct words{
    char* data;
    struct words* suiv;  
}Words;

//struct dirent *dir;

Words* create_list_word(char* cle);
Words* insert_word_in_List(char* cle, Words* lcle);
Words* insertWordsNotExist(char* cle, Words* lcle);
void print_List_Word(Words* lw);
void free_List_word(Words* lw) ;
Words* read_Files_Shakespeare(char* nomDossier);
void eciture_words(Words* words);
Words* read_ouvre_Shakespeare(char* nomFichier);

double measureTime_ajout_un_seul_PAT(void (*function)(PAT**, char*),PAT** pat, char* cle);
double measureTime_supp_PAT(void (*function)(PAT**, char*),PAT** pat, char* cle);
double measureTime_fusion_PAT(PAT* (*function)(PAT*, PAT*),PAT* a, PAT* b);


#endif