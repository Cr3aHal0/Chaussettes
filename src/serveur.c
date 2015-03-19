#include "serveur.h"

#define LOCALHOST "127.0.0.1"
#define NB_SALONS 4

#define SUCCESS 0
#define ERROR 1
#define SERVER_PORT 1500

int main(int argc,char *argv[])
{
    pthread_t thread;
    Server server;
    
    chargerSalons(&server);

    int sd,newSd;
    socklen_t cliLen;

    struct sockaddr_in cliAddr, servAddr;

    /* TEST PURPOSE :
    
    Message m;
    m.action = 1;
    m.salon = 2;
    m.joueur = 0;
    m.x = 5;

    char* mes = toString(&m);
    printf("message : %s \n", mes);
    
    Message *message = fromString(mes);
    */

    //Creation de la socket
    sd = socket(AF_INET,SOCK_STREAM,0);
    if(sd<0)
    {
        perror("Cannot open socket");
        exit(ERROR);
    }

    //Initialisation des champs de la structure servAddr
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons (SERVER_PORT);

    //Bind
    if(bind(sd,(struct sockaddr *) &servAddr, sizeof(servAddr))<0)
    {
        perror("Cannot bind port");
        exit(ERROR);
    }

    //Listen
    listen(sd,5);
	printf("%s : waiting for data on port TCP %u \n",argv[0],SERVER_PORT);
    //Acceptation de la connexion
    cliLen = sizeof(cliAddr);
    while (newSd = accept(sd,(struct sockaddr *) &cliAddr, &cliLen))
    {
		printf("Acceptation d'un nouveau client \n");
		if(newSd<0)
		{
		    perror("Cannot accept connection");
		    exit(ERROR);
		}
		
		Client *client = malloc(sizeof(Client));
		client->sd = newSd;
		client->addr = cliAddr;
		client->server = server;
		
		if(pthread_create(&thread , NULL , connection_handler , (void*) client) < 0)
		{
			perror("could not create thread");
			return 1;
		}
		else
		{
			printf("Thread créé avec succès \n");
		}
		printf("Fin du lancement du thread %d \n", client->sd);
    }

	printf("Fin du while\n");
    freeSalons(&server);

    return(SUCCESS);
}

int get_nb_salon()
{
	return NB_SALONS;
}

//Retourne un buffer contenant la liste des salons et leur infos
char* afficher_liste_salons()
{
	return NULL;
	
}

/**
 *	Handler dedicated to listen for new client then trying to add them in the player base
 */
void *connection_handler(void *client)
{
	Client *connection = (Client*)client;

	//while (1) {
		//Rejoindre un salon
		int num = 0;
		Message *mes = get_signal(connection->sd);
		if (mes->action == CHOOSE_LOBBY) {
			num = mes->salon;
			printf("Numero de salon : %d\n", num);

			//Try to retrieve a slot for the new player
			mes->couleur = rejoindreSalon(&connection->server, connection, num);
			envoyerMessageJoueur(connection->sd, mes);

			//If mes->couleur >= 0 then he has been added to the player base.
			if (mes->couleur >= 0) {
				printf("Couleur %d\n", mes->couleur);
				printf("Canal rejoint : %d\n", connection->sd);
			}
		}
		free(mes);
	//}
	
	 //Send some messages to the client
	//message = "Greetings! I am your connection handler\n";
	//write(sock , message , strlen(message)); 
		
	return NULL;
}	


/**
 *	Thread function dedicated to each life of lobbys
 */
void *gestion_salon(void *salon) {
	Salon_t *lobby = (Salon_t*)salon;
	printf("nombre de joueurs dans le salon : %d \n", lobby->nb_joueurs);
	printf("En attente de joueurs\n");
	
	//While the thread is alive
	while(1) {
		
		//While the lobby isn't complete
		while (lobby->nb_joueurs < 2) {
			//printf("[%d] Waiting for %d people to join ... \n", lobby->id, (2-lobby->nb_joueurs));
			Message *mes1 = malloc(sizeof(*mes1));
			mes1->action = WAITING_PLAYER;
			diffuserMessage(lobby, mes1);
			sleep(1);
		}
		
		//Tell the players we're ready to go
		Message *mes = malloc(sizeof(*mes));
		mes->action = GAME_START;
		diffuserMessage(lobby, mes);

		sleep(1);

		//Send a message to tell players than the first one can play
		Message *m = malloc(sizeof(*m));
		m->salon = -1;
		m->x = -1;
		m->action = PLAYER_TURN;
		m->couleur = ROUGE;

		diffuserMessage(lobby, m);

		lobby->joueur_courant = m->couleur;

		int winner;

		while ((winner = is_win(lobby->grille)) == 0 && (lobby->nb_joueurs == 2)) {
			//printf("[%d] Partie toujours en cours\n", lobby->id);
				
			sleep(1);
		}
		
		//If we're out and there is still 2 players, then the game is over
		if (lobby->nb_joueurs == 2) {
			printf("Le joueur %d a gagné!\n", winner);
			m->action = PLAYER_WIN;
			m->couleur = winner;
			diffuserMessage(lobby, m);
		}

		//renew salon
		reinitSalon(lobby);

		//Déconnecter client : close les sockets
	}
	
	return NULL;
}

/**
 * Reinitialize a lobby :
 * - empty the array containing players
 * - empty the array containing the socket identifiers
 * - close each thread allocated to players
 */
void reinitSalon(Salon_t *salon) {

	//Free the sockets allocated
	int i;
	for (i = 0; i < salon->nb_sockets; i++) {
		close(salon->sockets_id[i]);
	}
	printf("Fermeture des sockets du salon %d\n", salon->id);

	salon->nb_joueurs = 0;     
    salon->joueur_courant = -1;
    salon->liste_joueur[0] = -1;
    salon->liste_joueur[1] = -1;
	salon->sockets_id[0] = 0;
	salon->sockets_id[1] = 0;
	salon->nb_sockets = 0;

	//Close threads
	for (i = 0; i < salon->nb_threads; i++) {
		pthread_join (*salon->threads_joueurs[i], NULL);
	}
	free(salon->threads_joueurs);

	printf("Fermeture des threads du salon %d\n", salon->id);

	salon->nb_threads = 0;

	//Close threads_joueurs
	salon->threads_joueurs = malloc(2*sizeof(pthread_t));
	printf("Réallocation d'espace pour les threads du salon %d\n", salon->id);

	//Erase the grid
    int x, y;
    for (x = 0; x < TAILLE_LIGNE; x++) {
        for(y = 0; y < TAILLE_COLONNE; y++) {
            salon->grille[x][y] = 0;
        }
    }
	printf("Remise à zéro de la grille du salon %d\n", salon->id);

	//Yay, success !
	printf("Salon %d réinitialisé avec succès \n", salon->id);
}

/**
 * Initialize a lobby :
 * - initialize the grid
 * - create a thread for handlind basic thread requests
 */
void chargerSalons(Server *server) {
    server->salons = malloc(NB_SALONS * sizeof(Salon_t));
    int i;
    for(i = 0; i < NB_SALONS; i++) {
        Salon_t *salon = malloc(sizeof(*salon));
        salon->id = i;
        salon->nb_joueurs = 0;     
        salon->joueur_courant = -1;
        salon->liste_joueur[0] = -1;
        salon->liste_joueur[1] = -1;
		salon->sockets_id[0] = 0;
		salon->sockets_id[1] = 0;
		salon->nb_sockets = 0;
		salon->nb_threads = 0;
		salon->threads_joueurs = malloc(2*sizeof(pthread_t));
		
        int x, y;
        for (x = 0; x < TAILLE_LIGNE; x++) {
            for(y = 0; y < TAILLE_COLONNE; y++) {
                salon->grille[x][y] = 0;
            }
        }

		pthread_t threadsalon;
		if(pthread_create(&threadsalon , NULL , gestion_salon , (void*) salon) < 0)
		{
			printf("[ERROR] Could not create thread for lobby #%d", i);
		}
		
		salon->thread_salon = threadsalon;
		
        server->salons[i] = salon; 
        printf("Salon %d créé\n", i+1);
    }

    server->addr = (struct in_addr *) malloc (NB_SALONS * 2 * sizeof(struct in_addr));
    if (server->addr == NULL) {
			printf("Holy shit");
	}

    server->nb_clients = 0;
}

/**
 *	Wait for lobby threads to be finished
 */
void freeSalons(Server *server) {
	int i;
	for (i=0; i<NB_SALONS; i++) {
		pthread_join(server->salons[i]->thread_salon, 0);
	}
    free(server->salons);
}

/**
 *	Try to join a lobby
 */
int rejoindreSalon(Server *server, Client *client, int num) {
    if (num < 1 || num > NB_SALONS) {
        return 0;
    }
    Salon_t *salon = server->salons[num-1];

    /*if (aJoueur(server, client) >= 0) {
        return 0;
    }*/
    int idJoueur = ajouter_client(server, client->addr.sin_addr);
    printf("Joueur ajouté au salon %d par le slot %d : %s \n", num, client->sd, inet_ntoa(client->addr.sin_addr));
        
    int retour = ajouter_joueur(salon, client->sd, idJoueur); 
    if (retour < 0) {
		printf("Impossible d'ajouter le joueur au salon\n");
        return -1;
    }	

	pthread_t thread;
	Joueur_t *joueur = malloc(sizeof(*joueur));;
	joueur->slot = client->sd;
	joueur->salon = salon;

	//printf("Slot à réserver : %d\n", client->sd);
	if(pthread_create(&thread , NULL , gestion_joueur , (void*) joueur) < 0)
	{
		printf("[ERROR] Could not create thread for client on slot #%d \n", client->sd);
	}
	salon->threads_joueurs[salon->nb_threads++] = &thread;

    return retour;
}

/**
 * Thread inside each lobby who is dedicated to handle requests coming from one player
 */
void *gestion_joueur(void *data) {
	Joueur_t *joueur = (Joueur_t*)data;
	printf("Slot occupé : %d\n", joueur->slot);

	//char* buffer = reserver();
	//int start = 1;

	//Tant que le thread est en vie et que le socket l'est aussi
	int error = 0;
	socklen_t len = sizeof (error);
	int retval;
	int ended = 0;
	int winner = 0;

	//While there isn't any winner, while the game has not been "forced-ended" and while the socket is alive
	while(((retval = getsockopt (joueur->slot, SOL_SOCKET, SO_ERROR, &error, &len )) == 0)
			&& (ended == 0) && (winner == 0)) {

			printf("Etat de la socket : %d\n", retval);
			/*while (start == 1)*/ {
			//read(joueur->slot, buffer, TAILLE_MAX * sizeof(char));
			//printf("Message reçu : %s \n", buffer);
			int retour;

			Message *message = get_signal(joueur->slot);
			printf("Message reçu pour le salon %d depuis %d\n", joueur->salon->id, message->salon);

			//Check if the lobby targeted is the player's one.
			if (message->salon == joueur->salon->id) {
				printf("Message reçu pour le salon %d\n", joueur->salon->id);
				//Switch on actions
				switch (message->action) {
					
					//If the player puts a token in the grid
					case PLAYER_PUT_TOKEN:
						if (message->couleur == joueur->salon->joueur_courant) {
							retour = placerJeton(message->x, message->couleur, joueur->salon->grille);
							Message m;
							if (retour == 1) {
								//Okay dude

								m.action = PLAYER_PUT_TOKEN;
								m.x = message->x;
								m.couleur = message->couleur;

								diffuserMessage(joueur->salon, &m);

								if ((winner = is_win(joueur->salon->grille)) == 0) {
									m.x = -1;
									m.action = PLAYER_TURN;
									m.couleur = (message->couleur == ROUGE) ? JAUNE : ROUGE;

									diffuserMessage(joueur->salon, &m);

									joueur->salon->joueur_courant = m.couleur;
								}
								afficherGrille(joueur->salon->grille);
							}
							else
							{
								m.action = TOKEN_ERROR;
								envoyerMessageJoueur(joueur->slot,&m);
							}
						}
					break;

					// >> Trying to handle violent player disconnecting
					case DISCONNECTING:
						printf("/!\\ Player trying to disconnect\n");
						diffuserMessage(joueur->salon, message);
						close(joueur->slot);
						joueur->salon->nb_joueurs--;
						printf("Slot %d coupé\n", joueur->slot);	
						ended = 1;	
						printf("Fin de la partie");	
					break;
					// << 
				}
			}
			free(message);
		}

	}

	printf("Fin du thread de gestion du joueur du slot %d\n", joueur->slot);

	return NULL;
}

/**
 * Check if the current player with the current IP address is new or already registered
 * [UNUSED]
 */
int aJoueur(Server server, struct in_addr client) {
    int i = 0;
    while (i < server.nb_clients && client.s_addr != server.addr[i].s_addr) {
        i++;
    }
    return (client.s_addr == server.addr[i].s_addr) ? i : -1;
}

/**
 *	Add a client to the global server array of players
 */
int ajouter_client(Server *server, struct in_addr client) {
	//printf("Nombre de clients avant opération : %d \n", server->nb_clients);
    server->addr[server->nb_clients++] = client;
    //printf("Nombre de clients après opération : %d \n", server->nb_clients);
    return server->nb_clients-1;
}

/**
 *	Broadcast a message to an entire lobby
 */
void diffuserMessage(Salon_t *salon, Message *message) {
	int i;
	for (i = 0; i < salon->nb_sockets; i++) {
		//char *buffer = toString(message);
		//printf("Message notifié au socket %d : %s \n", salon->sockets_id[i], buffer);
		//write(salon->sockets_id[i], buffer, TAILLE_MAX * sizeof(char));
		printf("Message notifié au socket %d : %s \n", salon->sockets_id[i], toString(message));
		write(salon->sockets_id[i], message, sizeof(Message));
	}
}

/**
 *	Send a message to a specified player
 */
void envoyerMessageJoueur(int slot, Message *message) {
	//write(slot, toString(message), TAILLE_MAX * sizeof(char));
	write(slot, message, sizeof(Message));
}

/**
 * Retrieve the signal from a socket identifier
 */
Message* get_signal(int sd) {
	Message *message = malloc(sizeof(*message));
	recv(sd, message, sizeof(Message), MSG_WAITALL);
	//printf("Reçu : %s\n", toString(message));
	return message;
}

/**
 * Function dedicated to interact with Ctrl+C keystroke
 */
void handler_arret(int sig_num)
{
	
}

