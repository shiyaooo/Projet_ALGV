#include "ecriture_lecture.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Ecrit le trie hybride dans le format JSON */
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

int cpt = 0;    // pour attribuer un identifiant unique

/* Modifie la valeur de cpt */
void setCpt(int valeur) {
    cpt = valeur;
}

/* Construit le trie hybride depuis le format JSON */
TrieH* charger_trie(char *content, int *index) {
    TrieH *th = (TrieH*) malloc(sizeof(TrieH));
    memset(th, 0, sizeof(TrieH));   // Initialiser à zéro

    // Parsing
    while (content[*index] != '\0') {
        if (content[*index] == '\"') {
            (*index)++;
            if (strncmp(&content[*index], "char", 4) == 0) {
                *index += 8;
                //printf("%c\n",content[*index]);
                th->l = content[*index];
                *index += 3;
            } else if (strncmp(&content[*index], "is_end_of_word", 14) == 0) {
                *index += 17;
                if (strncmp(&content[*index], "false", 5) == 0) {
                    th->v = -1;
                    *index += 6;
                } else {
                    th->v = cpt;
                    cpt++;
                    *index += 5;    // true
                }
            } else if (strncmp(&content[*index], "left", 4) == 0) {
                *index+=7;
                if (strncmp(&content[*index], "null", 4) == 0) {
                    *index+=5;
                    th->inf = TH_Vide();
                } else {
                    //*index+=1;
                    th->inf = charger_trie(content, index);
                }
            } else if (strncmp(&content[*index], "middle", 6) == 0) {
                *index+=9;
                 if (strncmp(&content[*index], "null", 4) == 0) {
                    *index+=5;
                    th->eq = TH_Vide();
                } else {
                    //*index+=1;
                    th->eq = charger_trie(content, index);
                }
            } else if (strncmp(&content[*index], "right", 5) == 0) {
                *index+=8;
                 if (strncmp(&content[*index], "null", 4) == 0) {
                    *index+=4;
                    th->sup = TH_Vide();
                } else {
                    //*index+=1;
                    th->sup = charger_trie(content, index);
                }
            }
        } else if (strncmp(&content[*index], "}", 1) == 0) {
            *index+=1;
            return th;
        } else {
            (*index)++;
        }
    }
    return th;
}