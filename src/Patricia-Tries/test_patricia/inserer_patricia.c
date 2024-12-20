#include "../Patricia_Tries.h"
#include "../fonct_avc.h"
#include "../patricia_json.h"
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
    PAT* pat = NULL;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        //printf("%s", line);
        line[strcspn(line, "\n")] = '\0';
        PATinsertion(&pat, line);
        cpt++;
    }
    fclose(file);
    
    // Ecrire un fichier .json
    char* name_file = "pat.json";
    
    ecrire_patricia(name_file, pat);

    return 0;
}