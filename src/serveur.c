/**
 * Note : 
 * 	Le serveur possède plusieurs salons (10)
 * 	Quand un joueur joue sur une grille, il joue sur la grille du salon, et pas directement depuis le serveur.
 * 
 **/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "serveur.h"

#define LOCALHOST "127.0.0.1"
#define NB_SALONS 4

#define SUCCESS 0
#define ERROR 1
#define SERVER_PORT 1500

int main(int argc,char *argv[])
{
    
    Server server;
    chargerSalons(&server);

	int i, j, k;
	int couleur;
	char position[1];
	//Salon_t liste_salon[10];
	int grille[TAILLE_LIGNE][TAILLE_COLONNE] = {0};

    int sd,newSd;
    socklen_t cliLen;

    struct sockaddr_in cliAddr, servAddr;


    //Creation de la socket
    sd = socket(AF_INET,SOCK_STREAM,0);
    if(sd<0)
    {
        perror("Cannot open socket");
        exit(ERROR);
    }

    //Initialisation des champs de la structure servAddr
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons (SERVER_PORT);

    //Bind
    if(bind(sd,(struct sockaddr *) &servAddr, sizeof(servAddr))<0)
    {
        perror("Cannot bind port");
        exit(ERROR);
    }

    //Listen
    listen(sd,5);

    while (1)
    {
        printf("%s : waiting for data on port TCP %u \n",argv[0],SERVER_PORT);
        cliLen = sizeof(cliAddr);

	//Acceptation de la connexion
		
			newSd = accept(sd,(struct sockaddr *) &cliAddr,&cliLen);
		    if(newSd<0)
		    {
		        perror("Cannot accept connection");
		        exit(ERROR);
			}


  
			read(newSd, position, sizeof(int));
			printf("%s: received from %s:TCP%d : %s \n",argv[0],inet_ntoa(cliAddr.sin_addr),ntohs(cliAddr.sin_port), position);
			
			placerJeton(atoi(position), ROUGE, grille);
			afficherGrille(grille);
			//write(newSd, ROUGE, sizeof(int));
			//Envoi de la grille apres que le joueur ai joué
			write(newSd, grille, sizeof(int)*TAILLE_COLONNE*TAILLE_LIGNE);
			
			
        

    }

    freeSalons(&server);

    return(SUCCESS);
}


void chargerSalons(Server *server) {
    server->salons = malloc(NB_SALONS * sizeof(Salon_t));
    int i;
    for(i = 0; i < NB_SALONS; i++) {
        Salon_t salon;
        salon.nb_joueurs = 0;     

        int x, y;
        for (x = 0; x < TAILLE_LIGNE; x++) {
            for(y = 0; y < TAILLE_COLONNE; y++) {
                salon.grille[x][y] = 0;
            }
        }

        server->salons[i] = salon; 
        printf("Salon %d créé\n", i+1);
    }
}

void freeSalons(Server *server) {
    free(server->salons);
}


