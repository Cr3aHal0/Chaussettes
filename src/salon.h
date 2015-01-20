#include "grille.h"
#include <stdio.h>

/* Un salon contient une grille, et 2 joueurs */

#define TAILLE_LIGNE 7
#define TAILLE_COLONNE 6

typedef struct
{
	int liste_joueur[2]; 
    Couleur joueur_courant;
	Couleur grille[TAILLE_LIGNE][TAILLE_COLONNE];
	int nb_joueurs;
} Salon_t;


Couleur ajouter_joueur(Salon_t * salon, int joueur);
void afficher_infos_salon(Salon_t salon);
void raz_salon(Salon_t* salon);
