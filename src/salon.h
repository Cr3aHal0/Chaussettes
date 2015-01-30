#include "grille.h"
#include <stdio.h>
#include <pthread.h>

/* Un salon contient une grille, et 2 joueurs */

#define TAILLE_LIGNE 7
#define TAILLE_COLONNE 6

typedef struct
{
	int id;
	int liste_joueur[2]; 
    Couleur joueur_courant;
	Couleur grille[TAILLE_LIGNE][TAILLE_COLONNE];
	int nb_joueurs;
	pthread_t thread_salon;
} Salon_t;

Couleur ajouter_joueur(Salon_t * salon, int joueur);
void afficher_infos_salon(Salon_t salon);
void raz_salon(Salon_t* salon);
int is_win(Couleur grille[TAILLE_LIGNE][TAILLE_COLONNE]);
int placerJeton(int position, Couleur couleur, Couleur matrice[TAILLE_LIGNE][TAILLE_COLONNE]);


