#include "../Patricia_Tries.h"
#include "../fonct_avc.h"
#include "../patricia_json.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 比较函数，用于 qsort 按字母顺序排序
int compare_strings(const void* a, const void* b) {
    const char* str_a = *(const char**)a;
    const char* str_b = *(const char**)b;
    return strcmp(str_a, str_b);
}

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



    // 解析 JSON 字符串
    cJSON* json = cJSON_Parse(content);
    free(content);  // 不再需要 JSON 字符串

    if (!json) {
        printf("解析 JSON 失败\n");
        return 1;
    }


    PAT* pat = json_to_pat(json);

    cJSON_Delete(json);  // 解析完成后删除 JSON 对象

    // printf("pat is \n");
    // printPAT(pat);

    
    // lecture du fichier .txt
    // et suppressions successives des mots dans le trie hybride
    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier .txt\n");
        return 1;
    }
    
    // 动态分配字符串指针数组
    char** listmot = NULL;
    size_t list_size = 0;

    char line[256];
    // while (fgets(line, sizeof(line), file)) {
    //     line[strcspn(line, "\n")] = '\0';
    //     printf("mots is %s_\n", line);
    //     PATsuppression(&pat, line);
    // }
    // fclose(file);

    while (fgets(line, sizeof(line), file)) {
        // 去掉末尾换行符
        line[strcspn(line, "\n")] = '\0';

        // 跳过空行
        if (line[0] == '\0') {
            continue;
        }

        // 动态扩展字符串指针数组
        listmot = realloc(listmot, (list_size + 1) * sizeof(char*));
        if (!listmot) {
            perror("Erreur de realloc");
            fclose(file);
            return -1;
        }

        // 动态分配内存保存字符串
        listmot[list_size] = malloc(strlen(line) + 1);
        if (!listmot[list_size]) {
            perror("Erreur de malloc");
            fclose(file);
            return -1;
        }
        strcpy(listmot[list_size], line);
        list_size++;
    }

    fclose(file);

    // 排序字符串列表
    qsort(listmot, list_size, sizeof(char*), compare_strings);

    for (int i = 0; i < list_size; i++) {
        // printf("mots is %s_\n", listmot[i]);
        PATsuppression(&pat, listmot[i]);
    }

    // printf("apes supprmer\n");
    // printPAT(pat);
    // Ecrire un fichier .json
    char* name_file = "pat.json";
    
    ecrire_patricia(name_file, pat);

    return 0;
}