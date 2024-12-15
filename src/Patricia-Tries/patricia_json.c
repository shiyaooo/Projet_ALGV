#include "patricia_json.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Ecrit le patricia dans le format JSON */
int ecrire_patricia(char* namefile, PAT* arbre){
    // 打开文件进行写入
    FILE* file = fopen(namefile, "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier .json\n");
        return 1;
    }

    if (EstVide(arbre)==1) {
        fputs("null", file);
        return 1;
    }

    // 如果树不为空，获取其 JSON 表示
    cJSON* json_arbre = pat_to_json(arbre);
    if (json_arbre == NULL) {
        printf("Erreur lors de la conversion de l'arbre en JSON\n");
        return 1;
    }

    // 将 JSON 格式的数据写入文件
    char* json_string = cJSON_Print(json_arbre);
    if (json_string == NULL) {
        printf("Erreur lors de la conversion de l'arbre en chaîne JSON\n");
        cJSON_Delete(json_arbre);
        return 1;
    }

    fputs(json_string, file);  // 将字符串写入文件

    printf("Successful!\n");
    // 释放分配的内存
    free(json_string);
    cJSON_Delete(json_arbre);

    return 0;  // 成功写入文件
    
}


int compare_nodes(const void* a, const void* b) {
    Node* nodeA = *((Node**)a);
    Node* nodeB = *((Node**)b);
    return strcmp(nodeA->cle, nodeB->cle);  // 按字母顺序比较字符串
}

void sort_children(PAT* pat) {
    if (pat && pat->node) {
        int fils_count = 0;
        while (pat->node[fils_count] != NULL) {
            fils_count++;  // 计算 node 数组中的元素数量
        }

        qsort(pat->node, fils_count, sizeof(Node*), compare_nodes);  // 使用 qsort 排序
    }
}


// 递归转换 PAT 树为 JSON
cJSON* node_to_json(Node* node) {
    cJSON* json_node = cJSON_CreateObject();

    // 将节点信息添加到 JSON 对象中
    cJSON_AddStringToObject(json_node, "label", node->cle);
    if(node->cle[strlen(node->cle)-1] == ' '){
        cJSON_AddBoolToObject(json_node, "is_end_of_word", true);
    }else{
        cJSON_AddBoolToObject(json_node, "is_end_of_word", false);
    }
    // cJSON_AddNumberToObject(json_node, "valeur", node->valeur);

    // 如果该节点有子节点，递归添加子节点
    cJSON* json_fils = cJSON_CreateObject();
    if (node->fils != NULL) {

        sort_children(node->fils);  // 确保子节点按字母顺序排序
        
        for (int i = 0; node->fils->node[i] != NULL; ++i) {
            if(strcmp(node->fils->node[i]->cle, END_OF_WORD) == 0){
                // cJSON_AddBoolToObject(json_node, "is_end_of_word", true);
                cJSON_ReplaceItemInObject(json_node, "is_end_of_word", cJSON_CreateBool(true));
            }else{
                char key[2]; // 1 个字符加上 '\0' 终止符
                key[0] = node->fils->node[i]->cle[0];
                key[1] = '\0';
                cJSON* child_json = node_to_json(node->fils->node[i]);
                cJSON_AddItemToObject(json_fils,key, child_json);
            }
        }
        cJSON_AddItemToObject(json_node, "children", json_fils);
    }else{
        cJSON_AddItemToObject(json_node, "children", json_fils);
    }
    return json_node;
}

void print_node_json(Node* n){
    cJSON* json_node = node_to_json(n);
    char* json_str = cJSON_Print(json_node);
    printf("%s\n", json_str);
    free(json_str);
    cJSON_Delete(json_node);
}


// 将整个 PAT 树转换为 JSON 格式

cJSON* pat_to_json(PAT* pat) {
    cJSON* json_pat = cJSON_CreateObject();

    cJSON_AddStringToObject(json_pat, "label", "");
    if(pat->node == NULL){
        cJSON_AddBoolToObject(json_pat, "is_end_of_word", true);
    }else{
        cJSON_AddBoolToObject(json_pat, "is_end_of_word", false);
    }


    // 如果 pat 存在，并且它的子节点数组非空
    if (pat != NULL && pat->node != NULL) {
        // 确保对子节点按字母顺序排序
        int fils_count = 0;
        while (pat->node[fils_count] != NULL) {
            fils_count++;  // 计算子节点数量
        }

        qsort(pat->node, fils_count, sizeof(Node*), compare_nodes);  // 按字母顺序排序子节点

        // 创建一个用于存储子节点的 JSON 对象
        cJSON* json_children = cJSON_CreateObject();

        // 对每个子节点调用 node_to_json，将其转换为 JSON，并添加到子节点对象中
        for (int i = 0; i < fils_count; ++i) {
            Node* current_node = pat->node[i];  // 当前子节点
            char key[2]; // 1 个字符加上 '\0' 终止符
            key[0] = current_node->cle[0];
            key[1] = '\0';
            cJSON* child_json = node_to_json(current_node);  // 获取当前子节点的 JSON 表示
            cJSON_AddItemToObject(json_children, key, child_json);  // 添加到 JSON 对象
        }

        // 将子节点添加到 PAT 的 JSON 对象中
        cJSON_AddItemToObject(json_pat, "children", json_children);
    } else {
        // 如果没有子节点，添加空的 children 对象
        cJSON_AddItemToObject(json_pat, "children", cJSON_CreateObject());
    }

    return json_pat;
}

// 打印 PAT 树的 JSON 格式
void print_pat_json(PAT* pat) {
    cJSON* json_pat = pat_to_json(pat);
    char* json_str = cJSON_Print(json_pat);
    printf("%s\n", json_str);
    free(json_str);
    cJSON_Delete(json_pat);
}
