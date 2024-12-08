#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "Patricia_Tries.h"
#include <ctype.h>  // 包含字符分类函数


//gcc -Wall -o main main.c Patricia_Tries.c

/*****************************EX1*****************************/
// Question 1.2 Encoder les primitives de base concernant les Patricia-tries.

/* Fonction pour créer un nœud vide */
Node* Nodevide(){
    return NULL;
}

/* Fonction pour créer un PAT vide */
PAT* PATVide(){
    return NULL;
}

/* Fonction pour créer un noeud*/
Node* NodeCons(char* m){
    Node* A =(Node*) malloc(sizeof(Node));
    if (A == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour Node\n");
        exit(1);
    }
    A -> cle = strdup(m);
    int len = strlen(A->cle);
    if(A->cle[len-1] == ' '){
        A -> valeur = 1;
    }else{
        A -> valeur = 0;
    } 
    
    A -> fils = NULL; // Pas de sous-fils initialement
    //A-> est_fin = false; 
    return A;
}

/* Fonction pour créer un arbre null*/
PAT* creer_PAT(){
    PAT* P =(PAT*) malloc(sizeof(PAT));
    // P -> racine = NULL;
    P -> node = NULL;
    return P;
}

/* Fonction pour créer un arbre avec un seul nœud */
PAT* PATCons(Node* n){
    PAT* P =(PAT*) malloc(sizeof(PAT));
    if(!P){
        fprintf(stderr,"Erreur: Allocation de mémoire échouée pour PAT.\n");
        exit(EXIT_FAILURE);
    }
    // Allouer la mémoire pour la liste dynamique des racines (avec un seul élément au départ)
    // P->racine = (Node**)malloc(2 * sizeof(Node*)); // Un nœud + NULL pour terminer
    // if (!P->racine) {
    //     fprintf(stderr, "Erreur : Allocation de mémoire échouée pour la racine.\n");
    //     free(P);
    //     exit(EXIT_FAILURE);
    // }

     P->node = (Node**)malloc(2 * sizeof(Node*)); // Un nœud + NULL pour terminer
    if (!P->node) {
        fprintf(stderr, "Erreur : Allocation de mémoire échouée pour la racine.\n");
        free(P);
        exit(EXIT_FAILURE);
    }

    // Initialiser le tableau avec le nœud donné
    // P->racine[0] = n;
    // P->racine[1] = NULL; // Terminaison de la liste
    P->node[0] = n;
    P->node[1] = NULL; // Terminaison de la liste

    return P;
}

/* renvoie 1 ssi l'arbre A est vide, 0 sinon */
int EstVideNode(Node* A){
     if (A != NULL) {
        return 0;
    }
    return 1;
}

int EstVide(PAT* A){
     if (A != NULL) {
        return 0;
    }
    return 1;
}

/* renvoie la clé du noeud*/
char* Rac(Node* A){
    return A -> cle;
}

/* renvoie l'entier du noeud, -1 sinon */
int Val(Node* A){
    if(A == NULL){
        return -1;
    }
    return A -> valeur;
}

/* Fonction pour afficher un noeud (parcours en profondeur) */
void printNode(Node* A, int indentation){
    if(EstVideNode(A) == 1) return;

    for(int i =0; i < indentation ; i++){
        printf("  ");  // Indentation pour chaque niveau
    }

    printf("(%s, %d)\n", A -> cle, A -> valeur);

    // Afficher les enfants du nœud
    // for(int i = 0; A -> fils != NULL && A -> fils[i] != NULL; i++){
    //     printNode(A->fils[i], indentation + 1);
    // }
    for(int i = 0; A -> fils != NULL && A -> fils->node[i] != NULL; i++){
        printNode(A->fils->node[i], indentation + 1);
    }
}

/* Fonction pour afficher tout le Patricia Trie */
void printPAT(PAT* P){
    // if (!P || !P->racine) return;
    if (!P || !P->node) return;
    

    // Parcourir les racines du Patricia Trie
    // for(size_t i = 0; P->racine[i] != NULL; i++){
    //     printNode(P -> racine[i], 0);
    // }

    for(size_t i = 0; P->node[i] != NULL; i++){
        printNode(P -> node[i], 0);
    }
}

// Fonction pour libérer la mémoire du noeud
void libererNode(Node* A){
    if(EstVideNode(A) == 1) return;

    // Libérer la mémoire des enfants
    if (A->fils != NULL) {
        if(A->fils->node!=NULL){
            for (int i = 0; A->fils->node[i] != NULL; i++) {
                libererNode(A->fils->node[i]);
            }
            // Libérer le tableau des fils
            free(A->fils->node);
        }
        free(A->fils);
    }
    // Libérer la mémoire allouée pour la clé (chaîne de caractères)
    free(A->cle);
    // Libérer le nœud lui-même
    free(A);
}

// Fonction pour libérer la mémoire de l'arbre
void libererPAT(PAT* A){
    if(EstVide(A) == 1) return;

    // Libérer la mémoire des enfants
    if(A->node != NULL){
        int i =0;
        while(A -> node[i] != NULL){
            libererNode(A->node[i]);
            i++;
        }
        // Libérer la mémoire allouée pour le tableau
        free(A->node);
    }

    // Libérer le nœud lui-même
    free(A);
}

// Fonction pour ajouter un enfant à un nœud
void ajouter_fils(Node* A, Node* fil ){
    if(EstVideNode(A) ==  1){
        fprintf(stderr, "Erreur: Le parent est NULL. Impossible d'ajouter un enfant\n");
    }

    if(A->fils == NULL){ // Le tableau lui-même ne stocke pas le nombre actuel de nœuds enfants. En ajoutant un pointeur NULL à la fin du tableau, le programme peut facilement savoir où se termine la liste des nœuds enfants, évitant ainsi les accès hors limites.
        A->fils = (PAT*) malloc(sizeof(PAT));
        A->fils->node = (Node**) malloc(2* sizeof(Node*));
        A->fils->node[0] = fil; // Ajouter le premier enfant
        A->fils->node[1] = NULL; // Marquer la fin de la liste
    }else{
        // Si des enfants existent déjà, compter leur nombre
        int i = 0;
        while(A->fils->node[i]!=NULL) i++;
        
        // Agrandir le tableau pour un nouvel enfant
        Node** temp = (Node**) realloc(A->fils->node, (i + 2) * sizeof(Node*));
        if (temp == NULL) {
            fprintf(stderr, "Erreur de réallocation de mémoire\n");
            exit(1);
        }
        A->fils->node = temp;
        A->fils->node[i] = fil;  // Ajouter le nouvel enfant
        A->fils->node[i+1] = NULL; // Mettre à jour le terminateur

    }

}

// Fonction pour ajouter une racine
void ajouter_racine(PAT** P, Node* r){
    if(!r){
        fprintf(stderr, "Erreur: noeud invalide.\n");
    }
    if(*P == NULL){
        *P = PATCons(r);
    }

    PAT* trie = *P;

    // Si le tableau de racines n'existe pas encore
    if (trie->node == NULL) {
        trie->node = (Node**) malloc(2 * sizeof(Node*));
        trie->node[0] = r;
        trie->node[1] = NULL; // Terminateur
        return;
    }

    int taille  = 0;
    while(trie->node[taille] != NULL){
        taille ++;
    } 

    // Redimensionner le tableau
    //trie->node = (Node**) realloc(trie->node,(taille+2)*sizeof(Node*)); 
    Node** temp = (Node**) realloc(trie->node, (taille+2) * sizeof(Node*));
    // Ajouter le nouveau nœud et terminer par NULL
    trie -> node = temp;
    trie->node[taille] = r;
    trie->node[taille + 1] = NULL;

}

// Fonction pour insérer un mot dans l'arbre
void PATinsertion(PAT** A, char* m) {
    if(EstVide(*A) == 1){
        // Cas où l'arbre est vide : on crée un nouveau nœud avec tout le mot
        if(m == NULL){
            Node* n = NodeCons(END_OF_WORD);
            *A = PATCons(n);
        }else{
            char* tmp = malloc((strlen(m)+1)*sizeof(char)); //("abc\0")
            strcpy(tmp, m) ;
            tmp = realloc(tmp,(strlen(tmp)+2)*sizeof(char));
            strcat(tmp,END_OF_WORD);
            Node* n = NodeCons(tmp);
            *A = PATCons(n);
            free(tmp);
        }
    }else if(m == NULL){
        Node* n = NodeCons(END_OF_WORD);
        *A = PATCons(n);
    }else{
        char t = *m;
        Node* c = Nodevide();
        for(int i = 0; (*A)->node[i]!= NULL; i++){
            if((*A)->node[i]->cle[0] == t){
                c = (*A)->node[i];
                break;
            }
        }

        if(c == NULL){
            char* tmp = malloc((strlen(m)+1)*sizeof(char)); //("abc\0")
            strcpy(tmp, m) ;
            tmp = realloc(tmp,(strlen(tmp)+2)*sizeof(char));
            strcat(tmp,END_OF_WORD);
            Node* n = NodeCons(tmp);
            ajouter_racine(A, n);
            free(tmp);
        }else{
            if(estPrefixe(c->cle, m) == 1){
                // printf("ici\n");
                // printf("c, m = %s, %s\n", c->cle, m);
                int len_c = strlen(c->cle);  // Longueur de la chaîne `c`
                if(c->cle[len_c -1] == ' ') len_c --;
                
                int len_m = strlen(m);  // Longueur de la chaîne `m`
                if(m[len_m -1] == ' ') len_m --;

                if(len_c == len_m){
                    bool find = false;
                    printf("egal:");
                    printf("c, m = %s, %s\n", c->cle, m);
                    if(c->fils == NULL) c->valeur ++;           
                    else{
                        int val = c->valeur;
                        int i = 0;
                        while(c->fils->node[i]!=NULL){
                            if(strcmp(c->fils->node[i]->cle, END_OF_WORD) == 0){
                                c->fils->node[i]->valeur++;
                                find = true;
                                break;
                            }
                            i++;
                        }
                        if(find == false){
                            c->valeur = 0;
                            int i = 0;
                            while(c->fils->node[i]!=NULL) i++;
                            Node** temp = (Node**) realloc(c->fils->node, (i + 2) * sizeof(Node*));
                            if (temp == NULL) {
                                fprintf(stderr, "Erreur de réallocation de mémoire\n");
                                exit(1);
                            }
                            c->fils->node = temp;
                            c->fils->node[i] = NodeCons(END_OF_WORD);  // Ajouter le nouvel enfant
                            c->fils->node[i]->valeur = val+1;
                            c->fils->node[i+1] = NULL; // Mettre à jour le terminateur

                        }
                    }
                    
                }else{
                    char* reste_m = m + len_c;
                    PATinsertion(&(c->fils), reste_m);
                }

            // }else if(estPrefixe(m, c->cle) == 1){
            //     int len_c = strlen(c->cle);  // Longueur de la chaîne `c`
            //     if(c->cle[len_c -1] == ' ') len_c --;
                
            //     int len_m = strlen(m);  // Longueur de la chaîne `m`
            //     if(m[len_m -1] == ' ') len_m --;

                
            //     char* reste_c = c -> cle + len_m; 
            //     Node* new_node = NodeCons(reste_c);
            //     new_node -> fils = c->fils; // Reprendre les enfants existants

            //     c -> cle = strdup(m); // Mettre à jour la clé du parent 
            //     //c ->valeur = 1;
            //     c -> fils = NULL; // Réinitialiser les enfants
            //     ajouter_fils(c, new_node);
            }else{
                int len_com = prefixe(c->cle, m);
                char* reste_c = c->cle + len_com;         // Le reste de `c`        
                char* reste_m = m + len_com;         // Le reste de `m`

                Node* fc = NodeCons(reste_c);
                fc->fils = c ->fils;

                // Créer un nouveau nœud pour le reste du mot
                char* tmp = malloc((strlen(m)+1)*sizeof(char)); //("abc\0")
                strcpy(tmp, reste_m) ;
                tmp = realloc(tmp,(strlen(tmp)+2)*sizeof(char));
                strcat(tmp,END_OF_WORD);
                
                Node *fm = NodeCons(tmp);

                // Mettre à jour le nœud actuel pour contenir uniquement le préfixe commun 
                // stocker clé ancienne
                char* old_cle = c->cle;

                // utilser strndup pour créer une nouvelle cle
                c->cle = strndup(old_cle, len_com);                         
                c->valeur = 0;
                c->fils = NULL; // Réinitialiser les enfants
                ajouter_fils(c, fc);
                ajouter_fils(c, fm);
                free(tmp);
                // free cle acienne
                if (old_cle != NULL) {
                    free(old_cle);
                }
            }
        }
    }
}

// Foction pour verifier c est préfixe de m, si oui -> 1, sinon 0
int estPrefixe (char*c , char* m){
    int len_c = strlen(c);  // Longueur de la chaîne `c`
    if(c[len_c -1] == ' '){
        len_c --;
    }
    int len_m = strlen(m);  // Longueur de la chaîne `m`
    if(m[len_m -1] == ' '){
        len_m --;
    }

    // Si `c` est plus long que `m`, ce ne peut pas être un préfixe
    if (len_c > len_m) {
        return 0;
    }

    // Comparaison caractère par caractère
    for(int i =0; i < len_c ; i++){
        if(c[i] != m[i]) return 0;
    }    

    // Extraire la sous-chaîne restante de `m` après `c`
    // char* reste_m = m + len_c;  // Pointeur pointant sur le reste de la chaîne `m` après `c`

    // Afficher la sous-chaîne restante pour vérification
    // printf("Le reste de 'm' après '%s' est : '%s'\n", c, reste_m);
    return 1;
}

int prefixe(char* c, char* m){
    int common = 0;
    int len_c = strlen(c);  // Longueur de la chaîne `c`
    if(c[len_c -1] == ' '){
        len_c --;
    }
    int len_m = strlen(m);  // Longueur de la chaîne `m`
    if(m[len_m -1] == ' '){
        len_m --;
    }

    // Trouver la longueur minimale des deux chaînes
    int min_length = len_c < len_m ? len_c : len_m;

    // Comparer les caractères des deux chaînes et construire le préfixe
    for(int i =0; i< min_length; i++){
        if(c[i]==m[i]) common++;
        else break;
    }
    return common;
}

void splitSentence(char *sentence) {
    char word[MAX_SIZE];  // 用来存储当前的单词
    int wordIndex = 0;    // 用来标记当前单词的位置
    char *ptr = sentence; // 指向当前字符

    while (*ptr != '\0') {
        if (isalpha(*ptr) || isdigit(*ptr)) {
            // 如果是字母或数字，构建单词
            word[wordIndex++] = *ptr;
        } else if (ispunct(*ptr)) {
            // 如果是标点符号，打印当前单词并打印标点符号
            if (wordIndex > 0) {
                word[wordIndex] = '\0';  // 结束当前单词
                printf("Mot: %s\n", word);  // 打印单词
                wordIndex = 0;  // 重置单词位置
            }
            printf("Ponctuation: '%c'\n", *ptr);  // 打印标点符号
        } else if (isspace(*ptr)) {
            // 如果是空格，打印当前单词
            if (wordIndex > 0) {
                word[wordIndex] = '\0';  // 结束当前单词
                printf("Mot: %s\n", word);  // 打印单词
                wordIndex = 0;  // 重置单词位置
            }
        }
        ptr++;  // 移动到下一个字符
    }

    // 打印最后一个单词（如果有的话）
    if (wordIndex > 0) {
        word[wordIndex] = '\0';
        printf("Mot: %s\n", word);
    }
}

