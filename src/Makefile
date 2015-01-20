all: serveur mainClient
CXXFLAGS = -lpthread -Wall

mainClient: mainClient.c client.o
	gcc mainClient.c client.o -o mainClient $(CXXFLAGS)

serveur: serveur.c grille.o salon.o
	gcc serveur.c grille.o salon.o -o serveur $(CXXFLAGS)

client.o: client.c client.h salon.h
	gcc -o client.o -c client.c

salon.o: salon.c salon.h grille.h
	gcc -o salon.o -c salon.c

grille.o: grille.c grille.h
	gcc -o grille.o -c grille.c

clean: 
	rm -rf serveur mainClient *.o	
