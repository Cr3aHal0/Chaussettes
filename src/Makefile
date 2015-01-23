all: serveur mainClient
CXXFLAGS = -lpthread -Wall

mainClient: mainClient.c client.o grille.o
	gcc mainClient.c client.o grille.o -o mainClient $(CXXFLAGS)

serveur: serveur.c grille.o salon.o message.c
	gcc serveur.c message.c grille.o salon.o -o serveur $(CXXFLAGS)

client.o: client.c client.h grille.h message.c
	gcc -c client.c -o client.o

salon.o: salon.c salon.h grille.h
	gcc -o salon.o -c salon.c

grille.o: grille.c grille.h
	gcc -o grille.o -c grille.c

clean: 
	rm -rf serveur mainClient *.o	
