#include "grille.h"
#include <stdio.h>

/* Un salon contient une grille, et 2 joueurs */

typedef struct
{
	int liste_joueur[2]; 
	int grille[TAILLE_LIGNE][TAILLE_COLONNE];
	
} Salon_t;


int ajouter_joueur(Salon_t * salon, int joueur);
void afficher_infos_salon(Salon_t salon);
void raz_salon(Salon_t* salon);
