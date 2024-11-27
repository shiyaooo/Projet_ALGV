#ifndef FONCTIONS_AVANCEES_H
#define FONCTIONS_AVANCEES_H

#include "tries_hybrides.h"

/* recherche un mot dans un dictionnaire
 * renvoie 1 ssi le mot est présent dans le dictionnaire,
 *         O sinon 
 */
int Recherche(TrieH* arbre, char* mot);

/* compte les mots présents dans le dictionnaire */
int ComptageMots(TrieH* arbre);

typedef struct List {
    char* mot;
    int entier;
    struct List *suiv;
} List;

/* liste les mots du dictionnaire dans l'ordre alphabétique 
 * renvoie une liste de mots
 */
List* ListeMots(TrieH* arbre);

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

#endif // FONCTIONS_AVANCEES_H