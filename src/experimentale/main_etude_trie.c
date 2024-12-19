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
    start = clock();
    th = TH_AjoutEquilibre(m, th, cpt);
    end = clock();
    //temps_ajout_th += measureTime_ajout_un_seul_TH(TH_Ajout, m, th, cpt);
    printf("temps d'ajout d'un nouveau mot dans TrieH equilibré: %.7f\n", temps_ajout_th);

    /*---------------- Comparer les profondeur et hauteur des structures equilibre----------------*/
    int prof_TH = 0;
    prof_TH = ProfondeurMoyenne(th);
    int haut_TH = th->hauteur;//Hauteur(th);
    printf("Hauteur de TrieH équilibré est %d, Profondeur de TrieH équilibré est %d\n", haut_TH, prof_TH);
    
    /*---------------- Compteur des fonctions sur un trie équilibré ------------------------------*/
    printf("\nIl y a %d noeuds dans TrieH équilibré\n", compteNoeuds(th));

    setCptFct(0);
    printf("Rechercher un mot dans TrieH :\n");
    m = "dactylo";
    int cpt_recherche = Recherche(th, m);
    printf("le mot '%s' est dans l'arbre ? = %d et son cpt = %d\n", m, cpt_recherche, getCptFct());

    setCptFct(0);
    printf("\nLes mots présents dans le dictionnaire :\n");
    int cpt_comptagemots = ComptageMots(th);
    printf("il y a %d mots présents dans le dictionnaire (avec les ponctuations) et son compteur est %d.\n", cpt_comptagemots, getCptFct());



    setCptFct(0);
    printf("\nCompte les pointeurs vers Nil :\n");
    int cpt_nil = ComptageNil(th);
    printf("Nombre total de pointeurs NULL : %d et son cpt = %d\n", cpt_nil, getCptFct());

    setCptFct(0);
    printf("\nCalcule la hauteur de l'arbre TrieH équilibré :\n");
    int hauteur = Hauteur(th);
    printf("Hauteur du Trie Hybride équilibré : %d et son cpt: %d\n", hauteur, getCptFct());

    setCptFct(0);
    printf("\nCalcule la profondeur moyenne des feuilles du trie hybride équilibré :\n");
    int prof_moy = ProfondeurMoyenne(th);
    printf("Profondeur moyenne des feuilles du Trie Hybride : %d et son cpt : %d\n", prof_moy, getCptFct());

    setCptFct(0);
    printf("\nCompter les mots du dictionnaire préfixe d'un mot\n");
    m = "dactylographie";
    int cpt_prefixe = Prefixe(th, m);
    printf("Il y a %d de mots du dictionnaire préfixe du mot '%s' et son cpt est : %d.\n", cpt_prefixe, m, getCptFct());

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
    prof_TH = ProfondeurMoyenne(th);
    haut_TH = th->hauteur;//Hauteur(th);
    printf("Hauteur de TrieH non équilibré est %d, Profondeur non équilibré de TrieH est %d\n", haut_TH, prof_TH);

    /*---------------- Compteur des fonctions sur un trie non équilibré ------------------------------*/
    printf("\nIl y a %d noeuds dans TrieH non équilibré\n", compteNoeuds(th));

    setCptFct(0);
    printf("Rechercher un mot dans TrieH non équilibré :\n");
    m = "dactylo";
    cpt_recherche = Recherche(th, m);
    printf("le mot '%s' est dans l'arbre ? = %d et son cpt = %d\n", m, cpt_recherche, getCptFct());

    setCptFct(0);
    printf("\nLes mots présents dans le dictionnaire :\n");
    cpt_comptagemots = ComptageMots(th);
    printf("il y a %d mots présents dans le dictionnaire (avec les ponctuations) et son compteur est %d.\n", cpt_comptagemots, getCptFct());



    setCptFct(0);
    printf("\nCompte les pointeurs vers Nil :\n");
    cpt_nil = ComptageNil(th);
    printf("Nombre total de pointeurs NULL : %d et son cpt = %d\n", cpt_nil, getCptFct());

    setCptFct(0);
    printf("\nCalcule la hauteur de l'arbre TrieH non équilibré :\n");
    hauteur = Hauteur(th);
    printf("Hauteur du Trie Hybride non équilibré : %d et son cpt: %d\n", hauteur, getCptFct());

    setCptFct(0);
    printf("\nCalcule la profondeur moyenne des feuilles du trie hybride non équilibré :\n");
    prof_moy = ProfondeurMoyenne(th);
    printf("Profondeur moyenne des feuilles du Trie Hybride non équilibré: %d et son cpt : %d\n", prof_moy, getCptFct());

    setCptFct(0);
    printf("\nCompter les mots du dictionnaire préfixe d'un mot\n");
    m = "dactylographie";
    cpt_prefixe = Prefixe(th, m);
    printf("Il y a %d de mots du dictionnaire préfixe du mot '%s' et son cpt est : %d.\n", cpt_prefixe, m, getCptFct());

    /*---------------- Temps de la suppression d'un ensemble de mots des structures non equilibre ----------------*/
    // DANS TrieH
    temps_supp_th = 0;
    tmp = lwords;
    while(tmp != NULL){
        temps_supp_th += measureTime_supp_TH(Suppression, th, tmp->data);
        tmp = tmp->suiv;
    }
    printf("Temps de la suppression d'un ensemble de mots dans TrieH non équilibre: %.7f\n", temps_supp_th);
    
    return 0;
}