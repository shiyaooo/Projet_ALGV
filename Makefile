CC = /usr/bin/gcc
CFLAGS = -Wall

all: main_trie inserer_trie suppression_trie main_patrie

# Tries hybrides

tries_hybrides.o: src/tries_hybrides/tries_hybrides.c
	$(CC) $(CFLAGS) -c src/tries_hybrides/tries_hybrides.c

fonctions_avancees.o: src/tries_hybrides/fonctions_avancees.c
	$(CC) $(CFLAGS) -c src/tries_hybrides/fonctions_avancees.c

Patricia_Tries.o: src/Patricia-Tries/Patricia_Tries.c
	$(CC) $(CFLAGS) -c src/Patricia-Tries/Patricia_Tries.c

fonct_avc.o: src/Patricia-Tries/fonct_avc.c
	$(CC) $(CFLAGS) -c src/Patricia-Tries/fonct_avc.c

main_trie: tries_hybrides.o fonctions_avancees.o  
	$(CC) $(CFLAGS) -o main_trie src/tries_hybrides/main.c tries_hybrides.o fonctions_avancees.o -lm

ecriture_lecture.o: src/tries_hybrides/ecriture_lecture.c
	$(CC) $(CFLAGS) -c src/tries_hybrides/ecriture_lecture.c

inserer_trie: tries_hybrides.o fonctions_avancees.o ecriture_lecture.o
	$(CC) $(CFLAGS) -o inserer_trie src/tries_hybrides/inserer_trie.c tries_hybrides.o fonctions_avancees.o ecriture_lecture.o -lm

suppression_trie: tries_hybrides.o fonctions_avancees.o ecriture_lecture.o
	$(CC) $(CFLAGS) -o suppression_trie src/tries_hybrides/suppression_trie.c tries_hybrides.o fonctions_avancees.o ecriture_lecture.o -lm

main_patrie: Patricia_Tries.o fonct_avc.o
	$(CC) $(CFLAGS) -o main_patrie src/Patricia-Tries/main.c Patricia_Tries.o fonct_avc.o

clean:
	rm -f *.o main_trie inserer_trie suppression_trie

.PHONY: all clean