#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "experimentale.h"
#include <ctype.h>  
#include <stdbool.h>
#include <unistd.h>
#include "../tries_hybrides/tries_hybrides.h"
#include "../tries_hybrides/fonctions_avancees.h"
//  gcc -Wall -o main main.c experimentale.c

int main() {
    Words* lwords=read_Files_Shakespeare("../../Shakespeare");
    printf("\n");
    eciture_words(lwords);
    printf("Successful!\n");

    /* Q 6.10*/

    // Construction du trie hybride
    FILE *file = fopen("words.txt", "r");
    // printf("name file %s\n", argv[1]);
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier .txt\n");
        return 1;
    }
    int cpt=0;
    TrieH* th = NULL;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        //printf("%s", line);
        line[strcspn(line, "\n")] = '\0';
        th = TH_Ajout(line, th, cpt);
        cpt++;
    }
    fclose(file);
    file = fopen("trie.json", "w");

    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier .json\n");
        return 1;
    }
    //fprintf(file, "{\n");
    ecrire_trie(file, th, 0);
    fclose(file);
    printf("trie.json construit");

    return 0;
}