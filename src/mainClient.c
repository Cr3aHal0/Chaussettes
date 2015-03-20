#include <stdio.h>
#include <stdlib.h>
#include "client.h"
#include <signal.h>
#include <pthread.h>

int sd;

/**
 *	Trying to handle the Ctrl+C signal to inform the server that we're disconnecting
 */
void handler_arret(int signum)
{
	printf("Préparation d'un signal pour déconnexion\n...");
	Message signal;
	signal.action = DISCONNECTING;

	write(sd, toString(&signal), TAILLE_MAX * sizeof(char));	
	printf("Message envoyé /!\\\n");
	se_deconnecter(sd);
	exit(1);
}	

void *heartbeat_handling(void *datas)
{
	while(1) {
		//printf("Connexion au serveur en cours...\n");
		sleep(4);
	}
}

/**
 * main()
 */
int main()
{

	printf("********** Bienvenue sur le client Puissance4 TCP **********\n");
	printf("Veuillez entrer votre serveur de connexion : ");
	char adresse_ip[16];
	scanf("%s", adresse_ip);
	printf("Tentative de connexion au serveur %s en cours...\n\n\n\n", adresse_ip);
	sd = se_connecter(adresse_ip);
	//Pour clear le terminal LINUX
	system("clear");
	
	afficher_liste_salons(sd);
	//int nb_salons = get_nb_salon();
	
	//While we're not leaving the program, ask for a lobby and check if it's not full
	int choix = -1;
	Couleur couleur = -1;

	while (couleur == -1) {
		choix = -1;
		while (choix < 0 || choix > 4) {
	    	printf("Veuillez choisir un numéro de salon ou tapez 0 pour quitter\n");
	    	scanf("%d", &choix);

			if (choix < 0 || choix > 4) {
				printf("Erreur : vous devez choisir un salon entre 1 et 4 ou Quitter (0) \n");
			}
		}

		if (choix == 0) {
			se_deconnecter(sd);
			exit(1);
		}

		couleur = rejoindre_salon(sd, choix);
		if (couleur == -1) {
			printf("\n[Erreur] Salon %d plein !\n", choix);
		}
	}

	//Notice that we want to handle the Ctrl+C keystroke
	signal(SIGINT, handler_arret);

	if (couleur == ROUGE) {
		int commencee = 0;
		printf("En attente d'un autre joueur...\n");
		while (commencee == 0) {
			commencee = partie_commencee(sd);
		}
		printf("Un deuxième joueur à rejoint la salle !\n");
	}
	else {
		//If we're the 2nd player, just wait for the game to start
		int commencee = 0;
		while (commencee == 0) {
			commencee = partie_commencee(sd);
		}
		printf("La partie est sur le point de commencer !\n");
	}

	pthread_t thread;
	if(pthread_create(&thread , NULL , heartbeat_handling , (void*) NULL) < 0)
	{
		printf("Erreur : impossible d'initialiser le module de surveillance de l'état de la connexion...\n");
		se_deconnecter(sd);
		return 1;
	}

	//Initialize a local grid
	Couleur grille[TAILLE_LIGNE][TAILLE_COLONNE];

	//Début de partie
	printf("La partie commence !!!\n");
	initGrille(grille);
	afficherGrille(grille);

	int end = 0;
	int x;
	int waiting = 1;
	char *saisie = malloc(sizeof(saisie));

	//While it's not over
	while (end == 0) {
		printf("Partie en cours...\n");
		printf("En attente du tour du joueur adverse ...\n");

		//Keep looking for a signal
		Message *signal = malloc(sizeof(*signal));
		signal = get_signal(sd);

		if (signal != NULL) {
			//Define several behaviors according to the signal type
			switch(signal->action) {

				//Did someone win ?
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

				//The server is telling who should play now
				case PLAYER_TURN:
					if (signal->couleur == couleur) {
						printf("\n------\n A votre tour de jouer ! \n------\n");
						waiting = 0;
					}
					//If it's our turn
					if (waiting == 0) {
						int fail = 1;
						//Keep asking for a column while there is an error
						while (fail == 1 ) {
							printf("Dans quelle colonne souhaitez-vous  ajouter un pion ?\n");
							scanf("%s", saisie);
							x = atoi(saisie);

							Message m;
							m.action = PLAYER_PUT_TOKEN;
							m.couleur = couleur;
							m.x = x;
							m.salon = choix-1;

							write(sd, &m, sizeof(Message));
							
							//Waiting for a response
							Message *ret = get_signal(sd);
							//If there is an error, notice the player and go back
						 	if (ret->action == TOKEN_ERROR) {
								printf("Erreur de token\n");
							}
							else
							{
								//put the token in the selected column
								placerJeton(x, signal->couleur, grille);
								waiting = 1;
								fail = 0;
								afficherGrille(grille);
							}
						}
					}
				break;

				//Someone put a token
				case PLAYER_PUT_TOKEN:
					placerJeton(signal->x, signal->couleur, grille);
					afficherGrille(grille);
					//If we just put a token, wait for the other play turn
					if (signal->couleur == couleur) {
						waiting = 1;
					} else {
						waiting = 0;
					}
				break;

				//Trying to handle violent disconnection
				case DISCONNECTING:
					printf("Le joueur adverse a quitté la partie. Déconnexion...\n");
					end = 1;
				break;
				// <<

				//???
				default:
					printf("Action reçue : %d\n", signal->action);
				break;
			}
		}
		free(signal);
		sleep(1);
	}

	se_deconnecter(sd);
	
	return 0;
}

	

