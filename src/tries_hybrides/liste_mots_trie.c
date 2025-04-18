#include "tries_hybrides.h"
#include "fonctions_avancees.h"
#include "ecriture_lecture.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc!=2) {
        printf("Usage: %s <arbre.json>\n", argv[0]);
        return 1;
    }

    // lecture du fichier .json
    FILE *file = fopen(argv[1], "rb");
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


    // Ecrire le fichier mot.txt
    file = fopen("mot.txt", "w");

    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier .txt\n");
        return 1;
    }

    // liste les mots contenus dans l'arbre dans le fichier mot.txt
    List* liste = ListeMots(th);
    //int i = 1;
    List* tmp = liste;
    while (tmp!=NULL) {
        fprintf(file, "%s\n", tmp->mot);
        tmp = tmp->suiv;
        //i++;
    }

    fclose(file);

    return 0;
}