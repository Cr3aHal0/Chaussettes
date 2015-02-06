#include "grille.h"
#include <stdio.h>
#include <pthread.h>

/* Un salon contient une grille, et 2 joueurs */

#define TAILLE_LIGNE 7
#define TAILLE_COLONNE 6

typedef enum Status_t {WAITING, INGAME} Status_t;

typedef struct
{
	int id;
	int liste_joueur[2]; 
	int sockets_id[2];
	int nb_sockets;
    Couleur joueur_courant;
	Couleur grille[TAILLE_LIGNE][TAILLE_COLONNE];
	int nb_joueurs;
	pthread_t thread_salon;
	pthread_t* *threads_joueurs;
	int nb_threads;
} Salon_t;

typedef struct 
{
	int slot;
	Salon_t *salon;
} Joueur_t;

Couleur ajouter_joueur(Salon_t * salon, int slot, int joueur);
void afficher_infos_salon(Salon_t salon);
void raz_salon(Salon_t* salon);
int is_win(Couleur grille[TAILLE_LIGNE][TAILLE_COLONNE]);
void notifierJoueurs(Salon_t *salon, int status);
