#include "tries_hybrides.h"

/* Question 1.5 ajouts successifs */

int main() {
    TrieH* th = TH_Vide();

    char* exemple_de_base =
    "A quel genial professeur de dactylographie sommes nous redevables de la superbe phrase ci dessous, un modele du genre, que toute dactylo connait par coeur puisque elle fait appel a chacune des touches du clavier de la machine a ecrire ?";

    char* tmp = exemple_de_base;
    int cpt = 0;

    while (tmp) {
        char* c = tmp;
        while (c[1]!=' ' && c[1]!='\0') {
            c = &c[1];
        }
        if (c[1]==' ') {
            c[1] = '\0';
            th = TH_Ajout(tmp, th, cpt);
            c[1] = ' ';
            cpt++;
            tmp = &c[2];
            continue;
        }
        th = TH_Ajout(tmp, th, cpt);    // Hypothèse : Pour cet exemple, on considère qu'il n'y a pas d'espace
        break;                          // à la fin de la chaîne de caractères
    }

    //th = TH_Ajout("A", th, 0);

    return 0;
}