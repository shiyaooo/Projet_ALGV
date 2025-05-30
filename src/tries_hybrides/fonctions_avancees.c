#include "fonctions_avancees.h"
#include "tries_hybrides.h"
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include <math.h>

#include <stdio.h>

int cpt_fct = 0;

/* recherche un mot dans un dictionnaire
 * renvoie 1 ssi le mot est présent dans le dictionnaire,
 *         O sinon 
 */
int Recherche(TrieH* arbre, char* mot) {
    cpt_fct++;
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

        cpt_fct++;
        if (strlen(mot) == 1) {
            cpt_fct++;
            if (rac == pm) {
                cpt_fct++;
                if (Val(arbre)!=-1) {
                    return 1;
                }
                return 0;
            }
            //return 0;
        }
        
        cpt_fct++;
        if (pm < rac) {
            return Recherche(Inf(arbre), mot);
        }
        else if (pm > rac) {
            cpt_fct++;
            return Recherche(Sup(arbre), mot);
        }
        return Recherche(Eq(arbre), reste(mot));
    }
}

/* compte les mots présents dans le dictionnaire */
int ComptageMots(TrieH* arbre) {
    cpt_fct++;
    if (EstVide(arbre)==1) {
        return 0;
    } else {
        cpt_fct++;
        if (Val(arbre)!=-1) {
            return 1 + ComptageMots(Sup(arbre)) + ComptageMots(Eq(arbre)) + ComptageMots(Inf(arbre));
        }
        return ComptageMots(Sup(arbre)) + ComptageMots(Eq(arbre)) + ComptageMots(Inf(arbre));
    }
}

List* ListeMotsRec(TrieH* arbre, char* mot) {
    cpt_fct++;
    if (EstVide(arbre)==1) {
        return NULL;
    }
    //printf("%c\n", Rac(arbre));
    char lettre[2];
    lettre[0] = Rac(arbre);
    lettre[1] = '\0';

    char* nouv;
    cpt_fct++;
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

    cpt_fct++;
    if (linf!=NULL) {   // s'il y a des mots inférieurs dans l'ordre alphabétique
        list = linf;
        tmp = linf;
        while (tmp->suiv!=NULL) {   // pour pointer sur le dernier élément de la liste
            cpt_fct++;
            tmp = tmp->suiv;
        }
    }
    
    cpt_fct++;
    if (Val(arbre)!=-1) { // s'il y a un mot
        cpt_fct++;
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

    cpt_fct++;
    if (leq!=NULL) {    // s'il y a un (des) mot(s) qui se termine(nt) plus loin
        cpt_fct++;
        if (list==NULL) {   // s'il n'y avait pas de mot avant
            list = leq;
            tmp = list;
        } else {            // s'il y avait d'autre mots
            tmp->suiv = leq;
        }
        while (tmp->suiv!=NULL) {
            cpt_fct++;
            tmp = tmp->suiv;
        }
    }

    cpt_fct++;
    if (lsup!=NULL) {   // s'il y a des mots supérieurs
        cpt_fct++;
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
    cpt_fct++;
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
    cpt_fct++;
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
    cpt_fct++;
    if (EstVide(arbre)==1) {
        return 0;
    }
    //int cpt = MAX(Hauteur(Inf(arbre)), Hauteur(Eq(arbre)));
    //return 1 + MAX(cpt, Hauteur(Sup(arbre)));
    //return HauteurRec(arbre);
    return arbre->hauteur;   // Partie 6, hauteur inclu dans structure TrieH
}

List* ProfondeurMoyenneRec(TrieH* arbre, int profondeur) {
    cpt_fct++;
    if (EstVide(arbre)==1) {
        return NULL;
    }
    //printf("%c\n", Rac(arbre));
    List* list = NULL;
    cpt_fct+=3;
    if (EstVide(Inf(arbre)) && EstVide(Eq(arbre)) && EstVide(Sup(arbre))) {
        list = (List*)malloc(sizeof(List));
        list->entier = profondeur;
        list->suiv = NULL;
        //printf("profondeur feuille: %d\n", profondeur);
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
    cpt_fct++;
    if (linf!=NULL) {
        list = linf;
        tmp = linf;
        while (tmp->suiv!=NULL) {
            cpt_fct++;
            tmp = tmp->suiv;
        }
    }

    cpt_fct++;
    if (leq!=NULL) {
        cpt_fct++;
        if (list==NULL) {
            list = leq;
            tmp = list;
        } else {
            tmp->suiv = leq;
        }
        while (tmp->suiv!=NULL) {
            cpt_fct++;
            tmp = tmp->suiv;
        }
    }

    cpt_fct++;
    if (lsup!=NULL) {
        cpt_fct++;
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
    cpt_fct++;
    if (EstVide(arbre)==1) {
        return 0;
    }
    List* lprofondeur = ProfondeurMoyenneRec(arbre, 0);
    int cpt = 0;
    int nb = 0;

    List* tmp = lprofondeur;
    cpt_fct++;
    if (tmp==NULL) {
        return 0;
    }
    while (tmp!=NULL) {
        cpt_fct++;
        //printf("profondeur: %d\n", tmp->entier);
        cpt += tmp->entier;
        nb++;
        tmp = tmp->suiv;
    }
    cpt_fct++;
    if (nb == 0) {
        freeList(lprofondeur);
        return 0;
    }
    float moyenne = cpt/nb;
    freeList(lprofondeur);
    //printf("profondeur moyenne: %f\n", moyenne);
    return (int) round(moyenne);
}

/* prend un mot A en arguments
 * et qui indique combien de mots du dictionnaire
 * le mot A est préfixe
 */
int Prefixe(TrieH* arbre, char* mot) {
    cpt_fct++;
    if (EstVide(arbre)==1) {
        return 0;
    }
    int prefixe = 0;
    cpt_fct++;
    if (strcmp(mot, "")==0) {
        cpt_fct++;
        if (Val(arbre)!=-1) {
            prefixe = 1;
        }
    } else {
        char pm = prem(mot);
        char rac = Rac(arbre);
        cpt_fct++;
        if (strlen(mot) == 1) {
            cpt_fct++;
            if (rac == pm) {
                cpt_fct++;
                if (Val(arbre)!=-1) {
                    prefixe = 1;
                }
                //return 0;
            }
        }
        cpt_fct++;
        if (pm < rac) {
            return prefixe + Prefixe(Inf(arbre), mot);
        }
        else if (pm > rac) {
            cpt_fct++;
            return prefixe + Prefixe(Sup(arbre), mot);
        }
        cpt_fct++;
        return prefixe + Prefixe(Eq(arbre), reste(mot));
    }
    return prefixe + Prefixe(Inf(arbre), mot) + Prefixe(Sup(arbre), mot) + Prefixe(Eq(arbre), mot);
}

/* prend un mot en argument
 * et qui le supprime de l'arbre s'il y figure
 */
TrieH* Suppression(TrieH* arbre, char* mot) {
    cpt_fct++;
    if (EstVide(arbre)==1) {
        return arbre;
    }
    char pm = prem(mot);
    char rac = Rac(arbre);
    //printf("%s : %ld\n", mot, strlen(mot));
    cpt_fct++;
    if (strlen(mot) == 1) {
        //printf("%c %d\n", rac, Val(arbre));
        cpt_fct+=2;
        if (rac == pm && Val(arbre)!=-1) {
            arbre->v = -1;
            cpt_fct++;
            if (EstVide(Eq(arbre))==0) {    // si le mot était un préfixe
                return arbre;
            }
            //free(arbre->l);
            TrieH* nouv = NULL;
            cpt_fct++;
            if (EstVide(Inf(arbre))==0) {
                TrieH* inf = Inf(arbre);
                nouv = inf;
                arbre->inf = TH_Vide();
            }
            TrieH* sup = Sup(arbre);
            cpt_fct++;
            if (EstVide(sup)==0) {
                cpt_fct++;
                if (EstVide(nouv)==1) {
                    arbre->sup = TH_Vide();
                    free(arbre);
                    return sup;
                }
                //char c = Rac(sup);
                TrieH* tmp = nouv;
                while (tmp!=NULL) {
                    cpt_fct++;
                    TrieH* tmpsup = Sup(tmp);
                    cpt_fct++;
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
            cpt_fct+=2;
            return arbre;   // Sinon, le mot n'est pas présent
        }
        cpt_fct+=2;
    }
    
    cpt_fct++;
    if (pm < rac) {
        TrieH* inf = Inf(arbre);
        cpt_fct++;
        if (EstVide(inf)==1) {  // Si vide, alors vide
            arbre->inf = inf;
        } else {                // Sinon, suppression
            arbre->inf = Suppression(inf, mot);
        }
        //arbre->inf = Suppression(Inf(arbre), mot);
    } else if (pm > rac) {
        cpt_fct++;
        TrieH* sup = Sup(arbre);
        //printf("ICI");
        cpt_fct++;
        if (EstVide(sup)==1) {  // Si vide,   //   //
            arbre->sup = sup;
        } else {                // Sinon,       //
            arbre->sup = Suppression(sup, mot);
        }
        //arbre->sup = Suppression(Sup(arbre), mot);
    } else {
        cpt_fct++;
        //printf("%c ", rac);
        TrieH* eq = Eq(arbre);
        cpt_fct++;
        if (EstVide(eq)==1) {   // Si vide,   //   //
            arbre->eq = eq;
        } else {                // Sinon,
            eq = Suppression(eq, reste(mot));  // suppression
            cpt_fct++;
            if (EstVide(eq)==1) {       // Si vide (après suppression),

                cpt_fct++;
                if (Val(arbre)!=-1) {       // Si Rac(arbre) est la fin d'un mot
                    cpt_fct++;
                    if (EstVide(Inf(arbre))==0) {
                        TrieH* inf = Inf(arbre);
                        arbre->eq = inf;
                        arbre->inf = TH_Vide();
                    } 
                    else if (EstVide(Sup(arbre))==0) {
                        cpt_fct++;
                        TrieH* sup = Sup(arbre);
                        arbre->eq = sup;
                        arbre->sup = TH_Vide();
                    }
                    else {
                        cpt_fct++;
                        arbre->eq = eq;
                    }
                    return arbre;
                }

                TrieH* nouv = NULL;
                cpt_fct++;
                if (EstVide(Inf(arbre))==0) {   // Si inf non vide
                    nouv = Inf(arbre);
                }
                TrieH* sup = Sup(arbre);
                cpt_fct++;
                if (EstVide(sup)==0) {          // Si sup non vide
                    cpt_fct++;
                    if (nouv==NULL) {
                        free(arbre);
                        return sup;
                    }
                    //char c = Rac(sup);
                    TrieH* tmp = nouv;
                    while (tmp!=NULL) {
                        cpt_fct++;
                        TrieH* tmpsup = Sup(tmp);
                        cpt_fct++;
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

/* renvoie le trie hybride après une rotation gauche */
TrieH* rotationGauche(TrieH* A) { 
    TrieH* nouv = A->sup; 
    A->sup = nouv->inf; 
    nouv->inf = A; 
    majHauteur(A); 
    majHauteur(nouv); 
    return nouv; 
} 

/* renvoie le trie hybride après une rotation droite */
TrieH* rotationDroite(TrieH* A) { 
    TrieH* nouv = A->inf; 
    A->inf = nouv->sup; 
    nouv->sup = A; 
    majHauteur(A); 
    majHauteur(nouv); 
    return nouv; 
}

TrieH* reequilibrer(TrieH* A) { 
    if (A == NULL) { 
        return A; 
    } 
    majHauteur(A); 
    
    int h_inf = -1, h_sup = -1;

    if (EstVide(Inf(A))==0) {
        h_inf = A->inf->hauteur;
    }
    if (EstVide(Sup(A))==0) {
        h_sup = A->sup->hauteur;
    }

    // Si déséquilibre à gauche 
    if (h_inf - h_sup > 1) {
        int h_inf_inf = -1, h_inf_sup = -1;
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
        int h_sup_inf = -1, h_sup_sup = -1;
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

/* retourne le trie hybride équilibré */
TrieH* TH_AjoutEquilibre(char* c, TrieH* A, int v) { 
    A = TH_Ajout(c, A, v); 
    majHauteur(A); 
    return reequilibrer(A); 
}

/* retourne la valeur du compteur */
int getCptFct() {
    return cpt_fct;
}

/* modifie la valeur du compteur */
void setCptFct(int v) {
    cpt_fct = v;
}

/* renvoie le nombre de noeuds dans un trie hybride */
int compteNoeuds(TrieH* arbre) {
    if (EstVide(arbre)==1) {
        return 0;
    }
    return 1 + compteNoeuds(Inf(arbre)) + compteNoeuds(Eq(arbre)) + compteNoeuds(Sup(arbre));
}