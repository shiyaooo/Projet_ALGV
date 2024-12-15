#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Patricia_Tries.h"
#include "fonct_avc.h"
#include "patricia_json.h"
#include <ctype.h>  
#include <stdbool.h>
#include <unistd.h>
//  gcc -Wall -o main main.c Patricia_Tries.c fonct_avc.c ecriture_lecture_patricia.c -I/usr/include/cjson -lcjson

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
    char* tmp9 = "des";
    char* tmp10 = "AACG";

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

    printf("/************************ Q1.3 Ajouts successifs l'arbre représentant la phrase suivante. ************************/\n\n");

    char exemple[] =
    "A quel genial professeur de dactylographie sommes nous redevables de la superbe phrase ci dessous, un modele du genre, que toute dactylo connait par coeur puisque elle fait appel a chacune des touches du clavier de la machine a ecrire ?";
    //"La phrase ci-dessus, quelle que soit la situation d'énonciation, signifie qu'il fait beau. Rien de plus, rien de moins. En tant qu'énoncé par contre, elle peut avoir des sens différents. S'il fait vraiment beau, le sens de l'énoncé ci-dessus correspond à la signification de la phrase. Si, au contraire, le temps n'est pas beau, et que l'énonciateur s'exprime ironiquement, le sens de l'énoncé sera : ' Il ne fait vraiment pas beau ! ', tandis que la signification de la phrase restera inchangée : ' Il fait beau. '";
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
    

    printf("/************************ Q2.6 Écrire les algorithmes suivants pour PAT. ************************/\n\n");
    printf("Recher un mot dans PAT:\n");
    m = "des";
    bool isExist = recherchePAT(pat,m);
    printf("le mot '%s' est dans l'arbre ? = %d\n", m, isExist);

    printf("\nLes mots présents dans le dictionnaire: \n");
    int nb_mot = ComptageMotsdansPAT(pat);
    printf("il y a %d mots présents dans le dictionnaire (avec les ponctuations).\n",nb_mot);

    printf("\nliste les mots du dictionnaire dans l’ordre alphabétique:\n");
    char** list_mot =  ListeMotsdansPAT(pat);
    printf("Mots dans le Patricia Trie :\n");
    for (int i = 0; list_mot[i] != NULL; i++) {
        printf("%s\n", list_mot[i]);
    }

    printf("\nCompte les pointeurs vers Nil: \n");
    int totalNil = ComptageNildansPAT(pat);
    printf("Nombre total de pointeurs NULL : %d\n", totalNil);

    printf("\nCalcule la hauteur de l’arbre PAT:\n");
    int hauteur = HauteurPAT(pat);
    printf("Hauteur du Patricia Trie : %d\n", hauteur);

    printf("\nCalcule la profondeur moyenne des feuilles de l’arbre PAT:\n");
    int pronfondeur = ProfondeurMoyennePAT(pat);
    printf("Profondeur moyenne des feuilles du Patricia Trie : %d\n", pronfondeur);

    
    printf("\nCompter de mots du dictionnaire le mot A est préfixe.\n");
    m = "que";
    int nb_prefixe = PrefixedansPAT(pat, m);
    printf("Il y a %d de mots du dictionnaire le mot '%s' est préfixe.\n", nb_prefixe, m);

    printf("\nSupprimer un mot dans l'arbre PAT.\n");
    m = "dse";
    printPAT(pp);
    PATsuppression(&pp, m);
    printf("PAT apres supprime le mot '%s' :\n", m);
    printPAT(pp);

    printf("\nFusionner deux Patricia-tries en un seul.\n");
    printf("les deux Patricia-tries sont: \n");
    // Node* t = NodeCons("ABC ");
    // PAT* pt = PATCons(t); 
    printPAT(pp);
    printf(" et :\n");
    Node* tt = NodeCons("ABC ");
    PAT* ptt = PATCons(tt);
    PATinsertion(&ptt, "AACG");
    PATinsertion(&ptt, "ABCdef"); 
    PATinsertion(&ptt, "dessouss"); 
    printPAT(ptt);
    // PAT* test = PATfusion(pp, ptt);
    // printf("Le resultat obtenu est :\n");
    // printPAT(test);

    printf("\nAfficher un noeud en format JSON\n") ;
    //打印树的 JSON 形式
    print_node_json(ptt->node[0]);

    // printf("\nAfficher un PAT en format JSON\n") ;
    // print_pat_json(pat);

    // printf("\nEcrire un PAT en format JSON dans un file\n") ;
    ecrire_patricia("exemple.json",pat);

    printf("\nConstruit le noeud depuis le format JSON\n") ;
    printNode(ptt->node[0],0);
    cJSON* nj = node_to_json(ptt->node[0]);
    Node* jsonn = json_to_node(nj);
    printf("apres construire\n");
    printNode(jsonn,0);

    PAT* pj_ess = PATVide();
    PATinsertion(&pj_ess, "car");
    PATinsertion(&pj_ess, "cat");
    PATinsertion(&pj_ess, "cart");
    PATinsertion(&pj_ess, "dog");
    PATinsertion(&pj_ess, "bat");
    printf("\nConstruit le PAT depuis le format JSON\n") ;
    printPAT(pj_ess);
    cJSON* pj = pat_to_json(pj_ess);
    PAT* jsonp = json_to_pat(pj);
    printf("apres construire\n");
    printPAT(jsonp);

    PATsuppression(&pj_ess, "car");
    PATsuppression(&pj_ess, "cat");
    PATsuppression(&pj_ess, "cart");
    PATsuppression(&pj_ess, "dog");
    PATsuppression(&pj_ess, "bat");
    printf("apres suppression\n");        
    printPAT(pj_ess);



    // Libération de la mémoire
    for (int i = 0; list_mot[i] != NULL; i++) {
        free(list_mot[i]);
    }
    free(list_mot);

    //libererNode(n);
    libererPAT(p);
    // libererPAT(pp);
    libererPAT(pat);

    return 0;
}
