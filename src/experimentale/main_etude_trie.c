#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "experimentale_trie.h"
#include "../tries_hybrides/tries_hybrides.h"
#include "../tries_hybrides/fonctions_avancees.h"
#include "../tries_hybrides/ecriture_lecture.h"
#include <ctype.h>  
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

int main() {
    Words* lwords=read_Files_Shakespeare("Shakespeare");
    printf("\n");
    eciture_words(lwords);
    printf("Successful!\n");

    // Words* lw_ou = read_ouvre_Shakespeare("../../Shakespeare/1henryiv.txt");
    // print_List_Word(lw_ou);



    /*---------------- Temps de construction de la structure complète equilibre ----------------*/
    // DANS TrieH
    double temps_cons_th = 0;
    TrieH* th = NULL;
    Words* tmp = lwords;
    int cpt = 0;
    clock_t start, end;
    start = clock();
    while(tmp != NULL){
        //th = TH_Ajout(tmp->data, th, cpt);
        th = TH_AjoutEquilibre(tmp->data, th, cpt);
        //temps_cons_th += measureTime_ajout_un_seul_TH(TH_Ajout, tmp->data, th, cpt);
        tmp = tmp->suiv;
        cpt++;
    }
    end = clock();
    temps_cons_th = ((double) (end - start)) / CLOCKS_PER_SEC;
    // print_List_Word(lwords);
    printf("temps de construction TrieH équilibré est : %.7f\n", temps_cons_th);

    /*---------------- Temps d'ajout d'un nouveau mot dans les structures equilibre ----------------*/
    // DANS TrieH
    
    double temps_ajout_th = 0;
    char* m = "sfqdftxtyqsff<y";
    th = TH_AjoutEquilibre(m, th, cpt);
    //temps_ajout_th += measureTime_ajout_un_seul_TH(TH_Ajout, m, th, cpt);
    printf("temps d'ajout d'un nouveau mot dans TrieH equilibré: %.7f\n", temps_ajout_th);

    /*---------------- Comparer les profondeur et hauteur des structures ----------------*/
    int prof_TH = 0;
    //prof_TH = ProfondeurMoyenne(th);
    int haut_TH = th->hauteur;//Hauteur(th);
    printf("Hauteur de TrieH équilibré est %d, Profondeur de TrieH équilibré est %d\n", haut_TH, prof_TH);
    
    /*---------------- Temps de la suppression d'un ensemble de mots des structures equilibre ----------------*/
    // DANS TrieH
    double temps_supp_th = 0;
    tmp = lwords;
    while(tmp != NULL){
        temps_supp_th += measureTime_supp_TH(Suppression, th, tmp->data);
        tmp = tmp->suiv;
    }
    // printPAT(pat);
    printf("Temps de la suppression d'un ensemble de mots dans TrieH équilibre: %.7f\n", temps_supp_th);

    /*---------------- Temps de construction de la structure complète non equilibre ----------------*/
    lwords=read_Files_Shakespeare("Shakespeare");
    printf("\n");
    eciture_words(lwords);
    printf("Successful!\n");
    
    tmp = lwords;
    start = clock();
    while(tmp != NULL){
        //th = TH_Ajout(tmp->data, th, cpt);
        th = TH_AjoutEquilibre(tmp->data, th, cpt);
        //temps_cons_th += measureTime_ajout_un_seul_TH(TH_Ajout, tmp->data, th, cpt);
        tmp = tmp->suiv;
        cpt++;
    }
    end = clock();
    temps_cons_th = ((double) (end - start)) / CLOCKS_PER_SEC;
    // print_List_Word(lwords);
    printf("temps de construction TrieH non équilibré est : %.7f\n", temps_cons_th);

    /*---------------- Temps d'ajout d'un nouveau mot dans les structures non equilibre ----------------*/
    // DANS TrieH
    
    temps_ajout_th = 0;
    m = "sfqdftxtyqsff<y";
    start = clock();
    th = TH_AjoutEquilibre(m, th, cpt);
    end = clock();
    //temps_ajout_th += measureTime_ajout_un_seul_TH(TH_Ajout, m, th, cpt);
    temps_ajout_th = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("temps d'ajout d'un nouveau mot dans TrieH non équilibré: %.7f\n", temps_ajout_th);
    
    /*---------------- Comparer les profondeur et hauteur des structures non equilibre ----------------*/
    prof_TH = 0;//ProfondeurMoyenne(th);
    haut_TH = th->hauteur;//Hauteur(th);
    printf("Hauteur de TrieH non équilibré est %d, Profondeur non équilibré de TrieH est %d\n", haut_TH, prof_TH);

    /*---------------- Temps de la suppression d'un ensemble de mots des structures non equilibre ----------------*/
    // DANS TrieH
    temps_supp_th = 0;
    tmp = lwords;
    while(tmp != NULL){
        temps_supp_th += measureTime_supp_TH(Suppression, th, tmp->data);
        tmp = tmp->suiv;
    }
    // printPAT(pat);
    printf("Temps de la suppression d'un ensemble de mots dans TrieH non équilibre: %.7f\n", temps_supp_th);

    return 0;
}