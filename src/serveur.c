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

#include "grille.h"



#define LOCALHOST "127.0.0.1"


#define SUCCESS 0
#define ERROR 1
#define SERVER_PORT 1500


int main(int argc,char *argv[])
{

	int i, j, k;
	int couleur;
	char position[1];
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
			
        

    }

    return(SUCCESS);
}



