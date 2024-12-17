#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "Patricia_Tries.h"
#include "fonct_avc.h"
#include <ctype.h>  // 包含字符分类函数

/*****************************EX2*****************************/

int nombre_node(PAT* pat){
    int cmpt = 0;
    for(int i = 0; pat->node[i]!= NULL; i++){
        Node * racine_actuelle = pat->node[i];
            if(racine_actuelle->fils!=NULL){
                PAT* sous_arbre = (PAT*) racine_actuelle->fils;
                cmpt += nombre_node(sous_arbre); 
            }      
        cmpt ++;
    }
    return cmpt ;
}

bool recherchePAT_cpt(PAT* A, char* mot, int* cpt) { // O(l * log n) où l = longeur de mot et n = nb total de racine
    if (A == NULL || mot == NULL) {
        return false; // Patricia Trie vide ou mot invalide
    }else{
   
        // Parcourir les racines de la Patricia Trie
        for (int i = 0; A->node[i] != NULL; i++) {
             (*cpt)++;
            Node* racine_actuelle = A->node[i];
            char* cle = racine_actuelle->cle;
            //printf("cle %s\n",cle);

            (*cpt)++;
            if(cle[0] == mot[0]){
                // Vérifier si le mot ou un préfixe correspond
                int longueur_commune = 0;
                while (cle[longueur_commune] != '\0' && mot[longueur_commune] != '\0' && cle[longueur_commune] == mot[longueur_commune]) {
                    (*cpt)++;
                    // printf("cle[longueur_commune] = %c\n",cle[longueur_commune]);
                    // printf(" mot[longueur_commune]  = %c\n", mot[longueur_commune]);
                    longueur_commune++;
                    // printf("len_com: %d\n",longueur_commune);
                }
                
                (*cpt)++;
                if ((cle[longueur_commune] == '\0' || cle[longueur_commune]==' ') && mot[longueur_commune] == '\0' ) {
                    (*cpt)++;
                    if(racine_actuelle ->valeur > 0){
                        // Le mot complet a été trouvé
                        return true;
                    }else{
                        int j = 0;
                        while(racine_actuelle->fils != NULL && racine_actuelle->fils->node[j]!=NULL ){
                            (*cpt)++; // 比较子节点的键
                            if(strcmp(racine_actuelle->fils->node[j]->cle, END_OF_WORD) == 0){
                                return true;
                            }
                            j++;
                        }
                    }    
                    // return racine_actuelle ->valeur >0;
                }

                (*cpt)++;
                if (cle[longueur_commune] == '\0') {
                    // On continue la recherche dans les enfants pour le reste du mot
                    char* reste_mot = mot + longueur_commune;
                    // printf("mot rest est  %s\n",reste_mot);
                    // printPAT(racine_actuelle->fils->node[0]->fils);
                    return recherchePAT_cpt((PAT*)racine_actuelle->fils, reste_mot, cpt);
                }
            }
        }
    }
    // Si aucune correspondance n'est trouvée
    return false;
}

// fonction qui compte les mots présents dans le dictionnaire : 
int ComptageMotsdansPAT_cpt(PAT* A, int* cpt){ // O(n) où n = nb de noeud
    if(A == NULL){
        return 0;
    }
    int cmpt = 0;

    // Parcourir tous les nœuds de la racine
    for(int i = 0; A->node[i]!=NULL; i++){
        (*cpt)++; // 增加比较次数：访问节点

        Node* racine_actuelle = A->node[i];

        // Si le nœud contient une valeur > 0, il correspond à un mot
        if (racine_actuelle->valeur > 0) {
            
            cmpt += 1; // Ajouter le nombre de mots enregistrés dans ce nœud
        }

        // Parcourir les sous-arbres (enfants)
        if(racine_actuelle->fils!=NULL){
            PAT* sous_arbre = (PAT*) racine_actuelle->fils;
            cmpt += ComptageMotsdansPAT_cpt(sous_arbre, cpt);  
        }
    }
    return cmpt;
}

// fonction qui liste les mots du dictionnaire dans l’ordre alphabétique :

// Fonction de comparaison pour trier les fils
// int comparemots(const void* a, const void* b) { // O(1)
//     char* A = *(char**) a;
//     char* B = *(char**) b;
//     return strcmp(A, B);
// }

// Fonction auxiliaire récursive pour collecter les mots
void collecterMots_cpt(Node* racine, char* prefixe, char*** resultats, int* taille, int* capacite, int* cpt) { // O(n) n= nb de noeud dans un noeud
    if(racine == NULL) return;
    (*cpt)++; // 增加比较次数：访问节点

    // Construire le mot courant en concaténant le préfixe et la clé du nœud
    char* mot_courant = (char*) malloc((strlen(prefixe)+strlen(racine->cle)+1)*sizeof(char));
    strcpy(mot_courant, prefixe);
    strcat(mot_courant, racine->cle);


    // printf("mot courant %s\n", mot_courant);
    // Si ce nœud marque la fin d'un mot
    if(racine -> valeur > 0){
        //Redimensionner le tab si nécessaire
        if(*taille >= *capacite){
            *capacite *=2;
            *resultats = (char**) realloc(*resultats, (*capacite)*sizeof(char*));
        }

        //ajouter le mot au tab
        if(mot_courant[strlen(mot_courant)-1]==' '){
            // printf("mot courant %sf\n", mot_courant);
            (*resultats)[*taille] = strndup(mot_courant, strlen(mot_courant)-1);
        }else{
            (*resultats)[*taille] = strdup(mot_courant);
        }
        (*taille)++;
    }

    //Parcourir les sous-fils
    if(racine->fils != NULL){
        for(int i = 0; racine->fils->node[i] != NULL; i++){
            (*cpt)++;
            if(mot_courant[strlen(mot_courant)-1]==' '){
                mot_courant = strndup(mot_courant, strlen(mot_courant)-1);
            }
            collecterMots_cpt(racine->fils->node[i], mot_courant, resultats, taille, capacite, cpt);
        }
    }

    //Libérer la mem temporaire pour 'mot_courant'
    free(mot_courant);
}


char** ListeMotsdansPAT_cpt(PAT* A, int* cpt){ // O()
    (*cpt)++; // 增加比较次数：检查树是否为空
    if(A == NULL) return NULL;
    //Initialiser le tab de résultat
    int cap = 10;
    int taille = 0;
    char** res = (char**) malloc(cap*sizeof(char*));

    //Parcourir toutes les racines
    for(int i = 0; A->node[i]!=NULL; i++){
        (*cpt)++; // 增加比较次数：检查树是否为空
        collecterMots_cpt(A->node[i],"", &res, &taille, &cap, cpt);
    }

    //Redimensionner le tab pour correspondre à la taille réelle
    res = (char**)realloc(res,(taille+1)*sizeof(char*));
    res[taille] = NULL;
    qsort(res, taille,sizeof(res), comparemots);
    (*cpt) += taille; // 增加比较次数：排序操作

    return res;
}

// une fonction qui compte les pointeurs vers Nil :
int ComptageNildansNode_cpt(Node* n, int* cpt){ //O(n)
    if(n == NULL) return 1;
    int cmpt =0;

    if (n->fils != NULL) {
        int i = 0;
        // Parcourir les fils du nœud
        while (n->fils->node[i] != NULL) {
            // (*cpt) ++;
            cmpt += ComptageNildansNode(n->fils->node[i]);
            i++;
        }
        // Ajouter le pointeur NULL qui termine le tableau de fils
        cmpt++;
    } else {
        (*cpt) ++;
        // Si le tableau de fils est NULL, compter ce pointeur
        cmpt++;
    }

    return cmpt;

}

int ComptageNildansPAT_cpt(PAT* A, int* cpt){ // O(n)
    if (A == NULL || A->node == NULL) {
        return 1; // Un pointeur NULL trouvé pour un arbre vide
    }

    int compteur = 0;
    int i = 0;
    // Parcourir les racines de l'arbre
    while (A->node[i] != NULL) {
        (*cpt) ++;
        compteur += ComptageNildansNode_cpt(A->node[i],cpt);
        i++;
    }

    // Ajouter le pointeur NULL qui termine le tableau des racines
    compteur++;
    return compteur;
}

// une fonction qui calcule la hauteur de l’arbre : 
int HauteurNode_cpt(Node* n, int* cpt) { // O(log n)
    (*cpt)++;
    if(n == NULL) return 0; // Hauteur d'un nœud NULL est 0

    int h_max = 0;

    if(n->fils!=NULL){
        for(int i = 0; n->fils->node[i]!=NULL; i++){
            // (*cpt) ++;
            // Calculer la hauteur maximale parmi tous les fils
            int h_f = HauteurNode_cpt(n->fils->node[i], cpt);
            if(h_f > h_max){
                h_max = h_f;
            }
        }
    }
    // La hauteur d'un nœud est 1 (lui-même) + hauteur maximale de ses fils
    return 1 + h_max;
}

int HauteurPAT_cpt(PAT* A, int* cpt){ // O(n)
    if(A == NULL) return 0;

    int h_max = 0;
    for(int i = 0; A->node[i] != NULL; i++){
        // (*cpt)++;
        int h_racine = HauteurNode_cpt(A->node[i], cpt);
        if(h_racine > h_max){
            h_max = h_racine;
        }
    }
    return h_max; // Retourner la hauteur maximale parmi toutes les racines
}

// une fonction qui calcule la profondeur moyenne des feuilles de l’arbre :
// Fonction qui parcourt l'arbre et calcule la somme des profondeurs des feuilles
void calculerProfondeursFeuilles_cpt(Node* A, int profondeur, int* somme, int* nb_feuilles, int* cpt) { //O(log n)
    (*cpt)++;  // 每次调用时增加计数器

    if (A == NULL) return; // Si le nœud est NULL, on ne fait rien

    // Si le nœud est une feuille (pas d'enfants)
    if (A->fils == NULL || A->fils->node[0] == NULL) {
        *somme += profondeur;  // Ajouter la profondeur de cette feuille à la somme
        (*nb_feuilles)++;      // Incrémenter le compteur de feuilles
        return;
    }

    // Sinon, on parcourt récursivement les enfants
    for (int i = 0; A->fils != NULL && A->fils->node[i] != NULL; i++) {
        calculerProfondeursFeuilles_cpt(A->fils->node[i], profondeur + 1, somme, nb_feuilles, cpt);
    }
}

int ProfondeurMoyennePAT_cpt(PAT* A, int* cpt) { // O(log n)
    if (A == NULL || A->node == NULL) return 0;  // Si l'arbre est vide, retourner 0

    int somme_profondeur = 0;  // Somme des profondeurs des feuilles
    int nb_feuilles = 0;      // Nombre de feuilles

    // Parcourir toutes les racines
    for (int i = 0; A->node[i] != NULL; i++) {
        calculerProfondeursFeuilles_cpt(A->node[i], 1, &somme_profondeur, &nb_feuilles, cpt);
    }

    printf("somme_profondeur: %d,nb_feuille: %d\n",somme_profondeur,nb_feuilles);

    // Si il y a des feuilles, calculer la profondeur moyenne
    if (nb_feuilles > 0) {
        return somme_profondeur / nb_feuilles;  // Retourner la profondeur moyenne
    }

    return 0;  // Si l'arbre n'a pas de feuilles, retourner 0
}

// une fonction qui prend un mot A en argument et qui indique de combien de mots du dictionnaire
// le mot A est préfixe. Ainsi pour l’exemple de base, le mot dactylo est préfixe de deux mots de l’arbre (dactylographie et dactylo). Noter que le mot A n’est pas forcément un mot de l’arbre :
// Fonction qui parcourt l'arbre pour compter le nombre de mots ayant un préfixe donné

// Compte tous les mots dans un sous-arbre à partir d'un nœud donné
void compterMotsDansSousArbre_cpt(Node* A, int* count, int* cpt) {  //  O(n)
    (*cpt)++;  // 每次递归调用时增加计数器
    if (A == NULL) return;

    if(A->valeur > 0) (*count) += 1; // Compte les mots terminant à ce nœud
    for (int i = 0; A->fils != NULL && A->fils->node[i] != NULL; i++) {
        compterMotsDansSousArbre_cpt(A->fils->node[i], count, cpt);
    }
}

void compterMotsPrefixe_cpt(Node* A, char* mot, int* count, int* cpt) { // O(Ln)
    (*cpt)++;  // 每次递归调用时增加计数器
    if (A == NULL) return; // Si le nœud est NULL ou mot invalide, on quitte

    int len_com = prefixe(A->cle, mot); // Longueur du plus long préfixe commun entre la clé et le mot
    (*cpt) ++;
    if (len_com > 0 && strncmp(A->cle, mot, len_com) == 0) { 
        // Le mot correspond partiellement ou entièrement au préfixe
        
        char* reste_mot = mot + len_com;

        (*cpt) ++;
        // Cas 1 : Si le préfixe correspond entièrement et que le mot est épuisé
        if (*reste_mot == '\0') {
            // On compte ce nœud et tous ses sous-arbres comme mots
            (*count) += A->valeur; // Ajouter les mots terminant ici
            for (int i = 0; A->fils != NULL && A->fils->node[i] != NULL; i++) {
                compterMotsDansSousArbre_cpt(A->fils->node[i], count, cpt);
            }
        } else {
            // Cas 2 : Le préfixe est partiellement épuisé, continuer dans les sous-arbres
            for (int i = 0; A->fils != NULL && A->fils->node[i] != NULL; i++) {
                compterMotsPrefixe_cpt(A->fils->node[i], reste_mot, count, cpt);
            }
        }
    }
    
}

int PrefixedansPAT_cpt(PAT* A, char* mot, int* cpt) { // O(L*n)
    if (A == NULL || mot == NULL) return 0; // Si l'arbre ou le mot est invalide
    (*cpt)++;
    int count = 0;

    // Parcourir les racines pour trouver le nœud correspondant au préfixe
    for (int i = 0; A->node[i] != NULL; i++) {
        // (*cpt)++;
        Node* racine_actuelle = A->node[i];
        char* cle = racine_actuelle->cle;
        if(cle[0] == mot[0]){
            compterMotsPrefixe_cpt(racine_actuelle,mot,&count, cpt);
        }
    }

    return count; // Retourner le nombre de mots ayant ce préfixe       
}


// // Fonction pour concaténer deux chaînes
// char* concat(const char* a, const char* b) { // O(1)
//     char* result = malloc(strlen(a) + strlen(b) + 1);
//     strcpy(result, a);
//     strcat(result, b);
//     return result;
// }

//  une fonction qui prend un mot en argument et qui le supprime de l’arbre PAT :

// Dic_enf* consDic_enf(char* cle, int val){
//     Dic_enf* de = malloc(sizeof(Dic_enf));
//     de -> cle = strdup(cle);
//     de -> val = val;
//     de -> enf =NULL;
//     return de;
// }

// void libererDic_enf(Dic_enf* de){
//     if(de != NULL){
//         free(de->cle);
//         libererPAT(de ->enf);
//         free(de);
//     }
// }
 
void PATsuppressionRec_cpt(PAT** A, char* mot, int* cpt){ // O(L*n)
    if((recherchePAT_cpt(*A,mot, cpt) == 0 && strlen(mot) !=0)){
        return;
    }
    (*cpt)++;  
    if (!*A) return;

    // Parcours des nœuds
    for(int i = 0; (*A )->node[i] != NULL; i++){ 
        Node * current = (*A)->node[i];
        // printf("strlen(m) = %ld\n", strlen(mot));
        (*cpt)++;  // Incrementing the counter for each node visited
        if (mot == NULL || strlen(mot) == 0) {
            // Si le mot est vide, on retourne l'arbre tel quel
            (*cpt)++; 
            if(strcmp(current->cle, END_OF_WORD) == 0){
                free(current->cle);
                current->valeur =0;
                // current->cle = NULL;
                break;
            }
            // return; 
        }

        (*cpt)++;  
        if(current->cle[0] == mot[0]){
            // printf("ghsdsjkh _\n");
            // printNode(current,0);

            // Cas 1 : suppression de la clé complète
            (*cpt)++;
            char* tmp = concat(mot, END_OF_WORD);
            if(strcmp(current->cle, tmp) == 0 /*&& current -> valeur > 0*/){
                // printf("dcd\n");
                free(current->cle);
                current->valeur = 0; 
                // if(current->fils == NULL) 
                // current->cle = NULL;
                // printPAT(*A);
                return ;
                }else{
                // Cas 2 : suppression dans un sous-arbre
                int len_com = prefixe(current->cle,mot);
                if(len_com >= 0){
                    char* rest_mot = mot + len_com;
                    // printf("current fils\n");
                    // printPAT(current->fils);
                    PATsuppressionRec(&(current->fils), rest_mot);
                    
                }
                // printf("current is\n");
              
                // printf("current is\n");
                // printPAT(current->fils);
                // // printPAT(*A);
                // printf("dsrrqsqrdf\n");
            }

            // printf("current cle %s_\n", current->cle);
            // printNode(current,0);
            // for(int i = 0)
            int nb_fils = 0;
            Dic_enf* s[MAX_SIZE];
            for(int i= 0; current->fils!=NULL && current->fils->node[i] !=  NULL; i++){ 
                (*cpt)++;
                // printf("current->fils->node[i]->cle %s\n", current->fils->node[i]->cle);
                // printf(" isValidKey(current->fils->node[i]->cle) == 1 ?%d\n",  isValidKey(current->fils->node[i]->cle) == 1);
                if(/*current->fils->node[i]->cle != NULL ||*/ isValidKey(current->fils->node[i]->cle) == 1){
                    Dic_enf* de = consDic_enf(current->fils->node[i]->cle,current->fils->node[i]->valeur );
                    de -> enf = current->fils->node[i]->fils;
                    s[nb_fils] = de;
                    nb_fils++;
                }
            }
            s[nb_fils] = NULL;

            // printf("nb_fils %d\n",nb_fils);
            
            (*cpt)++;
            // si un seul fils reste
            if(nb_fils == 1){
                char* newcle = concat(current->cle, s[0]->cle);
                free(current->cle);
                current->cle = strdup(newcle);
                current->valeur = s[0]-> val;
                free(current->fils);
                current->fils = s[0]->enf;
                free(s[0]->cle);
                s[0]->cle = NULL;
                s[0]->val  = 0;   
                free(newcle); 
            }
            // if(current->fils == NULL && current->valeur == 0 && isValidKey(current->cle) == 0){
            //     current = NULL;
            // }
            // Libérer les mémoires
            free(tmp);
            for(int i = 0; i < nb_fils ; i++){
                Dic_enf* tmp = s[i];
                free(tmp->cle);
                free(tmp);
            }
        }

    }
}


void PATsuppression_cpt(PAT** A, char* mot, int* cpt){ // O(L*n)
    PATsuppressionRec_cpt(A, mot, cpt);
    
    int nb_racine = 0;

    while((*A )->node[nb_racine] != NULL){
        // printf("node\n");
        // printNode((*A )->node[nb_racine] ,0);
        nb_racine++;
    }
    // printf("avant pat is\n");
    // printPAT(*A);

    // qsort((*A)->node, nb_racine, sizeof(Node*), compare_node);

    // printf("mots is %s_\n", mot);
    // printf("nb_racine %d\n", nb_racine);
    // printf("-----------\n");
    // int i;
    // for(i = 0; (*A )->node[i] != NULL/* i < nb_racine*/; i++){ 
    //     if((*A )->node[i]->cle == NULL || ((*A )->node[i]->valeur == 0 && (*A )->node[i]->fils == NULL)){
    //         // libererPAT((*A )->node[i]->fils);
    //         free((*A)->node[i]);
    //         (*A)->node[i]= NULL;
    //         break;
    //     }
    // }

    // 遍历节点并删除无效节点
    for (int i = 0; i < nb_racine; i++) {
        Node* current_node = (*A)->node[i];
        (*cpt)++;
        if (current_node == NULL) {
            continue;  // 跳过 NULL 节点
        }

        // 判断是否为无效节点（valeur 为 0 且无子节点）
        if ((current_node->valeur == 0 && current_node->fils == NULL) || (isValidKey(current_node->cle) == 0)) {
            // printf("Suppression du nœud : %s\n", current_node->cle);

            // 释放子树（如果存在），然后释放当前节点
            libererPAT(current_node->fils);
            free(current_node);
            (*A)->node[i] = NULL;
        }
    }

    // 将剩余有效节点重新整理到根节点数组前部
    int j = 0;
    for (int i = 0; i < nb_racine; i++) {
        if ((*A)->node[i] != NULL) {
            (*A)->node[j++] = (*A)->node[i];
        }
    }

    // 清理多余的节点引用
    while (j < nb_racine) {
        (*A)->node[j++] = NULL;
    }
    if((*A)->node[0] == NULL){
        (*A) ->node = NULL;
        *A = NULL;
    }
    // printf("apres pat is \n");
    // printPAT(*A);
    
}






/*****************************EX3*****************************/
// Fonction pour fusionner deux Patricia-tries en un seul.

int is_existsIN_cpt(char c, PAT* A, int* cpt){
    // int exists = 0;
    for(int j = 0; A->node[j] != NULL; j++){
        (*cpt) ++;
        Node* aNode = A->node[j];
        char* cle_A = aNode->cle;
        if(c == cle_A[0]){
            return 1;
        }
    }
    return 0;
}


PAT* PATfusion_cpt(PAT* A, PAT* B, int* cpt){ // O((n1​+n2​)⋅Lmax​)
    // Si l'un des arbres est vide, retourner l'autre
    if(EstVide(A) == 1) {
        return B;
    }
    else if(EstVide(B) == 1){
        return A;
    } 
    else{
        // Parcourir chaque nœud de l'alphabet
        for(int i = 0; B->node[i] != NULL; i++){
            Node* bNode = B->node[i];
            char* cle_b = bNode->cle;
            // printf("bNode\n");
            // printNode(bNode,0);

            // Vérifier si le nœud existe déjà dans A
            int existsInA = is_existsIN_cpt(cle_b[0], A, cpt);
            if(existsInA == 0) {
                ajouter_racine(&A, bNode);
                // printf("ajouter racine\n");
                // printPAT(A);
                
            }else{
                for(int j = 0; A->node[j] != NULL; j++){
                    Node* aNode = A->node[j];
                    char* cle_a = aNode->cle;

                    /*int existsInA = is_existsIN(cle_b[0], A);
                    if(existsInA == 0 ) {
                        printf("dd\n");
                        ajouter_racine(&A, bNode);
                        // printf("ajouter racine\n");
                        // printPAT(A);
                        
                    }

                    // Vérifier si le nœud existe déjà dans A
                    // int existsInB = is_existsIN(cle_a[0], B);
                    else */
                    (*cpt)++;
                    if (cle_a[0] == cle_b[0]){
                        // printf("clea[0] = %c, cle b[0] = %c\n",cle_a[0], cle_b[0]);
                        (*cpt)++;
                        if(strcmp(cle_a, cle_b) == 0){
                            // printf("ge\n");
                            // printf("acle, bcle: %s, %s\n", cle_a, cle_b);
                            if(cle_a[strlen(cle_a)-1] == ' ' && cle_b[strlen(cle_b)-1] == ' '){
                                // printf("fs\n");
                                aNode->valeur = aNode->valeur + bNode->valeur ;
                            }else
                               aNode->fils = PATfusion_cpt(aNode->fils, bNode->fils, cpt);
                        } else{
                            // printf("hh\n");
                            int len_com = prefixe(cle_a, cle_b);
                            char* pref_com = strndup(cle_a, len_com);
                            char* a_rest = cle_a + len_com;
                            char* b_rest = cle_b + len_com;
                            // printf("pre_cem = %s, a_res = %s, b_rest = %s\n",pref_com, a_rest,b_rest);

                            Node* F = NodeCons(a_rest);
                            PAT* Fp = PATCons(F); 

                            // printf("avant ajouter les aNode fils dans F:\n");
                            // printPAT(Fp);

                            // for(int i = 0; aNode->fils!=NULL && aNode->fils->node[i]!=NULL; i++){
                            //     ajouter_fils(F, aNode->fils->node[i]);
                            // }
                            (*cpt)++;
                            if(strcmp(F->cle, "") != 0){
                                // printf("ghfgh\n");
                                for(int i = 0; aNode->fils!=NULL && aNode->fils->node[i]!=NULL; i++){
                                    ajouter_fils(F, aNode->fils->node[i]);
                                }
                            }else{
                                // printf("fdfgdr\n");
                                Fp = PATVide();
                                for(int i = 0; aNode->fils!=NULL && aNode->fils->node[i]!=NULL; i++){
                                    // printf("aNode->fils->node[i]\n");
                                    // printNode(aNode->fils->node[i],0);
                                    ajouter_racine(&Fp, aNode->fils->node[i]);
                                }
                            }

                            // printf("apres ajouter les aNode fils dans F:\n");
                            // printPAT(Fp);

                            int val_oldb = bNode->valeur;
                            Node* G = NodeCons(b_rest);
                            G ->valeur = val_oldb; 
                            PAT* Gp = PATCons(G);
                            // printf("avant ajouter tous les fils de bNode dans G:\n");
                            // printPAT(Gp);
                            (*cpt)++;
                            if(strcmp(G->cle, "") != 0){
                                // printf("ghfgh\n");
                                for(int i = 0; bNode->fils!=NULL && bNode->fils->node[i]!=NULL; i++){
                                    ajouter_fils(G, bNode->fils->node[i]);
                                }
                            }else{
                                // printf("fdfgdr\n");
                                Gp = PATVide();
                                for(int i = 0; bNode->fils!=NULL && bNode->fils->node[i]!=NULL; i++){
                                    // printf("bNode->fils->node[i]\n");
                                    // printNode(bNode->fils->node[i],0);
                                    ajouter_racine(&Gp, bNode->fils->node[i]);
                                }
                            }
                             
                            // printf("apres ajouter tous les fils de bNode dans G:\n");
                            // printPAT(Gp);

                            aNode->cle = strdup(pref_com);
                            aNode->valeur = 0;
                            aNode->fils = PATfusion_cpt(Fp,Gp, cpt);                          
                        }
                    }/*else{}*/
                }
            }
        }
    }
    return A;
}