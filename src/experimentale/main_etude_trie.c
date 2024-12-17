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

//  gcc -Wall -o main main.c experimentale.c

//int main(int argc, char *argv[]) {
int main() {
    Words* lwords=read_Files_Shakespeare("Shakespeare");
    printf("\n");
    eciture_words(lwords);
    printf("Successful!\n");

    // Words* lw_ou = read_ouvre_Shakespeare("../../Shakespeare/1henryiv.txt");
    // print_List_Word(lw_ou);



    /*---------------- Temps de construction de la structure complète ----------------*/
    // DANS TrieH
    double temps_cons_th = 0;
    TrieH* th = NULL;
    Words* tmp = lwords;
    int cpt = 0;
    while(tmp != NULL){
        temps_cons_th += measureTime_ajout_un_seul_TH(TH_Ajout, tmp->data, th, cpt);
        tmp = tmp->suiv;
        cpt++;
    }
    // print_List_Word(lwords);
    printf("temps de construction TrieH est : %.7f\n", temps_cons_th);

    /*---------------- Temps d'ajout d'un nouveau mot dans les structures ----------------*/
    // DANS TrieH
    double temps_ajout_th = 0;
    char* m = "sfqdftxtyqsff<y";
    temps_ajout_th += measureTime_ajout_un_seul_TH(TH_Ajout, m, th, cpt);
    printf("temps d'ajout d'un nouveau mot dans TrieH: %.7f\n", temps_ajout_th);
    
    /*---------------- Comparer les profondeur et hauteur des structures ----------------*/
    int prof_TH = ProfondeurMoyenne(th);
    int haut_TH = Hauteur(th);
    printf("Hauteur de TrieH est %d, Profondeur de TrieH est %d\n", haut_TH, prof_TH);

    /*---------------- Temps de la suppression d'un ensemble de mots des structures ----------------*/
    // DANS TrieH
    double temps_supp_th = 0;
    tmp = lwords;
    while(tmp != NULL){
        temps_supp_th += measureTime_supp_TH(Suppression, th, tmp->data);
        tmp = tmp->suiv;
    }
    // printPAT(pat);
    printf("Temps de la suppression d'un ensemble de mots dans TrieH: %.7f\n", temps_supp_th);

    return 0;
}