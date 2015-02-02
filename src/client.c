//#include "grille.h"

#include "client.h"

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
 * 	      Possibilité de la mettre en globale pour eviter l'appel systematique dans chaque fonction ?
*/





int se_connecter(char* adresse_ip)
{
	int sd;
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




void se_deconnecter(int sd)
{
	printf("Deconnexion du client en cours...\n");
	sleep(3);
	close(sd);
	printf("Deconnexion reussie\nA bientôt!\n");
}

//Lorsque le joueur rejoint un salon, ce dernier lui attribue une couleur
Couleur rejoindre_salon(int sd, int num_salon)
{
	
	//Envoi du numero de salon au serveur
	write(sd, &num_salon, sizeof(int));
	int couleur;
	//Reception de la couleur attribuée par le salon
	read(sd, &couleur, sizeof(int));
	switch(couleur)
	{
		case 1:
			printf("Vous etes le joueur ROUGE\n");
			break;
		case 2:
			printf("Vous etes le joueur JAUNE\n");
			break;
		default:
			printf("Aucune couleur attribuée\n");
			break;
	}	
	return couleur;
	
}

void afficher_liste_salons(int sd)
{
	//reception des infos salons sous forme de buffer
	
	printf("Affichage des salons :\n");
}

//A definir :
void placer_jeton(int sd, int position_x)
{
	//Envoi de la position x de la grille du salon
	if (isdigit(position_x)){
		printf("Position inconnue\n");
	}
	else
	{
		write(sd, &position_x, sizeof(int));
	}
}

void afficher_grille(int sd)
{
	//Envoi de buffer par le serveur afin de reconstruire la grille
	int i;
	//for (i = 0; i
	
}

int partie_commencee(int sd, int choix) {
    int i;
    read(sd, &i, sizeof(int));
	//printf("Statut reçu : %d\n", i);
    return (i==1) ? 1 : 0;
}

Message* get_signal(int sd) {
	char* buf = malloc(TAILLE_MAX * sizeof(char));
	read(sd, buf, TAILLE_MAX * sizeof(char));
	//printf("Message reçu : %s\n", buf);
	return fromString(buf);
}
