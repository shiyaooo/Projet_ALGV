#include "tries_hybrides.h"
#include <string.h>

/* renvoie la première lettre de la chaine de caractères */
char prem(char* c) {
    return c[0];
}

/* renvoie le reste de la chaine de caractères 
    privée de la première lettre */
char* reste(char* c) {
    size_t len = strlen(c);
    char reste[len];
    for(int i=1;i<len;i++) {
        reste[i-1] = c[i];
    }
    return reste;
}


/* construit une trie hybride */
TrieH TrieH(char l, TrieH inf, TrieH eq, TrieH sup, int v) {
    TrieH th;
    th->l = l;
    th->inf = inf;
    th->eq = eq;
    th->sup = sup;
    th->v = v;
    return th;
}

/* renvoie une trie hybride vide */
TrieH TH_Vide() {
    TrieH vide;
    return vide;
}

/* renvoie 1 ssi le trie hybride A est vide, 0 sinon */
int EstVide(TrieH A) {
    if (A->l = NULL) {
        if (A->sup!=NULL || A->eq!=NULL || A->inf!=NULL) {
            printf("Problème : Trie hybride sans lettre mais avec sous-arbre !\n");
        }
        return 1;
    }
    return 0;
}

/* renvoie le caractère de la racine du trie hybride */
char lettre(TrieH A) {
    return A->l;
}

/* renvoie l'entier de la racine du trie hybride, -1 sinon */
int val(TrieH A) {
    return A->v;
}

/* renvoie une copie du sous-arbre gauche de A */
TrieH Inf(TrieH A) {
    if (EstVide(A->inf)) {
        return TH_Vide();
    }
    return TrieH((A->inf)->v, 
                 Inf(A->inf), 
                 Eq(A->inf), 
                 Sup(A->inf), 
                 (A->inf)->v);
}

/* renvoie une copie du sous-arbre central de A */
TrieH Eq(TrieH A) {
    if (EstVide(A->eq)) {
        return TH_Vide();
    }
    return TrieH((A->eq)->v, 
                 Inf(A->eq), 
                 Eq(A->eq), 
                 Sup(A->eq), 
                 (A->eq)->v);
}

/* renvoie une copie du sous-arbre droite de A */
TrieH Sup(TrieH A) {
    if (EstVide(A->sup)) {
        return TH_Vide();
    }
    return TrieH((A->sup)->v, 
                 Inf(A->sup), 
                 Eq(A->sup), 
                 Sup(A->sup), 
                 (A->sup)->v);
}


/* renvoie la lettre de la racine de A */
char Rac(TrieH A) {
    return lettre(A);
}

/* renvoie la valeur de A */
int Val(TrieH A) {
    return val(A);
}


/* renvoie le trie hybride resultant de l'insertion de c dans A */
TrieH TH_Ajout(char* c, TrieH A, int v) {
    if (EstVide(A)) {
        if (strlen(c) == 1) {
            return TrieH(prem(c), TH_Vide(), TH_Vide(), TH_Vide(), v);
        } else {
            return TrieH(prem(c), TH_Vide(), TH_Ajout(reste(c), Eq(A), v), TH_Vide(), -1);
        }
    } else {
        char p = prem(c);
        if (strcmp(p, Rac(A)) < 0) {
            return TrieH(Rac(A), TH_Ajout(c, Inf(A), v), Eq(A), Sup(A), Val(A));
        } else if (strcmp(p, Rac(A)) < 0) {
            return TrieH(Rac(A), Inf(A), Eq(A), TH_Ajout(reste(c), Sup(A), v), Val(A));
        }
        return TrieH(Rac(A), Inf(A), TH_Ajout(reste(c), Eq(A), v), Sup(A), Val(A));
    }
}