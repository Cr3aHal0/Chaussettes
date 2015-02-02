#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netdb.h>

#include "grille.h"
#include "message.h"

#define ERROR 0
#define SUCCESS 1
#define SERVER_PORT 1500
#define MAX_MSG 100

int se_connecter(char* adresse_ip);
void se_deconnecter(int sd);
void afficher_liste_salons(int sd);
Couleur rejoindre_salon(int sd, int num_salon);
void placer_jeton(int sd, int position_x);
void afficher_grille(int sd);
int partie_commencee(int sd, int choix);
int partie_terminee(int sd);

