all: serveur client


serveur: serveur.c grille.o
	gcc serveur.c grille.o -o serveur

client: client.c grille.o
	gcc client.c grille.o -o client

grille.o: grille.c grille.h
	gcc -o grille.o -c grille.c

clean: 
	rm -rf serveur client *.o	