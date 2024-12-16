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

    printf("\ntemps de construction de la structure complète \n");

    double temps_cons_pat = 0;
    PAT* pat = NULL;
    while(lwords != NULL){
        temps_pat += measureTime_ajout_un_seul_PAT(PATinsertion, (&pat), lwords->data);
        lwords = lwords->suiv;
    }

    printf("temps de construction PAT est : %.7f\n", temps_pat);

    printf("\ntemps de construction de la structure complète \n");

    // double temps_pat = 0;
    // PAT* pat = NULL;
    // while(lwords != NULL){
    //     temps_pat += measureTime_ajout_un_seul_PAT(PATinsertion, (&pat), lwords->data);
    //     lwords = lwords->suiv;
    // }

    // printf("temps de construction PAT est : %.7f\n", temps_pat);



    return 0;
}