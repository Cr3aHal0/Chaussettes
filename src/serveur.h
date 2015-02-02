#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "salon.h"


typedef struct {
    Salon_t* *salons;
    struct in_addr *addr;
    int nb_clients;
} Server;

typedef struct
{
	int sd;
	struct sockaddr_in addr;
	Server server;
} Client;

void chargerSalons(Server*);
void freeSalons(Server*);
int rejoindreSalon(Server*, Client *client, int);
int aJoueur(Server server, struct in_addr client);
int ajouter_client(Server *server, struct in_addr client) ;
void *connection_handler(void *client);
void *gestion_salon(void *salon);
void *gestion_joueur(void *sd);
