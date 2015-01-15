#include <stdio.h>
#include <stdlib.h>
#include "client.h"



int main()
{

	printf("********** Bienvenue sur le client Puissance4 TCP **********\n");
	printf("Veuillez entrer votre serveur de connexion : ");
	char adresse_ip[16];
	scanf("%s", adresse_ip);
	printf("Tentative de connexion au serveur %s en cours...\n\n\n\n", adresse_ip);
	//se_connecter(adresse_ip);
	//Pour clear le terminal LINUX
	system("clear");
	
	//afficher_liste_salon();
	printf("Connecté au serveur %s", adresse_ip);
	printf("\n\n\n");
	
	printf("1\tSalon 1\n");
	printf("\tNombre de joueurs : 0/2\n");
	printf("\tPourcentage de la partie en cours 0/100\n\n");

	printf("2\tSalon 2\n");
	printf("\tNombre de joueurs : 2/2\n");
	printf("\tPourcentage de la partie en cours 86/100\n");
	
	
		
	

	
}
