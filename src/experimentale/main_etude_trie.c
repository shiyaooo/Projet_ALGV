#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "experimentale.h"
#include <ctype.h>  
#include <stdbool.h>
#include <unistd.h>
#include "tries_hybrides.h"
#include "fonctions_avancees.h"
#include "ecriture_lecture.h"
//  gcc -Wall -o main main.c experimentale.c

int main() {
    Words* lwords=read_Files_Shakespeare("../../Shakespeare");
    printf("\n");
    eciture_words(lwords);
    printf("Successful!\n");

    /*---------------- Temps de construction de la structure complète ----------------*/
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

    /*---------------- Temps d'ajout d'un nouveau mot dans les structures ----------------*/

    return 0;
}