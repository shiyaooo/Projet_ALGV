# Projet_ALGAV

Langage du projet en C.

Pour compiler, on peut utiliser gcc version 12.2.0 ou 13.2.0 et GNU Make 4.3

Pour gérer les fichiers JSON, on a utilisé la bibliothèque cJSON.h.
Pour l'installer, utiliser la commande suivante :
```sudo apt-get install libcjson-dev```



Avec la croissance rapide des volumes de données, la demande pour des solutions efficaces de stockage et de recherche de mots devient de plus en plusMimportante. Par exemple, une recherche rapide de définitions de mots et une saisie semi-automatique, une indexation et une recherche efficaces de grandes quantités de données textuelles, et bien plus encore. Afin de résoudre ces problèmes, nous avons choisi l’arbre de Trie. Il s’agit d’une structure de données spéciale qui permet de stocker et de rechercher efficacement des chaînes et qui est particulièrement adaptée à la représentation de dictionnaires de mots.

L’objectif du projet est d’implémenter deux structures Trie concurrentes (Patricia Trie et Trie hybride) et leurs fonctions en utilisant le langage C.
Ensuite, nous analyserons les avantages et les inconvénients des deux modèles en termes de performance en les comparant expérimentalement
