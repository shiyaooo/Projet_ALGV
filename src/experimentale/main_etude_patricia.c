#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "experimentale.h"
#include "../Patricia-Tries/Patricia_Tries.h"
#include "../Patricia-Tries/fonct_avc.h"
#include "../Patricia-Tries/fonct_avc.h"
#include "../Patricia-Tries/patricia_json.h"
#include <ctype.h>  
#include <stdbool.h>
#include <unistd.h>
#include <time.h>


//  gcc -Wall -o main main.c experimentale.c

int main() {

    Words* lwords=read_Files_Shakespeare("Shakespeare");
    printf("\n");
    eciture_words(lwords);
    printf("Successful!\n");

    // Words* lw_ou = read_ouvre_Shakespeare("../../Shakespeare/1henryiv.txt");
    // print_List_Word(lw_ou);



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

    /*---------------- Compteur des fonctions ----------------*/
    int cmpt = nombre_node(pat);
    printf("Il y a %d noeuds dans PAT. \n", cmpt);

    int cpt  = 0;
    printf("Recher un mot dans PAT:\n");
    m = "dactylo";

    bool isExit_cpt = recherchePAT_cpt(pat, m, &cpt);
    printf("le mot '%s' est dans l'arbre ? = %d et son cpt = %d\n", m, isExit_cpt, cpt);

    cpt = 0;
    printf("\nLes mots présents dans le dictionnaire: \n");
    int nb_mot = ComptageMotsdansPAT_cpt(pat, &cpt);
    printf("il y a %d mots présents dans le dictionnaire (avec les ponctuations) et son compteur est %d.\n",nb_mot, cpt);

    cpt = 0;
    printf("\nliste les mots du dictionnaire dans l’ordre alphabétique:\n");
    char** list_mot = ListeMotsdansPAT_cpt(pat, &cpt);
    printf("Mots dans le Patricia Trie :\n");
    // for (int i = 0; list_mot[i] != NULL; i++) {
    //     printf("%s\t", list_mot[i]);
    // }
    printf("\nson cpt est %d\n", cpt);

    cpt = 0;
    printf("\nCompte les pointeurs vers Nil: \n");
    int totalNil = ComptageNildansPAT_cpt(pat, &cpt);
    printf("Nombre total de pointeurs NULL : %d et son cpt = %d\n", totalNil, cpt);

    cpt = 0;
    printf("\nCalcule la hauteur de l’arbre PAT:\n");
    int hauteur = HauteurPAT_cpt(pat, &cpt);
    printf("Hauteur du Patricia Trie : %d et son cpt: %d\n", hauteur,cpt);

    cpt = 0;
    printf("\nCalcule la profondeur moyenne des feuilles de l’arbre PAT:\n");
    int pronfondeur = ProfondeurMoyennePAT_cpt(pat,&cpt);
    printf("Profondeur moyenne des feuilles du Patricia Trie : %d et son cpt : %d\n", pronfondeur, cpt);

    cpt = 0;
    printf("\nCompter de mots du dictionnaire le mot A est préfixe.\n");
    m = "dactylographie";
    int nb_prefixe = PrefixedansPAT_cpt(pat, m, &cpt);
    printf("Il y a %d de mots du dictionnaire le mot '%s' est préfixe et son cpt est %d.\n", nb_prefixe, m, cpt);

    cpt = 0;
    printf("\nSupprimer un mot dans l'arbre PAT.\n");
    m = "dactylographie";

    PATsuppression_cpt(&pat, m, &cpt);
    printf("PAT apres supprime le mot '%s'  et son cpt est %d:\n", m, cpt);

    /*---------------- Temps de la suppression d'un ensemble de mots des structures ----------------*/
    // DANS PAT
    // double temps_supp_pat = 0;
    // tmp = lwords;
    // while(tmp != NULL){
    //     temps_supp_pat += measureTime_supp_PAT(PATsuppression, (&pat), tmp->data);
    //     tmp = tmp->suiv;
    // }
    // // printPAT(pat);
    // printf("Temps de la suppression d'un ensemble de mots dans PAT: %.7f\n", temps_supp_pat);

    // /*---------------- Temps de fusions d'arbres encodant chacun une oeuvre  ----------------*/
    // struct dirent *dir;

    // DIR *d=opendir("Shakespeare");
    // if(!d){
    //     fprintf(stderr,"erreur d'ouverture du dossier Shakespeare\n");
    //     return -1;
    // }
    // // Lire tous les fichiers dans le répertoire
    // Words* words=NULL;
    // int i = 0;
    // PAT* pats[MAX_SIZE];
    // while((dir=readdir(d))!=NULL){
    //     // Assurez-vous de ne pas traiter les entrées spéciales "." et ".."
    //     if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
    //         //printf("file=%s\n",dir->d_name);
    //         char file_path[MAX_SIZE];
    //         sprintf(file_path,"%s/%s","Shakespeare",dir->d_name);
    //         file_path[strlen(file_path)]='\0';
    //         words = read_ouvre_Shakespeare(file_path);
    //         PAT* pat = NULL;
    //         while(words != NULL){
    //             PATinsertion(&pat, words->data);
    //             words = words ->suiv;
    //         } 
    //         pats[i] = pat;
    //         words = NULL;
    //         i++;
            
    //     }
        
    // }
    // closedir(d);  

    // // DANS PAT
    // double temps_fusion_pat = 0;
    // pat = NULL;
    // for(int j =0; j < i; j++){
    //     clock_t start, end;
    //     start = clock();
    //     pat = PATfusion(pat,pats[j]);
    //     end = clock();
    //     // printf("temps %f\n",measureTime_fusion_PAT(PATfusion,pat,pats[j]));
    //     // printPAT(pat);
    //     temps_fusion_pat += ((double) (end - start)) / CLOCKS_PER_SEC;

    // }
    // // printPAT(pat);
    // printf("temps de fusion les PAT est : %.7f\n", temps_fusion_pat);



    return 0;
}