all: serveur client
CXXFLAGS = -lpthread

serveur: serveur.c grille.o salon.o salon.o
	gcc serveur.c grille.o salon.o -o serveur $(CXXFLAGS)

client: client.c grille.o salon.o
	gcc client.c grille.o -o client $(CXXFLAGS)

salon.o: salon.c salon.h
	gcc -o salon.o -c salon.c

grille.o: grille.c grille.h
	gcc -o grille.o -c grille.c

clean: 
	rm -rf serveur client *.o	
