#ifndef PATRICIA_JSON_H
#define PATRICIA_JSON_H

#include "Patricia_Tries.h"
#include <stdio.h>
#include "cJSON.h" 


/* Ecrit le patricia dans le format JSON */
int ecrire_patricia(char* namefile, PAT* arbre);

/* Construit le patricia depuis le format JSON */
PAT* json_to_pat(cJSON* json_node);

int compare_nodes(const void* a, const void* b);
void sort_children(PAT* pat);
cJSON* node_to_json(Node* node);
void print_node_json(Node* n);


cJSON* node_to_json(Node* node);
cJSON* pat_to_json(PAT* pat);
void print_pat_json(PAT* pat);

Node* json_to_node(cJSON* json_node);


#endif // PATRICIA_JSON_H