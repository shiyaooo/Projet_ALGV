#include "tries_hybrides.h"
#include "fonctions_avancees.h"
#include <stdio.h>
#include <string.h>

int main() {
    /* Question 1.5 ajouts successifs */
    TrieH* th = TH_Vide();

    char exemple[] =
    "A quel genial professeur de dactylographie sommes nous redevables de la superbe phrase ci dessous, un modele du genre, que toute dactylo connait par coeur puisque elle fait appel a chacune des touches du clavier de la machine a ecrire ?";
    char *mot;

    mot = strtok(exemple, " ,.;?!");

    int cpt = 0;
    while (mot!=NULL) {
        //printf("mot %d : %s\n", cpt, mot);

        // 9 : de (*2 : 4)
        // 33 : du (*2 : 17)
        // 35 : de (*3 : 4)
        // 36 : la (*2 : 10)
        // 38 : a (*2 : 29)
        
        if (cpt==9 || cpt==33 || cpt==35 || cpt==36 || cpt==38) {
            char* m = mot;
            mot = strtok(NULL, " ,.;?!");
            th = TH_Ajout(m, th, cpt);
            cpt++;
            //printf("PASSE\n");
            continue;
        }
        
        char* m = mot;
        th = TH_Ajout(m, th, cpt);
        mot = strtok(NULL, " ,.;?!");
        cpt++;

        //printf("INSERE\n");
    }


    /* Tests fonctions avancées Question 2.6 */
    
    /* tests de Recherche */
    char exemple2[] =
    "A quel genial professeur de dactylographie sommes nous redevables de la superbe phrase ci dessous, un modele du genre, que toute dactylo connait par coeur puisque elle fait appel a chacune des touches du clavier de la machine a ecrire ?";

    mot = strtok(exemple2, " ,.;?!");
    int recherche;
    while (mot!=NULL) {
        recherche = Recherche(th, mot);
        if (recherche==0) {
            printf("\"%s\" n'est pas présent dans le dictionnaire\n", mot);
        }
        else {
            printf("\"%s\" est présent dans le dictionnaire\n", mot);
        }

        mot = strtok(NULL, " ,.;?!");
    }

    recherche = Recherche(th, "toto");
    if (recherche==0) {
        printf("\"toto\" n'est pas présent dans le dictionnaire\n");
    }
    else {
        printf("\"toto\" est présent dans le dictionnaire\n");
    }

    recherche = Recherche(th, "pro");
    if (recherche==0) {
        printf("\"pro\" n'est pas présent dans le dictionnaire\n");
    }
    else {
        printf("\"pro\" est présent dans le dictionnaire\n");
    }

    /* tests de ComptageMots */
    int comptagemots = ComptageMots(th);
    printf("Il y a %d mots dans la phrase de l'exemple de base\n", comptagemots);
    cpt=cpt-5;
    if (cpt==comptagemots) {
        printf("Le compte est bon !\n");
    }
    else {
        printf("erreur de comptage : %d !!!\n", cpt);
    }

    return 0;
}