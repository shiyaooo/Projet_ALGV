#include "tries_hybrides.h"
#include <stdlib.h>
#include <string.h>

/* renvoie la première lettre de la chaine de caractères */
char prem(char* c) {
    return c[0];
}

/* renvoie le reste de la chaine de caractères 
    privée de la première lettre */
char* reste(char* c) {
    size_t len = strlen(c);
    char* reste = (char*)malloc(len * sizeof(char));
    for(int i=1;i<len;i++) {
        reste[i-1] = c[i];
    }
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
    return A == NULL;
}

/* renvoie le caractère de la racine du trie hybride */
char Rac(TrieH* A) {
    if (A) {
        return A->l;
    }
    return '#';
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
    if (EstVide(A->inf)) {
        return TH_Vide();
    }
    return TrieHybride((A->inf)->l, 
                       Inf((TrieH*)A->inf), 
                       Eq((TrieH*)A->inf), 
                       Sup((TrieH*)A->inf), 
                       ((TrieH*)(A->inf))->v);
    return TH_Vide();
}

/* renvoie une copie du sous-arbre central de A */
TrieH* Eq(TrieH* A) {
    if (EstVide(A->eq)) {
        return TH_Vide();
    }
    return TrieHybride((A->eq)->l, 
                       Inf((TrieH*)A->eq), 
                       Eq((TrieH*)A->eq), 
                       Sup((TrieH*)A->eq), 
                       ((TrieH*)(A->eq))->v);
    return TH_Vide();
}

/* renvoie une copie du sous-arbre droite de A */
TrieH* Sup(TrieH* A) {
    if (EstVide(A->sup)) {
        return TH_Vide();
    }
    return TrieHybride((A->sup)->l, 
                       Inf(A->sup), 
                       Eq(A->sup), 
                       Sup(A->sup), 
                       (A->sup)->v);
    return TH_Vide();
}


/* renvoie le trie hybride resultant de l'insertion de c dans A */
TrieH* TH_Ajout(char* c, TrieH* A, int v) {
    if (EstVide(A)) {
        if (strlen(c) == 1) {
            return TrieHybride(prem(c), TH_Vide(), TH_Vide(), TH_Vide(), v);
        } else {
            return TrieHybride(prem(c), TH_Vide(), TH_Ajout(reste(c), Eq(A), v), TH_Vide(), -1);
        }
    } else {
        char pm = prem(c);
        char rac = Rac(A);
        /*
        char* p = &pm;
        char* r = &rac;
        int cmp = strcmp(p, r);
        */
        //if (cmp < 0) {
        if (pm < rac) {
            return TrieHybride(Rac(A), TH_Ajout(c, Inf(A), v), Eq(A), Sup(A), Val(A));
        } //else if (cmp > 0) {
        else if (pm > rac) {
            return TrieHybride(Rac(A), Inf(A), Eq(A), TH_Ajout(reste(c), Sup(A), v), Val(A));
        }
        return TrieHybride(Rac(A), Inf(A), TH_Ajout(reste(c), Eq(A), v), Sup(A), Val(A));
    }
}

//TrieH* ExempleAppel(TrieH* A) { return Sup((TrieH*)A->sup); }