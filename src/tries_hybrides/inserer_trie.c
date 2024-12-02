#include "tries_hybrides.h"
#include "fonctions_avancees.h"
#include "ecriture_lecture.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
int ecrire_trie(FILE* file, TrieH* arbre, int tabulation) {
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier .json\n");
        return 1;
    }

    if (EstVide(arbre)==1) {
        fputs("null", file);
        return 1;
    }

    int nouvtab = tabulation + 1;

    fputs("{\n", file);

    //char pm = prem(c);
    char rac = Rac(arbre);

    for(int i=0;i<nouvtab;i++) {
        fputc('\t', file);
    }
    fprintf(file, "\"char\": \"%c\",\n", rac);
    
    for(int i=0;i<nouvtab;i++) {
        fputc('\t', file);
    }
    if (Val(arbre)==-1) {
        fputs("\"is_end_of_word\": false,\n", file);
    } else {
        fputs("\"is_end_of_word\": true,\n", file);
    }

    for(int i=0;i<nouvtab;i++) {
        fputc('\t', file);
    }
    fputs("\"left\": ", file);
    ecrire_trie(file, Inf(arbre), nouvtab);
    fputs(",\n", file);

    for(int i=0;i<nouvtab;i++) {
        fputc('\t', file);
    }
    fputs("\"middle\": ", file);
    ecrire_trie(file, Eq(arbre), nouvtab);
    fputs(",\n", file);

    for(int i=0;i<nouvtab;i++) {
        fputc('\t', file);
    }
    fputs("\"right\": ", file);
    ecrire_trie(file, Sup(arbre), nouvtab);
    fputs("\n", file);
    
    for(int i=0;i<tabulation;i++) {
        fputc('\t', file);
    }
    fputs("}", file);

    //fputs("}", file);

    return 0;
}
*/
int main(int argc, char *argv[]) {
    if (argc!=2) {
        printf("Usage: %s <fichier.txt>\n", argv[0]);
        return 1;
    }

    // Lire le fichier .txt
    FILE *file = fopen(argv[1], "r");
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