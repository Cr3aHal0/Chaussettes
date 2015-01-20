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

        //Rejoindre un salon
        int couleur = rejoindreSalon(&server, cliAddr.sin_addr, 1);

		if(newSd<0)
		{
		    perror("Cannot accept connection");
		    exit(ERROR);
		}
		
  
		//read(newSd, position, sizeof(int));
		//printf("%s: received from %s:TCP%d : %s \n",argv[0],inet_ntoa(cliAddr.sin_addr),ntohs(cliAddr.sin_port), position);
			
		//placerJeton(atoi(position), ROUGE, grille);
		//afficherGrille(grille);
		//Envoi de la grille apres que le joueur ai joué
		char test[5] = "Test";
		write(newSd, test, strlen(test)+1);
			
			
        

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
        salon.joueur_courant = -1;
        salon.liste_joueur[0] = -1;
        salon.liste_joueur[1] = -1;
		
        int x, y;
        for (x = 0; x < TAILLE_LIGNE; x++) {
            for(y = 0; y < TAILLE_COLONNE; y++) {
                salon.grille[x][y] = 0;
            }
        }

        server->salons[i] = salon; 
        printf("Salon %d créé\n", i+1);
    }

    server->addr = (struct in_addr *) malloc (NB_SALONS * 2 * sizeof(struct in_addr));
    if (server->addr == NULL) {
			printf("Holy shit");
	}

    server->nb_clients = 0;
}

void freeSalons(Server *server) {
    free(server->salons);
}

int rejoindreSalon(Server *server, struct in_addr client, int num) {
    if (num < 1 || num > NB_SALONS) {
        return 0;
    }
    Salon_t salon = server->salons[num-1];
    if (aJoueur(server, client) >= 0) {
        return 0;
    }
    int idJoueur = ajouter_client(server, client);
    printf("Joueur ajouté au salon %d : %s \n", num, inet_ntoa(client));
        
    int retour = ajouter_joueur(&salon, idJoueur); 
    if (retour < 0) {
        return 0;
    }
}

int aJoueur(Server server, struct in_addr client) {
    int i = 0;
    while (i < server.nb_clients && client.s_addr != server.addr[i].s_addr) {
        i++;
    }
    return (client.s_addr == server.addr[i].s_addr) ? i : -1;
}

int ajouter_client(Server *server, struct in_addr client) {
	//printf("Nombre de clients avant opération : %d \n", server->nb_clients);
    server->addr[server->nb_clients++] = client;
    //printf("Nombre de clients après opération : %d \n", server->nb_clients);
    return server->nb_clients-1;
}
