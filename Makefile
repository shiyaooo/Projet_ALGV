CC = /usr/bin/gcc
CFLAGS = -Wall

all: trie

# Tries hybrides

trie: main_trie inserer_trie suppression_trie liste_mots_trie profondeur_moyenne_trie prefixe_trie

tries_hybrides.o: src/tries_hybrides/tries_hybrides.c
	$(CC) $(CFLAGS) -c src/tries_hybrides/tries_hybrides.c

fonctions_avancees.o: src/tries_hybrides/fonctions_avancees.c
	$(CC) $(CFLAGS) -c src/tries_hybrides/fonctions_avancees.c

main_trie: tries_hybrides.o fonctions_avancees.o  
	$(CC) $(CFLAGS) -o main_trie src/tries_hybrides/main.c tries_hybrides.o fonctions_avancees.o -lm

ecriture_lecture.o: src/tries_hybrides/ecriture_lecture.c
	$(CC) $(CFLAGS) -c src/tries_hybrides/ecriture_lecture.c

inserer_trie: tries_hybrides.o fonctions_avancees.o ecriture_lecture.o
	$(CC) $(CFLAGS) -o inserer_trie src/tries_hybrides/inserer_trie.c tries_hybrides.o fonctions_avancees.o ecriture_lecture.o -lm

suppression_trie: tries_hybrides.o fonctions_avancees.o ecriture_lecture.o
	$(CC) $(CFLAGS) -o suppression_trie src/tries_hybrides/suppression_trie.c tries_hybrides.o fonctions_avancees.o ecriture_lecture.o -lm

liste_mots_trie: tries_hybrides.o fonctions_avancees.o ecriture_lecture.o
	$(CC) $(CFLAGS) -o liste_mots_trie src/tries_hybrides/liste_mots_trie.c tries_hybrides.o fonctions_avancees.o ecriture_lecture.o -lm

profondeur_moyenne_trie: tries_hybrides.o fonctions_avancees.o ecriture_lecture.o
	$(CC) $(CFLAGS) -o profondeur_moyenne_trie src/tries_hybrides/profondeur_moyenne_trie.c tries_hybrides.o fonctions_avancees.o ecriture_lecture.o -lm

prefixe_trie: tries_hybrides.o fonctions_avancees.o ecriture_lecture.o
	$(CC) $(CFLAGS) -o prefixe_trie src/tries_hybrides/prefixe_trie.c tries_hybrides.o fonctions_avancees.o ecriture_lecture.o -lm


clean:
	rm -f *.o main_trie inserer_trie suppression_trie liste_mots_trie profondeur_moyenne_trie prefixe_trie

.PHONY: all clean