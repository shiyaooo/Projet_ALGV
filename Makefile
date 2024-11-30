CC = gcc
CFLAGS = -Wall

all: main_trie inserer_trie

# Tries hybrides

tries_hybrides.o: src/tries_hybrides/tries_hybrides.c
	$(CC) $(CFLAGS) -c src/tries_hybrides/tries_hybrides.c

fonctions_avancees.o: src/tries_hybrides/fonctions_avancees.c
	$(CC) $(CFLAGS) -c src/tries_hybrides/fonctions_avancees.c

main_trie: tries_hybrides.o fonctions_avancees.o  
	$(CC) $(CFLAGS) -o main_trie src/tries_hybrides/main.c tries_hybrides.o fonctions_avancees.o -lm

inserer_trie: tries_hybrides.o fonctions_avancees.o
	$(CC) $(CFLAGS) -o inserer_trie src/tries_hybrides/inserer_trie.c tries_hybrides.o fonctions_avancees.o -lm

clean:
	rm -f *.o main_trie inserer_trie

.PHONY: all clean