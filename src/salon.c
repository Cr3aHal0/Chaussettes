#include "salon.h"
#include "grille.h"


int ajouter_joueur(Salon_t salon, int joueur)
{
	
	//Si le salon est plein, on refuse la connexion
	if (salon.liste_joueur[0] != 0 && salon.liste_joueur[1] != 0) return -1;
	
	//Si le salon est vide, on attribue la couleur rouge au joueur
	if (salon.liste_joueur[0] == 0 && salon.liste_joueur[1] == 0) 
	{
		salon.liste_joueur[0] = joueur;
		return ROUGE;
	}
	//Sinon on lui attribue la couleur jaune
	else 
	{
		salon.liste_joueur[1] = joueur;
		return JAUNE;
	}
		
}


void afficher_infos_salon(Salon_t salon)
{
	printf("Joueur 1 %d", salon.liste_joueur[0]);
	printf("Joueur 2 %d", salon.liste_joueur[1]);
	afficherGrille(salon.grille);
}

//Mise a zero du salon lorsque qu'une partie est finie (pour permettre de creer d'autres parties)
int void raz_salon(Salon_t salon)
{
	salon.liste_joueur[0] = 0;
	salon.liste_joueur[1] = 0;
	salon.grille[TAILLE_LIGNE][TAILLE_COLONNE = {0};
	
}


