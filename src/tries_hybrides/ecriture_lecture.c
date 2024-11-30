#include "ecriture_lecture.h"
#include <stdio.h>
#include <stdlib.h>

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
        fputs("\"is_end_of_world\": false,\n", file);
    } else {
        fputs("\"is_end_of_world\": true,\n", file);
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
    
    for(int i=0;i<nouvtab;i++) {
        fputc('\t', file);
    }
    fputs("}\n", file);

    return 0;
}