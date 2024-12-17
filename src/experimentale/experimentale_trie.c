#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <time.h>
#include<dirent.h>
#include "experimentale_trie.h"

/*----------------------Q6.10------------------------*/
Words* create_list_word(char* cle){
    Words* lcle=malloc(sizeof(Words));
    if(lcle==NULL){
        printf("Erreur d'allocation\n");
        return NULL;
    }
   
    lcle->data=strdup(cle);
    //printf("lcle->data %s\n",lcle->data);
    lcle->suiv=NULL;
    return lcle;
}

Words* insert_word_in_List(char* cle, Words* lcle){
    if(lcle==NULL){
        return create_list_word(cle);
    }
    Words* tmpcle=lcle;
    while(tmpcle->suiv!=NULL){
        tmpcle=tmpcle->suiv;
    }
    tmpcle->suiv=create_list_word(cle);
    return lcle;
}

Words* insertWordsNotExist(char* cle, Words* lcle){
    // Vérifier si l'élément est déjà présent dans la liste
    Words* current = lcle;
    //if(lcle==NULL){return create_list_word(cle);}
    while (current != NULL) {
        if (strcmp(current->data, cle) == 0) {
            // L'élément est déjà présent, ne pas l'insérer à nouveau
            //printf("deja exist\n");
            return lcle;
        }
        current = current->suiv;
    }
    // L'élément n'est pas dans la liste, l'insérer
    //printf("word=%s\n",cle);
    return insert_word_in_List(cle, lcle);
}

// Fonction pour afficher la liste chaînée
void print_List_Word(Words* lw) {
    Words* current = lw;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->suiv;
    }
    printf("\n");
}

// Fonction pour libérer la mémoire allouée pour la liste chaînée
void free_List_word(Words* lw) {
    Words* current = lw;
    Words* next;

    while (current != NULL) {
        next = current->suiv;
        free(current->data);
        free(current);
        current = next;
    }
}

   
Words* read_Files_Shakespeare(char* nomDossier){
    struct dirent *dir;

     DIR *d=opendir(nomDossier);
     if(!d){
        fprintf(stderr,"erreur d'ouverture du dossier %s\n",nomDossier);
        return NULL;
     }
    // Lire tous les fichiers dans le répertoire
    char word[256];
    Words* words=NULL;
    while((dir=readdir(d))!=NULL){
        // Assurez-vous de ne pas traiter les entrées spéciales "." et ".."
        if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
            //printf("file=%s\n",dir->d_name);
            char file_path[257];
            sprintf(file_path,"%s/%s",nomDossier,dir->d_name);
            file_path[strlen(file_path)]='\0';
            FILE* f =fopen(file_path,"r");
            if (f==NULL){
                fprintf(stderr,"erreur d'ouverture du fichier texte contenant les mots %s\n",file_path);
                return NULL;
            }

            int taille_max=256;
            char buffer[taille_max];
            
            while (fgets(buffer,256,f)!=NULL){
                sscanf(buffer,"%s",word);
                //inserer dans une liste de word apres comparer avec elm
                words=insertWordsNotExist(word,words);
                //words_initial=insert_word_in_List(word,words_initial);
            }
            //printf("words->data=%s\n",words->data);
            
            fclose(f);
        }
        
    }
    //print_List_Word(words);
    //print_list_cle(lcle);
    closedir(d);   
   
    return words;
}

Words* read_ouvre_Shakespeare(char* nomFichier) {
    FILE *file;
    char word[256];
    Words* words=NULL;
    
    // Ouvrir le fichier en mode lecture
    file = fopen(nomFichier, "r");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier %s\n", nomFichier);
        return NULL;
    }

    int taille_max=256;
    char buffer[taille_max];
    
    // Lire chaque mot du fichier
    while (fgets(buffer,256,file)!=NULL){
        sscanf(buffer,"%s",word);
        //inserer dans une liste de word apres comparer avec elm
        words=insertWordsNotExist(word,words);
        //words_initial=insert_word_in_List(word,words_initial);
    }

    // Fermer le fichier
    fclose(file);
    return words;
}


   

void eciture_words(Words* words){
    FILE *f = fopen("words.txt", "a");
    if (!f) {
        printf("Erreur ouverture fichier\n");
        return;
    }
    if(!words) return;
    Words* tmp=words;
    while(tmp){
        fprintf(f,"%s\n", tmp->data);
        tmp=tmp->suiv;
    }
    fclose(f);
}


double measureTime_ajout_un_seul_TH(TrieH* (*function)(char*, TrieH*, int),char* cle, TrieH* th, int val){
    clock_t start, end;
    start = clock();
    function(cle, th, val);
    end = clock();
    // free(result);
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

// temps de la suppression d'un mot des structures
double measureTime_supp_TH(TrieH* (*function)(TrieH*, char*),TrieH* th, char* cle){
    clock_t start, end;
    start = clock();
    function(th,cle);
    end = clock();
    // free(result);
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}