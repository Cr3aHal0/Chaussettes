/**
 * Note : 
 * 	Le serveur possède plusieurs salons (10)
 * 	Quand un joueur joue sur une grille, il joue sur la grille du salon, et pas directement depuis le serveur.
 * 
 **/


#include "serveur.h"
#include "message.h"

#define LOCALHOST "127.0.0.1"
#define NB_SALONS 4

#define SUCCESS 0
#define ERROR 1
#define SERVER_PORT 1500

int main(int argc,char *argv[])
{
    pthread_t monThreadCompteur;
    Server server;
    chargerSalons(&server);

	int position;
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

    while (1)
    {
        printf("%s : waiting for data on port TCP %u \n",argv[0],SERVER_PORT);
        cliLen = sizeof(cliAddr);

		//Acceptation de la connexion
		
		newSd = accept(sd,(struct sockaddr *) &cliAddr,&cliLen);
		
		if(newSd<0)
		{
		    perror("Cannot accept connection");
		    exit(ERROR);
		}
  
		//Rejoindre un salon
		int num = 0;
		read(newSd, &num, sizeof(int));
		printf("Numero de salon : %d\n", num);
        int couleur_joueur = rejoindreSalon(&server, cliAddr.sin_addr, num);
        //Envoi de la couleur au joueur
        write(newSd, &couleur_joueur, sizeof(int));        
		
		//Tant que la partie n'est pas finie
		//Je mets 10 pour pouvoir tester en dur
		int i;
		while (is_win(server.salons[num].grille) == 0)
		{
			//On reçoit la position du jeton du joueur
			read(newSd, &position, sizeof(int));
			//Le joueur place un jeton
			placerJeton(position, couleur_joueur, server.salons[num].grille);
			afficherGrille(server.salons[num].grille);
		}
		printf("Le joueur %d a gagné!\n", is_win(server.salons[num].grille));
		//Il faudrait kick les joueurs du salon quand on remet a 0 celui ci

    }

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


void chargerSalons(Server *server) {
    server->salons = malloc(NB_SALONS * sizeof(Salon_t));
    int i;
    for(i = 0; i < NB_SALONS; i++) {
        Salon_t salon;
        salon.nb_joueurs = 0;     
        salon.joueur_courant = -1;
        salon.liste_joueur[0] = -1;
        salon.liste_joueur[1] = -1;
		
        int x, y;
        for (x = 0; x < TAILLE_LIGNE; x++) {
            for(y = 0; y < TAILLE_COLONNE; y++) {
                salon.grille[x][y] = 0;
            }
        }

        server->salons[i] = salon; 
        printf("Salon %d créé\n", i+1);
    }

    server->addr = (struct in_addr *) malloc (NB_SALONS * 2 * sizeof(struct in_addr));
    if (server->addr == NULL) {
			printf("Holy shit");
	}

    server->nb_clients = 0;
}

void freeSalons(Server *server) {
    free(server->salons);
}

int rejoindreSalon(Server *server, struct in_addr client, int num) {
    if (num < 1 || num > NB_SALONS) {
        return 0;
    }
    Salon_t salon = server->salons[num-1];

    /*if (aJoueur(server, client) >= 0) {
        return 0;
    }*/
    int idJoueur = ajouter_client(server, client);
    printf("Joueur ajouté au salon %d : %s \n", num, inet_ntoa(client));
        
    int retour = ajouter_joueur(&salon, idJoueur); 
    if (retour < 0) {
        return 0;
    }

    return retour;
}

int aJoueur(Server server, struct in_addr client) {
    int i = 0;
    while (i < server.nb_clients && client.s_addr != server.addr[i].s_addr) {
        i++;
    }
    return (client.s_addr == server.addr[i].s_addr) ? i : -1;
}

int ajouter_client(Server *server, struct in_addr client) {
	//printf("Nombre de clients avant opération : %d \n", server->nb_clients);
    server->addr[server->nb_clients++] = client;
    //printf("Nombre de clients après opération : %d \n", server->nb_clients);
    return server->nb_clients-1;
}


//Fonction permettant de kill le processus, ou fermer le port (a voir) lorsqu'on ferme le serveur (CTRL+C)
void handler_arret(int sig_num)
{
	
}

