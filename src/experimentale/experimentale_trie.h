#ifndef EXPERIMANTALE_H
#define EXPERIMANTALE_H
#include "../tries_hybrides/tries_hybrides.h"
#include "../tries_hybrides/fonctions_avancees.h"
#include "../tries_hybrides/ecriture_lecture.h"
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

double measureTime_ajout_un_seul_TH(TrieH* (*function)(char*, TrieH*, int),char* cle, TrieH* th, int val);
double measureTime_supp_TH(TrieH* (*function)(TrieH*, char*),TrieH* th, char* cle);


#endif