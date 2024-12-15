#include "../Patricia_Tries.h"
#include "../fonct_avc.h"
#include "../patricia_json.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc!=3) {
        printf("Usage: %s <arbre.json> <s>\n", argv[0]);
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

    cJSON* json = cJSON_Parse(content);
    free(content);  // 不再需要 JSON 字符串

    if (!json) {
        printf("解析 JSON 失败\n");
        return 1;
    }

    PAT* pat = json_to_pat(json);


    // Ecrire le fichier prefixe.txt
    file = fopen("prefixe.txt", "w");

    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier .txt\n");
        return 1;
    }

    // écrit le nombre de mots dont s est prefixe dans le fichier prefixe.txt
    int nbmots = PrefixedansPAT(pat, argv[2]);
    fprintf(file, "%d", nbmots);

    fclose(file);

    return 0;
}