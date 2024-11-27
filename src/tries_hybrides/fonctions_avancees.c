#include "fonctions_avancees.h"
#include "tries_hybrides.h"
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

/* recherche un mot dans un dictionnaire
 * renvoie 1 ssi le mot est présent dans le dictionnaire,
 *         O sinon 
 */
int Recherche(TrieH* arbre, char* mot) {
    if (EstVide(arbre)==1) {
        if (strlen(mot) == 1 && mot[0]==Rac(arbre) && Val(arbre)>=0) {
            return 1;
        } else {
            return 0;
        }
    } else {
        char pm = prem(mot);
        char rac = Rac(arbre);

        if (strlen(mot) == 1) {
            if (rac == pm) {
                if (Val(arbre)!=-1) {
                    return 1;
                }
                return 0;
            }
            //return 0;
        }
        
        if (pm < rac) {
            return Recherche(Inf(arbre), mot);
        }
        else if (pm > rac) {
            return Recherche(Sup(arbre), mot);
        }
        return Recherche(Eq(arbre), reste(mot));
    }
}

/* compte les mots présents dans le dictionnaire */
int ComptageMots(TrieH* arbre) {
    if (EstVide(arbre)==1) {
        return 0;
    } else {
        if (Val(arbre)!=-1) {
            return 1 + ComptageMots(Sup(arbre)) + ComptageMots(Eq(arbre)) + ComptageMots(Inf(arbre));
        }
        return ComptageMots(Sup(arbre)) + ComptageMots(Eq(arbre)) + ComptageMots(Inf(arbre));
    }
}

List* ListeMotsRec(TrieH* arbre, char* mot) {
    if (EstVide(arbre)==1) {
        return NULL;
    }
    //printf("%c\n", Rac(arbre));
    char lettre[2];
    lettre[0] = Rac(arbre);
    lettre[1] = '\0';

    char* nouv;
    if (strlen(mot)>0) {
        nouv = (char*)malloc(strlen(mot) + 2); // +2 pour le caractère supplémentaire et le '\0' 
        strcpy(nouv, mot);
        strcat(nouv, lettre);
    } else {
        nouv = (char*)malloc(2); // 2 pour la lettre et le '\0' 
        strcpy(nouv, lettre);
    }
    //printf("inf ");
    List* linf = ListeMotsRec(Inf(arbre), mot);
    //printf("eq  ");
    List* leq = ListeMotsRec(Eq(arbre), nouv);
    //printf("sup ");
    List* lsup = ListeMotsRec(Sup(arbre), mot);

    List* list = NULL;
    List* tmp;

    if (linf!=NULL) {   // s'il y a des mots inférieurs dans l'ordre alphabétique
        list = linf;
        tmp = linf;
        while (tmp->suiv!=NULL) {   // pour pointer sur le dernier élément de la liste
            tmp = tmp->suiv;
        }
    }
    
    if (Val(arbre)!=-1) { // s'il y a un mot
        if (list!=NULL) {   // s'il y avait des mots inférieurs
            tmp->suiv = (List*)malloc(sizeof(List));
            tmp = tmp->suiv;
        } else {            // s'il n'y avait pas de mot avant
            list = (List*)malloc(sizeof(List));
            tmp = list;
        }
        tmp->mot = (char*)malloc(strlen(nouv) + 1); // +1 pour le '\0' 
        strcpy(tmp->mot, nouv);
        //printf("mot: %s\n", tmp->mot);
        //tmp->suiv = NULL;
    }

    if (leq!=NULL) {    // s'il y a un (des) mot(s) qui se termine(nt) plus loin
        if (list==NULL) {   // s'il n'y avait pas de mot avant
            list = leq;
            tmp = list;
        } else {            // s'il y avait d'autre mots
            tmp->suiv = leq;
        }
        while (tmp->suiv!=NULL) {
            tmp = tmp->suiv;
        }
    }

    if (lsup!=NULL) {   // s'il y a des mots supérieurs
        if (tmp!=NULL) {
            tmp->suiv = lsup;// on sait qu'il y a au moins un mot avant
        }/* else {
            list = lsup;
        }*/
    }
    free(nouv);
    return list;
}

/* liste les mots du dictionnaire dans l'ordre alphabétique 
 * renvoie une liste de mots
 */
List* ListeMots(TrieH* arbre) {
    if (EstVide(arbre)==1) {
        return NULL;
    }
    return ListeMotsRec(arbre, "");
}

/* compte les pointeurs vers Nil */
int ComptageNil(TrieH* arbre);

/* calcule la hauteur de l'arbre */
int Hauteur(TrieH* arbre);

/* calcule la profondeur moyenne des feuilles de l'arbre */
int ProfondeurMoyenne(TrieH* arbre);

/* prend un mot A en arguments
 * et qui indique combien de mots du dictionnaire
 * le mot A est préfixe
 */
int Prefixe(TrieH* arbre, char* mot);

/* prend un mot en argument
 * et qui le supprime de l'arbre s'il y figure
 */
TrieH* Suppression(TrieH* arbre, char* mot);
