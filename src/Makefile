all: serveur client


serveur: serveur.c grille.o
	gcc serveur.c grille.o -o serveur


grille.o: grille.c grille.h
	gcc -o grille.o -c grille.c

client: client.c
	gcc client.c -o client

clean: 
	rm -rf serveur client *.o	