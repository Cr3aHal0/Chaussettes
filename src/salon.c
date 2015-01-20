#include "salon.h"

/* Note :
 * Place des int aleatoires dans le tableau si il n'y a pas eu initialisation
 * */

Couleur ajouter_joueur(Salon_t * salon, int joueur)
{
	
	//Si le salon est plein, on refuse la connexion
	if (salon->liste_joueur[0] >= 0 && salon->liste_joueur[1] >= 0)
	{
		printf("Impossible de se connecter : Salon plein\n");
		return -1;
	}
	
	//Si le salon est vide, on attribue la couleur rouge au joueur
	if (salon->liste_joueur[0] < 0 && salon->liste_joueur[1] < 0) 
	{
		salon->liste_joueur[0] = joueur;
		printf("Couleur attribuée : ROUGE\n");
		return ROUGE;
	}
	//Sinon on lui attribue la couleur jaune
	else 
	{
		salon->liste_joueur[1] = joueur;
		printf("Couleur attribuée : JAUNE\n");
		return JAUNE;
	}
		
}


void afficher_infos_salon(Salon_t salon)
{
	printf("Joueur 1 %d\n", salon.liste_joueur[0]);
	printf("Joueur 2 %d\n", salon.liste_joueur[1]);
	//Pose probleme
	//afficherGrille(salon.grille);
	
}

void raz_salon(Salon_t* salon)
{
	salon->liste_joueur[0] = -1;
	salon->liste_joueur[1] = -1;
	//Pas content avec ça
	//salon.grille = {0};
	int i, j;
	
	for (i = 0; i < TAILLE_COLONNE; i++)
	{
		for (j = 0; j < TAILLE_LIGNE; j++)
		{	
			salon->grille[j][i] = BLANC;
		}
	}	
}

int is_tour(Salon_t salon, int id_joueur) {
    int pos = 0;
    while (pos < 2 && salon.liste_joueur[pos] != id_joueur) {
        pos++;
    }
    if (salon.liste_joueur[pos] != id_joueur) {
        return -1;
    }
    return (pos == salon.joueur_courant);
}

/* Pour tester la mise en place de salon (petit problèmes d'initialisation)*/
/*int main()
{

	Salon_t salon;
	raz_salon(&salon);
	afficher_infos_salon(salon);
	ajouter_joueur(&salon, 1);
	afficher_infos_salon(salon);
	ajouter_joueur(&salon, 2);
	afficher_infos_salon(salon);
	ajouter_joueur(&salon, 3);
	afficher_infos_salon(salon);
	raz_salon(&salon);
	afficher_infos_salon(salon);
	
}*/
