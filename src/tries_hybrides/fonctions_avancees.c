#include "fonctions_avancees.h"
#include "tries_hybrides.h"
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include <math.h>

#include <stdio.h>

/* recherche un mot dans un dictionnaire
 * renvoie 1 ssi le mot est présent dans le dictionnaire,
 *         O sinon 
 */
int Recherche(TrieH* arbre, char* mot) {
    if (EstVide(arbre)==1) {
        /*
        if (strlen(mot) == 1 && mot[0]==Rac(arbre) && Val(arbre)>=0) {
            return 1;
        } else {
            return 0;
        }
        */
        return 0;
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

/* libère la mémoire allouée pour toute une liste */ 
void freeList(List* list) {
    List* tmp;
    while (list != NULL) {
        tmp = list;
        list = list->suiv;
        free(tmp);
    }
}

/* compte les pointeurs vers Nil */
int ComptageNil(TrieH* arbre) {
    if (EstVide(arbre)==1) {
        return 1;
    }
    return ComptageNil(Inf(arbre)) + ComptageNil(Eq(arbre)) + ComptageNil(Sup(arbre));
}

int HauteurRec(TrieH* arbre) {
    if (EstVide(arbre)==1) {
        return -1;
    }
    int cpt = MAX(HauteurRec(Inf(arbre)), HauteurRec(Eq(arbre)));
    return 1 + MAX(cpt, HauteurRec(Sup(arbre)));
}

/* calcule la hauteur de l'arbre */
int Hauteur(TrieH* arbre) {
    if (EstVide(arbre)==1) {
        return 0;
    }
    //int cpt = MAX(Hauteur(Inf(arbre)), Hauteur(Eq(arbre)));
    //return 1 + MAX(cpt, Hauteur(Sup(arbre)));
    return HauteurRec(arbre);
}

List* ProfondeurMoyenneRec(TrieH* arbre, int profondeur) {
    if (EstVide(arbre)==1) {
        return NULL;
    }
    //printf("%c\n", Rac(arbre));
    List* list = NULL;
    if (EstVide(Inf(arbre)) && EstVide(Eq(arbre)) && EstVide(Sup(arbre))) {
        list = (List*)malloc(sizeof(List));
        list->entier = profondeur;
        return list;
    }
    
    int i = profondeur+1;
    //printf("inf ");
    List* linf = ProfondeurMoyenneRec(Inf(arbre), i);
    //printf("eq  ");
    List* leq = ProfondeurMoyenneRec(Eq(arbre), i);
    //printf("sup ");
    List* lsup = ProfondeurMoyenneRec(Sup(arbre), i);

    List* tmp;
    if (linf!=NULL) {
        list = linf;
        tmp = linf;
        while (tmp->suiv!=NULL) {
            tmp = tmp->suiv;
        }
    }

    if (leq!=NULL) {
        if (list==NULL) {
            list = leq;
            tmp = list;
        } else {
            tmp->suiv = leq;
        }
        while (tmp->suiv!=NULL) {
            tmp = tmp->suiv;
        }
    }

    if (lsup!=NULL) {
        if (list==NULL) {
            list = lsup;
            tmp = list;
        } else {
            tmp->suiv = lsup;
        }
    }

    return list;
}

/* calcule la profondeur moyenne des feuilles de l'arbre */
int ProfondeurMoyenne(TrieH* arbre) {
    if (EstVide(arbre)==1) {
        return 0;
    }
    List* lprofondeur = ProfondeurMoyenneRec(arbre, 0);
    int cpt = 0;
    int nb = 0;
    List* tmp = lprofondeur;
    if (tmp==NULL) {
        return 0;
    }
    while (tmp!=NULL) {
        cpt += tmp->entier;
        nb++;
        tmp = tmp->suiv;
    }
    float moyenne = cpt/nb;
    freeList(lprofondeur);
    return (int) round(moyenne);
}

/* prend un mot A en arguments
 * et qui indique combien de mots du dictionnaire
 * le mot A est préfixe
 */
int Prefixe(TrieH* arbre, char* mot) {
    if (EstVide(arbre)==1) {
        return 0;
    }
    int prefixe = 0;
    if (strcmp(mot, "")==0) {
        if (Val(arbre)!=-1) {
            prefixe = 1;
        }
    } else {
        char pm = prem(mot);
        char rac = Rac(arbre);
        if (strlen(mot) == 1) {
            if (rac == pm) {
                if (Val(arbre)!=-1) {
                    prefixe = 1;
                }
                //return 0;
            }
        }
        if (pm < rac) {
            return prefixe + Prefixe(Inf(arbre), mot);
        }
        else if (pm > rac) {
            return prefixe + Prefixe(Sup(arbre), mot);
        }
        return prefixe + Prefixe(Eq(arbre), reste(mot));
    }
    return prefixe + Prefixe(Inf(arbre), mot) + Prefixe(Sup(arbre), mot) + Prefixe(Eq(arbre), mot);
}

/* prend un mot en argument
 * et qui le supprime de l'arbre s'il y figure
 */
TrieH* Suppression(TrieH* arbre, char* mot) {
    if (EstVide(arbre)==1) {
        return arbre;
    }
    char pm = prem(mot);
    char rac = Rac(arbre);
    //printf("%s : %ld\n", mot, strlen(mot));
    if (strlen(mot) == 1) {
        //printf("%c %d\n", rac, Val(arbre));
        if (rac == pm && Val(arbre)!=-1) {
            arbre->v = -1;
            if (EstVide(Eq(arbre))==0) {    // si le mot était un préfixe
                return arbre;
            }
            //free(arbre->l);
            TrieH* nouv = NULL;
            if (EstVide(Inf(arbre))==0) {
                TrieH* inf = Inf(arbre);
                nouv = inf;
                arbre->inf = TH_Vide();
            }
            TrieH* sup = Sup(arbre);
            if (EstVide(sup)==0) {
                if (EstVide(nouv)==1) {
                    arbre->sup = TH_Vide();
                    free(arbre);
                    return sup;
                }
                //char c = Rac(sup);
                TrieH* tmp = nouv;
                while (tmp!=NULL) {
                    TrieH* tmpsup = Sup(tmp);
                    if (EstVide(tmpsup)==1) {
                        tmp->sup = sup;
                        break;
                    }
                    tmp = tmpsup;
                }
            }
            free(arbre);
            return nouv;
        }
        else if (EstVide(Inf(arbre))==1 && EstVide(Sup(arbre))==1) {
            return arbre;   // Sinon, le mot n'est pas présent
        }
    }
    
    if (pm < rac) {
        TrieH* inf = Inf(arbre);
        if (EstVide(inf)==1) {  // Si vide, alors vide
            arbre->inf = inf;
        } else {                // Sinon, suppression
            arbre->inf = Suppression(inf, mot);
        }
        //arbre->inf = Suppression(Inf(arbre), mot);
    } else if (pm > rac) {
        TrieH* sup = Sup(arbre);
        //printf("ICI");
        if (EstVide(sup)==1) {  // Si vide,   //   //
            arbre->sup = sup;
        } else {                // Sinon,       //
            arbre->sup = Suppression(sup, mot);
        }
        //arbre->sup = Suppression(Sup(arbre), mot);
    } else {
        //printf("%c ", rac);
        TrieH* eq = Eq(arbre);
        if (EstVide(eq)==1) {   // Si vide,   //   //
            arbre->eq = eq;
        } else {                // Sinon,
            eq = Suppression(eq, reste(mot));  // suppression
            if (EstVide(eq)==1) {       // Si vide (après suppression),

                if (Val(arbre)!=-1) {       // Si Rac(arbre) est la fin d'un mot
                    if (EstVide(Inf(arbre))==0) {
                        TrieH* inf = Inf(arbre);
                        arbre->eq = inf;
                        arbre->inf = TH_Vide();
                    } 
                    else if (EstVide(Sup(arbre))==0) {
                        TrieH* sup = Sup(arbre);
                        arbre->eq = sup;
                        arbre->sup = TH_Vide();
                    }
                    else {
                        arbre->eq = eq;
                    }
                    return arbre;
                }

                TrieH* nouv = NULL;
                if (EstVide(Inf(arbre))==0) {   // Si inf non vide
                    nouv = Inf(arbre);
                }
                TrieH* sup = Sup(arbre);
                if (EstVide(sup)==0) {          // Si sup non vide
                    if (nouv==NULL) {
                        free(arbre);
                        return sup;
                    }
                    //char c = Rac(sup);
                    TrieH* tmp = nouv;
                    while (tmp!=NULL) {
                        TrieH* tmpsup = Sup(tmp);
                        if (EstVide(tmpsup)==1) {
                            tmp->sup = sup;
                            break;
                        }
                        tmp = tmpsup;
                    }
                }
                free(arbre);
                return nouv;

            } else {
                arbre->eq = eq;
            }
        }
        //arbre->eq = Suppression(Eq(arbre), reste(mot));
    }
    return arbre;
}

/* met à jour la hauteur du noeud */
void majHauteur(TrieH* A) { 
    if (A != NULL) {
        int h_inf, h_eq, h_sup = -1;
        if (A->inf != NULL) {
            h_inf = A->inf->hauteur;
        }
        if (A->eq != NULL) { 
            h_eq = A->eq->hauteur;
        }
        if (A->sup != NULL) {
            h_sup = A->sup->hauteur;
        } 
        A->hauteur = 1 + MAX(h_inf, MAX(h_eq, h_sup)); 
    } 
}

/* renvoie le trie hybride après une rotation gauche */
TrieH* rotationGauche(TrieH* A) { 
    TrieH* nouv = A->eq; 
    A->eq = nouv->inf; 
    nouv->inf = A; 
    majHauteur(A); 
    majHauteur(nouv); 
    return nouv; 
} 

/* renvoie le trie hybride après une rotation droite */
TrieH* rotationDroite(TrieH* A) { 
    TrieH* nouv = A->inf; 
    A->inf = nouv->eq; 
    nouv->eq = A; 
    majHauteur(A); 
    majHauteur(nouv); 
    return nouv; 
}

TrieH* reequilibrer(TrieH* A) { 
    if (A == NULL) { 
        return A; 
    } 
    majHauteur(A); 
    /*
    int balance = (A->inf ? A->inf->hauteur : -1) - (A->sup ? A->sup->hauteur : -1); 
    // Si déséquilibre à gauche 
    if (balance > 1) { 
        if ((A->inf && A->inf->inf ? A->inf->inf->hauteur : -1) >= (A->inf && A->inf->sup ? A->inf->sup->hauteur : -1)) { 
            A = RotationDroite(A); 
        } else { 
            A->inf = RotationGauche(A->inf); 
            A = RotationDroite(A); 
        } 
    } 
    // Si déséquilibre à droite 
    else if (balance < -1) { 
        if ((A->sup && A->sup->sup ? A->sup->sup->hauteur : -1) >= (A->sup && A->sup->inf ? A->sup->inf->hauteur : -1)) { 
            A = RotationGauche(A); 
        } else { 
            A->sup = RotationDroite(A->sup); 
            A = RotationGauche(A); 
        } 
    } 
    return A; 
    */
    int h_inf, h_sup = -1;
    if (EstVide(Inf(A))==0) {
        h_inf = A->inf->hauteur;
    }
    if (EstVide(Sup(A))==0) {
        h_sup = A->sup->hauteur;
    }

    // Si déséquilibre à gauche 
    if (h_inf - h_sup > 1) {
        int h_inf_inf, h_inf_sup = -1;
        TrieH* inf = Inf(A);
        if (EstVide(inf)==0) {
            if (EstVide(inf->inf)==0) {
                h_inf_inf = inf->inf->hauteur;
            }
            if (EstVide(inf->sup)==0) {
                h_inf_sup = inf->sup->hauteur;
            }
        }

        if (h_inf_inf >= h_inf_sup) {
            A = rotationDroite(A);
        } else { 
            A->inf = rotationGauche(inf);
            A = rotationDroite(A);
        }
    }
    // Si déséquilibre à droite
    else if (h_sup - h_inf > 1) {
        int h_sup_inf, h_sup_sup = -1;
        TrieH* sup = Sup(A);
        if (EstVide(sup)==0) {
            if (EstVide(sup->inf)==0) {
                h_sup_inf = sup->inf->hauteur;
            }
            if (EstVide(sup->sup)==0) {
                h_sup_sup = sup->sup->hauteur;
            }
        }

        if (h_sup_sup >= h_sup_inf) {
            A = rotationGauche(A); 
        } else { 
            A->sup = rotationDroite(sup); 
            A = rotationGauche(A); 
        } 
    } 
    return A;
}

    /* A EFFACER*/
    /*
    if (Hauteur(Inf(A)) - Hauteur(Sup(A)) > 1) { 
        if (Hauteur(Inf(Inf(A))) >= Hauteur(Eq(Inf(A)))) { 
            A = RotationDroite(A); 
        } else { 
            A->inf = RotationGauche(A->inf); 
            A = RotationDroite(A); 
        } 
    } else if (Hauteur(Sup(A)) - Hauteur(Inf(A)) > 1) { 
        if (Hauteur(Sup(Sup(A))) >= Hauteur(Eq(Sup(A)))) { 
            A = RotationGauche(A); 
        } else { 
            A->sup = RotationDroite(A->sup); 
            A = RotationGauche(A); 
        } 
    } 
    return A;
}*/

/* retourne le trie hybride équilibré */
TrieH* TH_AjoutEquilibre(char* c, TrieH* A, int v) { 
    A = TH_Ajout(c, A, v); 
    majHauteur(A); 
    return reequilibrer(A); 
}
