#include "tries_hybrides.h"
#include <string.h>

/* recherche un mot dans un dictionnaire
 * renvoie 1 ssi le mot est présent dans le dictionnaire,
 *         O sinon 
 */
int Recherche(TrieH* arbre, char* mot) {
    if (EstVide(arbre)==1) {
        if (strlen(mot) == 1 && mot[0]==Rac(arbre) && Val(arbre)>=0) {
            return 1;
        } else {
            return 0;
        }
    } else {
        char pm = prem(mot);
        char rac = Rac(arbre);

        if (strlen(mot) == 1) {
            if (rac == pm) {
                if (Val(arbre)!=-1) {
                    return 1;
                }
                return 0;
            }
            //return 0;
        }
        
        if (pm < rac) {
            return Recherche(Inf(arbre), mot);
        }
        else if (pm > rac) {
            return Recherche(Sup(arbre), mot);
        }
        return Recherche(Eq(arbre), reste(mot));
    }
}

/* compte les mots présents dans le dictionnaire */
int ComptageMots(TrieH* arbre) {
    if (EstVide(arbre)==1) {
        return 0;
    } else {
        if (Val(arbre)!=-1) {
            return 1 + ComptageMots(Sup(arbre)) + ComptageMots(Eq(arbre)) + ComptageMots(Inf(arbre));
        }
        return ComptageMots(Sup(arbre)) + ComptageMots(Eq(arbre)) + ComptageMots(Inf(arbre));
    }
}

/* liste les mots du dictionnaire dans l'ordre alphabétique 
 * renvoie une liste de mots
 */
char** ListeMots(TrieH* arbre);

/* compte les pointeurs vers Nil */
int ComptageNil(TrieH* arbre);

/* calcule la hauteur de l'arbre */
int Hauteur(TrieH* arbre);

/* calcule la profondeur moyenne des feuilles de l'arbre */
int ProfondeurMoyenne(TrieH* arbre);

/* prend un mot A en arguments
 * et qui indique combien de mots du dictionnaire
 * le mot A est préfixe
 */
int Prefixe(TrieH* arbre, char* mot);

/* prend un mot en argument
 * et qui le supprime de l'arbre s'il y figure
 */
TrieH* Suppression(TrieH* arbre, char* mot);
