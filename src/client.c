#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

//#include "grille.h"
#include "salon.h"
#include "client.h"

#define SUCCESS 0
#define ERROR 1
#define SERVER_PORT 1500
#define MAX_MSG 100


int se_connecter(char* adresse_ip)
{
	int sd, rc, i;
	struct sockaddr_in localAddr, servAddr;
    struct hostent * h;
	
	

    h = gethostbyname(adresse_ip);
    if(h == NULL)
    {
        printf("%s : Unknown host '%s'", "Client", adresse_ip);
        exit(ERROR);
    }

    //Initialisation des champs de la structure servAddr
    servAddr.sin_family = h->h_addrtype;
    memcpy((char *)&servAddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
    servAddr.sin_port = htons(SERVER_PORT);

    //Creation de la socket
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if(sd < 0)
    {
        perror("Cannot open socket : ");
        exit(ERROR);
    }

    //Initialisation des champs de la structure localAddr
    localAddr.sin_family = AF_INET;
    localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    localAddr.sin_port = htons(0);

    //Bind
    if(bind(sd, (struct sockaddr *) &localAddr, sizeof(localAddr)) < 0)
    {
        printf("%s : cannot bind port TCP %u\n", "Client", SERVER_PORT);
        perror("Error : ");
        exit(ERROR);
    }

    //Connexion au serveur
    if(connect(sd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)
    {
        perror("Cannot connect : ");
        exit(ERROR);
    }
	
	return 1;
}




int se_deconnecter(int sd)
{
	printf("Deconnexion du client en cours");
	close(sd);
	printf("Deconnexion reussi");
}

int rejoindre_salon(Salon_t* salon, int joueur)
{
	
}


int main(int argc, char * argv[])
{

    
    int grille[TAILLE_LIGNE][TAILLE_COLONNE];
    
	int co = se_connecter("127.0.0.1");
	if(co == 1) printf("Connexion ok\n");
   


    
    /*if(write(sd, argv[2], strlen(argv[2])+1) < 0)
    {
        printf("Cannot send data : ");
        close(sd);
        exit(ERROR);
    }
	
	
    printf("%s : data %u send (%s)\n", argv[0], i-1, argv[2]);
    
    int couleur;
    read(sd, grille, sizeof(int)*TAILLE_COLONNE*TAILLE_LIGNE);
    
    afficherGrille(grille);*/
   

    return(SUCCESS);
}


