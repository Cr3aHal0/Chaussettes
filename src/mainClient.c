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
	
	int choix;
    do {
	    printf("Veuillez choisir un numéro de salon ou tapez 0 pour quitter\n");
	    scanf("%d", &choix);			
	}while (choix < 0 && choix > 4);
	

    if (choix == 0) {
        se_deconnecter(sd);
        exit(1);
    }

	Couleur couleur = rejoindre_salon(sd, choix);
	printf("Connexion au salon n°%d avec la couleur %d\n", choix, couleur);

	if (couleur == 0) {
		printf("Erreur, impossible de rejoindre le salon\n");
		exit(1);
	}

	if (couleur == ROUGE) {
		int commencee = 0;
		printf("En attente d'un autre joueur...\n");
		while (commencee == 0) {
			commencee = partie_commencee(sd, choix);
		}
		printf("Un deuxième joueur à rejoint la salle !\n");
	}
	else {
		printf("La partie est sur le point de commencer !\n");
	}

	int end = 0;
	Couleur grille[TAILLE_LIGNE][TAILLE_COLONNE];

	while (end == 0) {
		printf("Partie en cours...\n");
		Message* signal = get_signal(sd);

		switch(signal->action) {
			//Début de partie
			case GAME_START:
				printf("La partie commence !!!\n");
				initGrille(grille);
				afficherGrille(grille);
			break;

			//Partie remportée par un joueur
			case PLAYER_WIN:
				end = 1;
				printf("Partie terminé : victoire du joueur %d\n", signal->joueur);
			break;

			//Tour d'un joueur
			case PLAYER_TURN:

			break;

			//Un joueur pose un jeton
			case PLAYER_PUT_TOKEN:

			break;

			default:

			break;
		}

		sleep(4);
	}

	//Tant que la partie n'est pas finie
	/*int i;
	
	for (i = 0; i < 10; i++)
	{
		//Une fois que le joueur est connecté, on lui affiche la grille pour chaque fois ou un jeton est placé
		int position;
		printf("Position du jeton à placer\n");
		scanf("%d", &position);
		placer_jeton(sd, position);
	}*/
	
	
	return 0;
}

	

