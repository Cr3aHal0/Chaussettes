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
	
	
	printf("Veuillez choisir un numéro de serveur ou tapez 10 pour quitter\n");
	int choix;
	scanf("%d", &choix);
	
	switch(choix)
	{
		int i_case, nb_salon;
		
		/*for (i_case = 0; i_case < nb_salon; i_case++)
		{*/
			case 1:
				//Je ne sais pas encore comment on va faire pour determiner la variable joueur
				//rejoindre_salon(&salon[i_case], joueur);
				printf("Connexion salon machin\n");
				break;
			case 10:
				//se_deconnecter();
				printf("Deconnexion du salon\n");
				break;
			default:
				printf("Choix inconnu\n");
				break;
		//}
			
			
	}
}

	

