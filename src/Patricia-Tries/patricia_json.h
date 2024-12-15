#ifndef PATRICIA_JSON_H
#define PATRICIA_JSON_H

#include "Patricia_Tries.h"
#include <stdio.h>
#include "cJSON.h" 


/* Ecrit le patricia dans le format JSON */
int ecrire_patricia(char* namefile, PAT* arbre);

// /* Modifie la valeur de cpt */
// void setCpt(int valeur);

// /* Construit le patricia depuis le format JSON */
// PAT* charger_patricia(char *content, int *index);

int compare_nodes(const void* a, const void* b);
void sort_children(PAT* pat);
cJSON* node_to_json(Node* node);
void print_node_json(Node* n);


cJSON* node_to_json(Node* node);
cJSON* pat_to_json(PAT* pat);
void print_pat_json(PAT* pat);

#endif // PATRICIA_JSON_H