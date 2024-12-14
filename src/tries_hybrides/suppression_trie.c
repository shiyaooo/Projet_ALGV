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

    
    // lecture du fichier .txt
    // et suppressions successives des mots dans le trie hybride
    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier .txt\n");
        return 1;
    }
    /*
    char* dactylo = "dactylo";
    printf("%ld\n", strlen(dactylo));
    */
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        //size_t len = strlen(line);
        //printf("Avant suppression du \\n, longueur: %zu, ligne: '%s'\n", len, line);
        //printf("%ld\n", strlen(line));
        line[strcspn(line, "\n")] = '\0';
        //len = strlen(line);
        //printf("Après suppression du \\n, longueur: %zu, ligne '%s'\n", len, line);
        th = Suppression(th, line);
    }
    fclose(file);

    /* affichage ListeMots */
    /*
    List* liste = ListeMots(th);
    int i = 1;
    List* tmp = liste;
    while (tmp!=NULL) {
        printf("%d : %s\n", i, tmp->mot);
        tmp = tmp->suiv;
        i++;
    }
    */
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