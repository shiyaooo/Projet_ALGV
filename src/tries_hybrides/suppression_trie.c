#include "tries_hybrides.h"
#include "fonctions_avancees.h"
//#include "ecriture_lecture.h"

TrieH* lire_trie(char *content, int *index) {
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
            } else { //if () {

            }
        }
    }

    return th;

}

int main(int argc, char *argv[]) {
    if (argc!=2) {
        printf("Usage: %s <fichier.txt>\n", argv[0]);
        return 1;
    }

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





    TrieH* th = lire_trie(content, &index);

    

    fclose(file)



    return 0;
}