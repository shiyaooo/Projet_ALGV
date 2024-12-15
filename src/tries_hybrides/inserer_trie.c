#include "tries_hybrides.h"
#include "fonctions_avancees.h"
#include "ecriture_lecture.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc!=2) {
        printf("Usage: %s <fichier.txt>\n", argv[0]);
        return 1;
    }

    // Lire le fichier .txt
    FILE *file = fopen(argv[1], "r");
    printf("name file %s\n", argv[1]);
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