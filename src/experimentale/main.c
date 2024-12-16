#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "experimentale.h"
#include "../Patricia-Tries/Patricia_Tries.h"
#include "../Patricia-Tries/fonct_avc.h"
#include "../Patricia-Tries/patricia_json.h"
#include <ctype.h>  
#include <stdbool.h>
#include <unistd.h>
//  gcc -Wall -o main main.c experimentale.c

int main() {
    Words* lwords=read_Files_Shakespeare("../../Shakespeare");
    printf("\n");
    eciture_words(lwords);
    printf("Successful!\n");

    /*---------------- Temps de construction de la structure complète ----------------*/
    // DANS PAT
    double temps_cons_pat = 0;
    PAT* pat = NULL;
    Words* tmp = lwords;
    while(tmp != NULL){
        temps_cons_pat += measureTime_ajout_un_seul_PAT(PATinsertion, (&pat), tmp->data);
        tmp = tmp->suiv;
    }
    // print_List_Word(lwords);
    printf("temps de construction PAT est : %.7f\n", temps_cons_pat);

    /*---------------- Temps d'ajout d'un nouveau mot dans les structures ----------------*/
    // DANS PAT
    double temps_ajout_pat = 0;
    char* m = "sfqdftxtyqsff<y";
    temps_ajout_pat += measureTime_ajout_un_seul_PAT(PATinsertion, (&pat), m);
    printf("temps d'ajout d'un nouveau mot dans PAT: %.7f\n", temps_ajout_pat);

    
    /*---------------- Comparer les profondeur et hauteur des structures ----------------*/
    int prof_PAT = ProfondeurMoyennePAT(pat);
    int haut_PAT = HauteurPAT(pat);
    printf("Hauteur de PAT est %d, Profondeur de PAT est %d\n", haut_PAT, prof_PAT);



    /*---------------- Temps de la suppression d'un ensemble de mots des structures ----------------*/
    // DANS PAT
    double temps_supp_pat = 0;
    tmp = lwords;
    while(tmp != NULL){
        temps_supp_pat += measureTime_supp_PAT(PATsuppression, (&pat), tmp->data);
        tmp = tmp->suiv;
    }
    // printPAT(pat);
    printf("Temps de la suppression d'un ensemble de mots dans PAT: %.7f\n", temps_supp_pat);


    return 0;
}