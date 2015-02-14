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
			commencee = partie_commencee(sd);
		}
		printf("Un deuxième joueur à rejoint la salle !\n");
	}
	else {
		int commencee = 0;
		while (commencee == 0) {
			commencee = partie_commencee(sd);
		}
		printf("La partie est sur le point de commencer !\n");
	}

	Couleur grille[TAILLE_LIGNE][TAILLE_COLONNE];

	//Début de partie
	printf("La partie commence !!!\n");
	initGrille(grille);
	afficherGrille(grille);

	int end = 0;
	int x;
	int waiting = 1;
	char *saisie = malloc(sizeof(saisie));

	while (end == 0) {
		printf("Partie en cours...\n");
		printf("En attente du tour du joueur adverse ...\n");
		Message *signal = malloc(sizeof(*signal));
		signal = get_signal(sd);

		if (signal != NULL) {
			switch(signal->action) {

				//Partie remportée par un joueur
				case PLAYER_WIN:
					end = 1;
					if (signal->couleur == couleur) {
						printf("Vous avez gagné !\n");
					}
					else
					{
						printf("Vous avez perdu :'(\n");
					}
					//printf("Partie terminé : victoire du joueur %d\n", signal->couleur);
				break;

				//Tour d'un joueur
				case PLAYER_TURN:
					if (signal->couleur == couleur) {
						printf("\n------\n A votre tour de jouer ! \n------\n");
						waiting = 0;
					}

					if (waiting == 0) {
						int fail = 1;
						while (fail == 1 ) {
							printf("Dans quelle colonne souhaitez-vous  ajouter un pion ?\n");
							scanf("%s", saisie);
							x = atoi(saisie);

							Message m;
							m.action = PLAYER_PUT_TOKEN;
							m.couleur = couleur;
							m.x = x;
							m.salon = choix-1;

							write(sd, toString(&m), TAILLE_MAX * sizeof(char));
							//printf("Envoi de l'ordre %s\n au serveur", toString(&m));
							//Waiting for a response
							Message *ret = get_signal(sd);
						 	if (ret->action == TOKEN_ERROR) {
								printf("Erreur de token\n");
							}
							else
							{
								placerJeton(x, signal->couleur, grille);
								waiting = 1;
								fail = 0;
								afficherGrille(grille);
							}
						}
					}
				break;

				//Un joueur pose un jeton
				case PLAYER_PUT_TOKEN:
					placerJeton(signal->x, signal->couleur, grille);
					afficherGrille(grille);
					if (signal->couleur == couleur) {
						waiting = 1;
					} else {
						waiting = 0;
					}
				break;

				default:
					printf("Action reçue : %d\n", signal->action);
				break;
			}
		}
		free(signal);
		sleep(1);
	}

	se_deconnecter(sd);
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

	

