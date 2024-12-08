#include "tries_hybrides.h"
#include <stdio.h>
#include <string.h>

/* Question 1.5 ajouts successifs */

int main() {
    TrieH* th = TH_Vide();

    char exemple[] =
    "A quel genial professeur de dactylographie sommes nous redevables de la superbe phrase ci dessous, un modele du genre, que toute dactylo connait par coeur puisque elle fait appel a chacune des touches du clavier de la machine a ecrire ?";
    char *mot;

    mot = strtok(exemple, " ,.;?!");
    printf("%s\n",mot);

    int cpt = 0;
    while (mot!=NULL) {
        printf("mot %d : %s\n", cpt, mot);

        // 9 : de (*2 : 4)
        // 19 : que (fini avant quel : 1)
        // 21 : dactylo (fini avant dactylographie : 5)
        // 29 : a (fini avant avant : 28)
        // 31 : des (fini avant dessous : 14)
        // 33 : du (*2 : 17)
        // 35 : de (*3 : 4)
        // 36 : la (*2 : 10)
        // 38 : a (*2 : 29)
        
        if (cpt==9 || cpt==33 || cpt==35 || cpt==36 || cpt==38) {
            char* m = mot;
            mot = strtok(NULL, " ,.;?!");
            th = TH_Ajout(m, th, cpt);
            cpt++;
            printf("PASSE\n");
            continue;
        }
        
        char* m = mot;
        th = TH_Ajout(m, th, cpt);
        mot = strtok(NULL, " ,.;?!");
        cpt++;

        printf("INSERE\n");
    }

    return 0;
}