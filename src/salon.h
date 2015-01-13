#include "grille.h"

/* Un salon contient une grille, et 2 joueurs */

typedef struct
{
	int liste_joueur[2] = {0}; 
	int grille[TAILLE_LIGNE][TAILLE_COLONNE] = {0};
	
} Salon_t;
