CC = /usr/bin/gcc
CFLAGS = -Wall

all: trie patricia main_etude_patricia main_etude_trie

# Tries hybrides

trie: main_trie inserer_trie suppression_trie liste_mots_trie profondeur_moyenne_trie prefixe_trie

patricia: main_patrie inserer_patricia suppression_patricia liste_mots_patricia profondeur_moyenne_patricia prefixe_patricia fusion_patricia

tries_hybrides.o: src/tries_hybrides/tries_hybrides.c
	$(CC) $(CFLAGS) -c src/tries_hybrides/tries_hybrides.c

fonctions_avancees.o: src/tries_hybrides/fonctions_avancees.c
	$(CC) $(CFLAGS) -c src/tries_hybrides/fonctions_avancees.c

Patricia_Tries.o: src/Patricia-Tries/Patricia_Tries.c
	$(CC) $(CFLAGS) -c src/Patricia-Tries/Patricia_Tries.c

fonct_avc.o: src/Patricia-Tries/fonct_avc.c
	$(CC) $(CFLAGS) -c src/Patricia-Tries/fonct_avc.c

patricia_json.o: src/Patricia-Tries/patricia_json.c
	$(CC) $(CFLAGS) -c src/Patricia-Tries/patricia_json.c -I/usr/include/cjson -lcjson

fonct_avc_cpt.o: src/Patricia-Tries/fonct_avc_cpt.c
	$(CC) $(CFLAGS) -c src/Patricia-Tries/fonct_avc_cpt.c

experimentale.o: src/experimentale/experimentale.c
	$(CC) $(CFLAGS) -c src/experimentale/experimentale.c -I/usr/include/cjson -lcjson

experimentale_trie.o: src/experimentale/experimentale_trie.c
	$(CC) $(CFLAGS) -c src/experimentale/experimentale_trie.c

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

main_patrie: Patricia_Tries.o fonct_avc.o patricia_json.o fonct_avc_cpt.o
	$(CC) $(CFLAGS) -o main_patrie src/Patricia-Tries/main.c Patricia_Tries.o fonct_avc.o patricia_json.o fonct_avc_cpt.o -I/usr/include/cjson -lcjson

inserer_patricia: Patricia_Tries.o fonct_avc.o patricia_json.o
	$(CC) $(CFLAGS) -o inserer_patricia src/Patricia-Tries/test_patricia/inserer_patricia.c Patricia_Tries.o fonct_avc.o patricia_json.o -I/usr/include/cjson -lcjson

suppression_patricia: Patricia_Tries.o fonct_avc.o patricia_json.o
	$(CC) $(CFLAGS) -o suppression_patricia src/Patricia-Tries/test_patricia/suppression_patricia.c Patricia_Tries.o fonct_avc.o patricia_json.o -I/usr/include/cjson -lcjson

liste_mots_patricia: Patricia_Tries.o fonct_avc.o patricia_json.o
	$(CC) $(CFLAGS) -o liste_mots_patricia src/Patricia-Tries/test_patricia/liste_mots_patricia.c Patricia_Tries.o fonct_avc.o patricia_json.o -I/usr/include/cjson -lcjson

profondeur_moyenne_patricia: Patricia_Tries.o fonct_avc.o patricia_json.o
	$(CC) $(CFLAGS) -o profondeur_moyenne_patricia src/Patricia-Tries/test_patricia/profondeur_moyenne_patricia.c Patricia_Tries.o fonct_avc.o patricia_json.o -I/usr/include/cjson -lcjson

prefixe_patricia: Patricia_Tries.o fonct_avc.o patricia_json.o
	$(CC) $(CFLAGS) -o prefixe_patricia src/Patricia-Tries/test_patricia/prefixe_patricia.c Patricia_Tries.o fonct_avc.o patricia_json.o -I/usr/include/cjson -lcjson

fusion_patricia: Patricia_Tries.o fonct_avc.o patricia_json.o
	$(CC) $(CFLAGS) -o fusion_patricia src/Patricia-Tries/test_patricia/fusion_patricia.c Patricia_Tries.o fonct_avc.o patricia_json.o -I/usr/include/cjson -lcjson

main_etude_patricia: experimentale.o  Patricia_Tries.o fonct_avc.o patricia_json.o fonct_avc_cpt.o
	$(CC) $(CFLAGS) -o main_etude_patricia src/experimentale/main_etude_patricia.c experimentale.o  Patricia_Tries.o fonct_avc.o patricia_json.o fonct_avc_cpt.o -I/usr/include/cjson -lcjson

main_etude_trie: experimentale_trie.o tries_hybrides.o fonctions_avancees.o ecriture_lecture.o
	$(CC) $(CFLAGS) -o main_etude_trie src/experimentale/main_etude_trie.c experimentale_trie.o tries_hybrides.o fonctions_avancees.o ecriture_lecture.o -lm

clean:
	rm -f *.o main_trie inserer_trie suppression_trie liste_mots_trie profondeur_moyenne_trie prefixe_trie patricia main_etude_patricia main_etude_trie

.PHONY: all clean