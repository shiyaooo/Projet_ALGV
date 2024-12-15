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

    // lecture du fichier a.json
    FILE *afile = fopen(argv[1], "rb");
    if (afile == NULL) {
        printf("Erreur lors de l'ouverture du fichier a.json\n");
        return 1;
    }
    fseek(afile, 0, SEEK_END);
    long alength = ftell(afile);
    fseek(afile, 0, SEEK_SET);
    char *acontent = (char*) malloc(alength + 1);
    fread(acontent, 1, alength, afile);
    fclose(afile);
    acontent[alength] = '\0';

    cJSON* json_a = cJSON_Parse(acontent);
    free(acontent);  // 不再需要 JSON 字符串

    if (!json_a) {
        printf("解析 JSON 失败\n");
        return 1;
    }

    PAT* pat_a = json_to_pat(json_a);

    // lecture du fichier b.json
    FILE *bfile = fopen(argv[2], "rb");
    if (bfile == NULL) {
        printf("Erreur lors de l'ouverture du fichier b.json\n");
        return 1;
    }
    fseek(bfile, 0, SEEK_END);
    long blength = ftell(bfile);
    fseek(bfile, 0, SEEK_SET);
    char *bcontent = (char*) malloc(blength + 1);
    fread(bcontent, 1, blength, bfile);
    fclose(bfile);
    bcontent[blength] = '\0';

    cJSON* json_b = cJSON_Parse(bcontent);
    free(bcontent);  // 不再需要 JSON 字符串

    if (!json_b) {
        printf("解析 JSON 失败\n");
        return 1;
    }

    PAT* pat_b = json_to_pat(json_b);

    PAT* pat = PATfusion(pat_a, pat_b);
    // Ecrire un fichier .json
    char* name_file = "pat.json";
    
    ecrire_patricia(name_file, pat);

    return 0;
}