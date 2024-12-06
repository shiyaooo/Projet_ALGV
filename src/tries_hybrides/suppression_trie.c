#include "tries_hybrides.h"
#include "fonctions_avancees.h"
#include "ecriture_lecture.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
int cpt = 0;    // setCpt(); pour le mettre à 0 si déplace la fonction

TrieH* charger_trie(char *content, int *index) {
    TrieH *th = (TrieH*) malloc(sizeof(TrieH));
    memset(th, 0, sizeof(TrieH));   // Initialiser à zéro

    // Parsing
    while (content[*index] != '\0') {
        if (content[*index] == '\"') {
            (*index)++;
            if (strncmp(&content[*index], "char", 4) == 0) {
                *index += 6;
                th->l = content[*index];
                *index += 2;
            } else if (strncmp(&content[*index], "is_end_of_word", 14) == 0) {
                *index += 16;
                if (strncmp(&content[*index], "false", 5) == 0) {
                    th->v = -1;
                    *index += 6;
                } else {
                    th->v = cpt;
                    cpt++;
                    *index += 5;    // true
                }
            } else if (strncmp(&content[*index], "left", 4) == 0) {
                *index+=6;
                if (strncmp(&content[*index], "null", 4) == 0) {
                    *index+=5;
                    th->inf = TH_Vide();
                } else {
                    // *index+=1;
                    th->inf = charger_trie(content, index);
                }
            } else if (strncmp(&content[*index], "middle", 6) == 0) {
                *index+=8;
                 if (strncmp(&content[*index], "null", 4) == 0) {
                    *index+=5;
                    th->eq = TH_Vide();
                } else {
                    // *index+=1;
                    th->eq = charger_trie(content, index);
                }
            } else if (strncmp(&content[*index], "right", 6) == 0) {
                *index+=7;
                 if (strncmp(&content[*index], "null", 4) == 0) {
                    *index+=4;
                    th->sup = TH_Vide();
                } else {
                    // *index+=1;
                    th->sup = charger_trie(content, index);
                }
            }
        } else {
            *index+=1;
        }
    }

    return th;
}
*/
int main(int argc, char *argv[]) {
    if (argc!=2) {
        printf("Usage: %s <fichier.txt>\n", argv[0]);
        return 1;
    }

    // lecture de trie.json
    FILE *file = fopen("trie.json", "rb");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier .json\n");
        return 1;
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *content = (char*) malloc(length + 1);
    fread(content, 1, length, file);
    fclose(file);
    content[length] = '\0';

    setCpt(0);
    int index = 0;
    TrieH* th = charger_trie(content, &index);

    /* test de ListeMots */
    
    List* liste = ListeMots(th);
    int i = 1;
    List* tmp = liste;
    while (tmp!=NULL) {
        printf("%d : %s\n", i, tmp->mot);
        tmp = tmp->suiv;
        i++;
    }
    
    // lecture du fichier .txt
    // et suppressions successives des mots dans le trie hybride
    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier .txt\n");
        return 1;
    }
    
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        //printf("%s", line);
        line[strcspn(line, "\n")] = '\0';
        th = Suppression(th, line);
    }
    fclose(file);
    
    // Ecrire un fichier .json
    file = fopen("trie.json", "w");

    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier .json\n");
        return 1;
    }
    //fprintf(file, "{\n");
    ecrire_trie(file, th, 0);

    fclose(file);
    
    return 0;
}