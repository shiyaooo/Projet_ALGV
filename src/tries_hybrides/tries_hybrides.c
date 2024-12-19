#include "tries_hybrides.h"
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <sys/param.h>

/* renvoie la première lettre de la chaine de caractères */
char prem(char* c) {
    return c[0];
}

/* renvoie le reste de la chaine de caractères 
    privée de la première lettre */
char* reste(char* c) {
    size_t len = strlen(c);
    char* reste = (char*)malloc(len * sizeof(char));
    /*
    for(int i=1;i<len;i++) {
        reste[i-1] = c[i];
    }
    */
    /*
    if (reste == NULL) {
        perror("Erreur d'allocation mémoire");
        return c;
    }
    */
    strcpy(reste, c + 1);
    return reste;
}


/* construit une trie hybride */
TrieH* TrieHybride(char l, TrieH* inf, TrieH* eq, TrieH* sup, int v) {
    TrieH* th = (TrieH*)malloc(sizeof(TrieH));
    th->l = l;
    th->inf = inf;
    th->eq = eq;
    th->sup = sup;
    th->v = v;
    return th;
}

/* renvoie une trie hybride vide */
TrieH* TH_Vide() {
    //TrieH* vide;
    //return vide;
    return NULL;
}

/* renvoie 1 ssi le trie hybride A est vide, 0 sinon */
int EstVide(TrieH* A) {
    /*
    if (A->l == NULL) {
        if (A->sup!=NULL || A->eq!=NULL || A->inf!=NULL) {
            printf("Problème : Trie hybride sans lettre mais avec sous-arbre !\n");
        }
        return 1;
    }
    return 0;
    */
    if (A) {
        return 0;
    }
    return 1;
}

/* renvoie le caractère de la racine du trie hybride */
char Rac(TrieH* A) {
    if (A) {
        return A->l;
    }
    return ' ';
}

/* renvoie l'entier de la racine du trie hybride, -1 sinon */
int Val(TrieH* A) {
    if (A) {
        return A->v;
    }
    return -1;
}

/* renvoie une copie du sous-arbre gauche de A */
TrieH* Inf(TrieH* A) { 
    if (A == NULL || EstVide(A->inf)) { 
        return TH_Vide(); 
    } 
    return A->inf; 
}
/*
TrieH* Inf(TrieH* A) {
    if (A==NULL) {
        return TH_Vide();
    }
    if (EstVide(A->inf)==1) {
        return A->inf;
    }
    return TrieHybride((A->inf)->l, 
                       Inf(A->inf), 
                       Eq(A->inf), 
                       Sup(A->inf), 
                       (A->inf)->v);
}
*/
/* renvoie une copie du sous-arbre central de A */
TrieH* Eq(TrieH* A) { 
    if (A == NULL || EstVide(A->eq)) { 
        return TH_Vide(); 
    } 
    return A->eq; 
}
/*
TrieH* Eq(TrieH* A) {
    if (A==NULL) {
        return TH_Vide();
    }
    if (EstVide(A->eq)==1) {
        return A->eq;
    }
    return TrieHybride((A->eq)->l, 
                       Inf(A->eq), 
                       Eq(A->eq), 
                       Sup(A->eq), 
                       (A->eq)->v);
    }
*/
/* renvoie une copie du sous-arbre droite de A */
TrieH* Sup(TrieH* A) { 
    if (A == NULL || EstVide(A->sup)) { 
        return TH_Vide(); 
    } 
    return A->sup; 
}
/*
TrieH* Sup(TrieH* A) {
    if (A==NULL) {
        return TH_Vide();
    }
    if (EstVide(A->sup)==1) {
        return A->sup;
    }
    return TrieHybride((A->sup)->l, 
                       Inf(A->sup), 
                       Eq(A->sup), 
                       Sup(A->sup), 
                       (A->sup)->v);

}
*/


/* met à jour la hauteur du noeud (Partie 6 - pour éviter d'utiliser Hauteur) */
void majHauteur(TrieH* A) { 
    if (A != NULL) {
        int h_inf = -1, h_eq = -1, h_sup = -1;
        if (EstVide(Inf(A))==0) {
            h_inf = A->inf->hauteur;
        }
        if (EstVide(Eq(A))==0) { 
            h_eq = A->eq->hauteur;
        }
        if (EstVide(Sup(A))==0) {
            h_sup = A->sup->hauteur;
        } 
        A->hauteur = 1 + MAX(h_inf, MAX(h_eq, h_sup)); 
    } 
}

/* renvoie le trie hybride resultant de l'insertion de c dans A */
TrieH* TH_Ajout(char* c, TrieH* A, int v) {
    if (EstVide(A)==1) {
        if (strlen(c) == 1) {
            return TrieHybride(prem(c), TH_Vide(), TH_Vide(), TH_Vide(), v);
        } else {
            //return TrieHybride(prem(c), TH_Vide(), TH_Ajout(reste(c), Eq(A), v), TH_Vide(), -1);
            char* r = reste(c); 
            TrieH* newTrie = TrieHybride(prem(c), TH_Vide(), TH_Ajout(r, TH_Vide(), v), TH_Vide(), -1); 
            free_chaine(r); // Libération de la mémoire allouée pour r
            majHauteur(newTrie);    // Mise à jour de la hauteur
            return newTrie;
        }
    } else {
        char pm = prem(c);
        char rac = Rac(A);

        // ajouté par rapport à l'algo donnée slide 45 du chap 2
        if (strlen(c) == 1) {
            if (rac == pm) {
                int val = Val(A);
                if (val >= 0) { // si le mot est un doublon
                    return A;
                }
                else {          // sinon, c'est la racine d'un mot déjà inséré
                    //return TrieHybride(rac, Sup(A), Eq(A), Inf(A), v);
                    A->v = v;
                    majHauteur(A);    // Mise à jour de la hauteur
                    return A;
                }
            }
        }
        
        if (pm < rac) {
            //return TrieHybride(rac, TH_Ajout(c, Inf(A), v), Eq(A), Sup(A), Val(A));
            A->inf = TH_Ajout(c, Inf(A), v);
        }
        else if (pm > rac) {
            //return TrieHybride(rac, Inf(A), Eq(A), TH_Ajout(c, Sup(A), v), Val(A));
            A->sup = TH_Ajout(c, Sup(A), v);
        }
        //return TrieHybride(rac, Inf(A), TH_Ajout(reste(c), Eq(A), v), Sup(A), Val(A));
        else {
            char* r = reste(c); 
            //TrieH* newTrie = TrieHybride(rac, A->inf, TH_Ajout(r, A->eq, v), A->sup, A->v); 
            A->eq = TH_Ajout(r, Eq(A), v);
            free_chaine(r); // Libération de la mémoire allouée pour r
            //return newTrie
        }
        majHauteur(A);  // Mise à jour de la hauteur
        return A;
    }
}

/* libère la mémoire allouée pour un noeud de trie hybride */
void free_TH(TrieH* A) {
    if (A != NULL) { 
        free_TH(A->inf); 
        free_TH(A->eq); 
        free_TH(A->sup); 
        free(A); 
    } 
} 

/* libère la mémoire allouée pour une chaîne de caractères */ 
void free_chaine(char* chaine) { 
    if (chaine != NULL) { 
        free(chaine); 
    }
}
