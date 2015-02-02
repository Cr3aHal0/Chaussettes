all: serveur mainClient
CXXFLAGS = -lpthread -Wall

mainClient: mainClient.c client.o grille.o message.o
	gcc mainClient.c client.o grille.o message.o -o $@ $(CXXFLAGS)

serveur: serveur.c grille.o salon.o message.o
	gcc serveur.c grille.o salon.o message.o -o $@ $(CXXFLAGS)

client.o: client.c client.h grille.h message.o
	gcc -c client.c message.o -o $@

salon.o: salon.c salon.h grille.h
	gcc -o $@ -c salon.c

grille.o: grille.c grille.h
	gcc -o $@ -c grille.c

clean: 
	rm -rf serveur mainClient *.o	
