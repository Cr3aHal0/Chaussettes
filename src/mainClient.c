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
	//Possibilité de faire ça avec un for?
	switch(choix)
	{

		
			case 1:
				rejoindre_salon(sd, 1);
				printf("Connexion au salon n°1\n");
				break;
			
			case 2:
				rejoindre_salon(sd, 2);
				printf("Connexion au salon n°2\n");
				break;	
				
			case 3:
				rejoindre_salon(sd, 1);
				printf("Connexion au salon n°1\n");
				break;
			
			case 4:
				rejoindre_salon(sd, 2);
				printf("Connexion au salon n°2\n");
				break;	
					
			case 0:
				se_deconnecter(sd);
				break;
				
			default:
				printf("Choix inconnu\n");
				break;
			
			
	}
	
	//Tant que la partie n'est pas finie
	int i;
	
	for (i = 0; i < 10; i++)
	{
		//Une fois que le joueur est connecté, on lui affiche la grille pour chaque fois ou un jeton est placé
		int position;
		printf("Position du jeton à placer\n");
		scanf("%d", &position);
		placer_jeton(sd, position);
	}
	
	
	return 0;
}

	

