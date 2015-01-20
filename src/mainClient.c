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
	int sd = se_connecter(adresse_ip);
	//Pour clear le terminal LINUX
	system("clear");
	
	afficher_liste_salons(sd);
	//int nb_salons = get_nb_salon();
	
	
	printf("Veuillez choisir un numéro de salon ou tapez 0 pour quitter\n");
	int choix;
	scanf("%d", &choix);
	
	switch(choix)
	{

		
			case 1:
				//Je ne sais pas encore comment on va faire pour determiner la variable joueur
				//rejoindre_salon(sd, &salon[i_case]);
				//printf("Connexion au salon n°%d\n", i_case);
				break;
			case 0:
				se_deconnecter(sd);
				break;
			default:
				printf("Choix inconnu\n");
				break;
		//}
			
			
	}
	return 0;
}

	

