#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Patricia_Tries.h"
#include <ctype.h>  

int main() {
    /*****************************EX1*****************************/

    // Q1.1 Déterminer un caractère parmi les 128 du code ASCII pour indiquer la fin d'un mot.
    printf("/************************ Q.1.1 Déterminer un caractère parmi les 128 du code ASCII pour indiquer la fin d'un mot. ************************/\n\n");
    printf("En général, le caractère '\\0' est utilisé pour indiquer la fin ");
    printf("d'une chaîne de caractères en C. Cependant, dans l'implémentation ");
    printf("d'un arbre de dictionnaire (patricia_trie), pour éviter tout ");
    printf("conflit avec le caractère de fin de chaîne en C, nous pouvons ");
    printf("choisir d'utiliser d'autres caractères ASCII peu courants dans un mot.");
    printf("Comme par exemple le caractère SPACE (ASCII 32 ou '\\x20'), ");
    printf("Cela permet d'assurer qu'aucun mot valide ne soit confondu avec le marqueur de fin.\n");

    printf("/************************ Q1.2 Testez les primitives de base concernant les Patricia-tries. ************************/\n\n");
    printf("creer un noeud de PAT:\n");
    char* m = "abcd ";
    Node* n = NodeCons(m);
    printNode(n,0);

    printf("\ncreer un PAT: \n");
    PAT* p = PATCons(n);
    printPAT(p);

    printf("\nclé et sa valeur de noeud:\n");
    printf("(%s, %d)\n", Rac(p->node[0]), Val(p->node[0]));

    printf("\najouter un fils dans le neoud: \n"); 
    char* s ="de ";
    Node* f = NodeCons(s);
    ajouter_fils(n,f);
    s = "cd ";
    Node* ff = NodeCons(s);
    ajouter_fils(n,ff);
    printNode(n,0);

    printf("\najouter un noeud dans PAT: \n"); 
    s ="sss ";
    Node* f1 = NodeCons(s);
    ajouter_racine(&p,f1);
    printPAT(p);

    printf("\nTest chaine1 est préfixe de chaine2 ou pas: \n"); 
    char *chaine1 = "sgfyh ";
    char *chaine2 = "sgfyhlm<";
    if (estPrefixe(chaine1, chaine2)) {
        printf("'%s' est un préfixe de '%s'\n", chaine1, chaine2);
    } else {
        printf("'%s' n'est pas un préfixe de '%s'\n", chaine1, chaine2);
    }

    printf("\nTest le nombre de préfixe commun de c et m: \n"); 
    char c[] = "bonjour ";
    char mm[] = "bonsoir ";

    int prefix_common = prefixe(c, mm);
    printf("Le nb de préfixe commun est : '%d'\n", prefix_common);

    printf("\nTest l'insérer les mot dans PAT: \n"); 
    // char* tmp = "TACG";
    // char* tmp2 = "AAT";
    // char* tmp3 = "AT";
    // char* tmp4 = "CGGA";
    // char* tmp5 = "TAC";
    char* tmp = "de";
    char* tmp2 = "dactylographie";
    char* tmp3 = "de";
    char* tmp4 = "dessous";
    char* tmp5 = "du";
    char* tmp6 = "dactylo";
    char* tmp7 = "des";
    char* tmp8 = "du";
    char* tmp9 = "de";
    char* tmp10 = "de";

    PAT* pp = NULL;
    PATinsertion(&pp, tmp);
    PATinsertion(&pp, tmp2);
    PATinsertion(&pp, tmp3);
    PATinsertion(&pp, tmp4);
    PATinsertion(&pp, tmp5);
    PATinsertion(&pp, tmp6);
    PATinsertion(&pp, tmp7);
    PATinsertion(&pp, tmp8);
    PATinsertion(&pp, tmp9);
    PATinsertion(&pp, tmp10);
    printf("PAT est:\n");
    printPAT(pp);

    printf("/************************ Q1.3 Ajouts successifs l'arbre représentant la phrase suivante,. ************************/\n\n");

    char exemple[] =
    "A quel genial professeur de dactylographie sommes nous redevables de la superbe phrase ci dessous, un modele du genre, que toute dactylo connait par coeur puisque elle fait appel a chacune des touches du clavier de la machine a ecrire ?";
    PAT* pat = PATVide();
    char *mot;
    mot = strtok(exemple, " ");
    while (mot != NULL ) {
        int isp = ispunct(mot[strlen(mot)-1]);
        if(!isp){
            printf ("%s\n", mot);
            PATinsertion(&pat, mot);
        }else if(strlen(mot)==1){
            printf ("%s\n", mot);
            PATinsertion(&pat, mot);
        }
        else{
            char* tmp = strndup(mot, strlen(mot)-1);
            printf ( "%s\n", tmp);
            PATinsertion(&pat, tmp);
            free(tmp);
            char pon[2] = {mot[strlen(mot)-1], '\0'};
            printf ( "%s\n", pon);
            PATinsertion(&pat, pon);
        }
        // On demande le token suivant.
        mot = strtok ( NULL, " ");
    }
    
    printPAT(pat);
    


    

    // liberer les memoire 
    //libererNode(n);
    libererPAT(p);
    libererPAT(pp);

    return 0;
}
