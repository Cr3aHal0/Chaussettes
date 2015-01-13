#include "grille.h"

/* Un salon contient une grille, et 2 joueurs */

typedef struct
{
	int liste_joueur[2]; 
	int grille[TAILLE_LIGNE][TAILLE_COLONNE];
	
} Salon_t;
