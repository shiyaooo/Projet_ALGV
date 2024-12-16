#ifndef EXPERIMANTALE_H
#define EXPERIMANTALE_H
/*
#include "../Patricia-Tries/Patricia_Tries.h"
#include "../Patricia-Tries/fonct_avc.h"
*/
// #include "../Patricia-Tries/patricia_json.h"
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


#endif