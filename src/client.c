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

/**
 * Un client peut :
 * 		Se connecter au serveur
 * 		Se deconnecter du serveur
 * 		Voir la liste des salons
 * 		rejoindre un salon
 * 		Quitter un salon
 * 		voir la grille de jeu
 * 		placer un jeton
 * 
 * 
 * NOTE : Chaque fonction utilise la socket reçu apres la connexion
 * 	      Possibilité de la mettre en globale pour eviter l'appel systematique dans chaque fonction 
*/

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
	
	return sd;
}




int se_deconnecter(int sd)
{
	printf("Deconnexion du client en cours");
	close(sd);
	printf("Deconnexion reussi");
}

int rejoindre_salon(int sd, int num_salon)
{
	//Envoi du numero de salon au serveur
	//write(sd, num_salon, sizeof(int));
}

void afficher_liste_salons(int sd)
{
	//reception des infos salon
}

Couleur get_couleur_from_salon(int sd)
{
	//Reception de la couleur attribuée par le salon
	/*read(sd, couleur, sizeof(int));
	switch(atoi(couleur))
	{
		case 1:
			printf("Vous etes le joueur ROUGE");
		case 2:
			printf("Vous etes le joueur JAUNE");
		default:
			printf("Aucune couleur attribuée");
	}*/
}


//A definir :
//Est ce que le serveur connait le salon auquel le joueur est associé, ou est ce que le joueur stipule le salon?
void placer_jeton(int sd, int position_x)
{
	//Envoi de la position x de la grille du salon
	//write(sd, position_x, sizeof(int));
}

void afficher_grille(int sd)
{
	//Reception de la grille, ou juste du rendu (envoi de buffer a reconstruire?)
	//read(sd, 
	
}


int main(int argc, char * argv[])
{
	int couleur;
	char test[5];
    
    int grille[TAILLE_LIGNE][TAILLE_COLONNE];
    
	int co = se_connecter("127.0.0.1");
	if(co == 1) printf("Connexion ok\n");
	read(co, test, strlen(test)+1);
	printf("Reception de : %s\n", test);


    
   /* if(write(sd, argv[2], strlen(argv[2])+1) < 0)
    {
        printf("Cannot send data : ");
        close(sd);
        exit(ERROR);
    }
	
	
    printf("%s : data %u send (%s)\n", argv[0], i-1, argv[2]);
    
    int couleur;
    read(sd, grille, sizeof(int)*TAILLE_COLONNE*TAILLE_LIGNE);
    
    afficherGrille(grille);
   */

    return(SUCCESS);
}


