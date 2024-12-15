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

    // lecture de trie.json
    FILE *file = fopen("pat.json", "rb");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier .json\n");
        return 1;
    }
     // 获取文件大小
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // 为文件内容分配内存
    char* content = (char*)malloc(file_size + 1);
    if (!content) {
        printf("内存分配失败\n");
        fclose(file);
        return 1;
    }

     // 读取文件内容
    fread(content, 1, file_size, file);
    content[file_size] = '\0'; // 确保字符串以 '\0' 结尾

    fclose(file);

    // content[length] = '\0';
    // printf("content is %s \n", content);


    // 解析 JSON 字符串
    cJSON* json = cJSON_Parse(content);
    free(content);  // 不再需要 JSON 字符串

    if (!json) {
        printf("解析 JSON 失败\n");
        return 1;
    }

    char* json_str = cJSON_Print(json);

    PAT* pat = json_to_pat(json);
    

    cJSON_Delete(json);  // 解析完成后删除 JSON 对象

    printf("pat is \n");
    printPAT(pat);

    
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
        line[strcspn(line, "\n")] = '\0';
        printf("mots is %s\n", line);
        PATsuppression(&pat, line);
    }
    fclose(file);

    // Ecrire un fichier .json
    char* name_file = "pat.json";
    
    ecrire_patricia(name_file, pat);


    fclose(file);
    
    return 0;
}