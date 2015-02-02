#include "salon.h"

/* Note :
 * Place des int aleatoires dans le tableau si il n'y a pas eu initialisation
 * */
 
 
 
 
 
/* Le joueur ne peut placer son jeton qu'uniquement sur les colonnes, le jeton va descendre si il reste de la place*/
int placerJeton(int position, Couleur couleur, Couleur matrice[TAILLE_LIGNE][TAILLE_COLONNE])
{
	if (position < 0 || position > TAILLE_COLONNE || isdigit(position))
	{
		
		printf("Erreur : Jeton en dehors du jeu\n");
		return -1; 
	}
	//Si la colonne est pleine
		
	else if (matrice[position][0] != BLANC)
	{
		printf("Erreur : Colonne pleine\n");
		return 0;
	}		
	else
	{		
		int i = TAILLE_COLONNE-1;
		while (matrice[position][i] != BLANC){
			i--;
		}
		printf("Jeton placé a l'emplacement %d, %d\n", position, i);
		matrice[position][i] = couleur;
		
		return 1;
	}

	
}

int is_full(Couleur matrice[TAILLE_LIGNE][TAILLE_COLONNE], int x)
{
	return (matrice[x][0] != BLANC);
}




int is_win(Couleur grille[TAILLE_LIGNE][TAILLE_COLONNE])
{
	int y = 0;
	int x = 0;
	int size = 1; 
	int color = 0;
	/*Verif par colonne*/
	while (x < TAILLE_LIGNE && size < 4)
	{
		//check each line
		y = 0;
		color = grille[x][y];
		while (y < TAILLE_COLONNE-1 && size < 4)
		{
			if ((grille[x][y] == grille[x][y+1]) && grille[x][y+1] != 0)
			{
				size++;
			}
			else
			{
				size = 1; 
				color = grille[x][y+1];
			}
			y++;
		}
		x++;
	} 	
	if (size == 4) return color;
	/*Verif par ligne*/	
	y = 0;
	size = 1;
	while (y < TAILLE_COLONNE && size < 4)
	{
		//check each line
		x = 0;
		color = grille[x][y];
		while (x < TAILLE_LIGNE-1 && size < 4)
		{
			if ((grille[x][y] == grille[x+1][y]) && grille[x+1][y] != 0)
			{
				size++;
			}
			else
			{
				size = 1; 
				color = grille[x+1][y];
			}
			x++;
		}
		y++;
	} 	

	if (size == 4) return color;
}


Couleur ajouter_joueur(Salon_t * salon, int socketslot, int joueur)
{
	
	//Si le salon est plein, on refuse la connexion
	if (salon->liste_joueur[0] >= 0 && salon->liste_joueur[1] >= 0)
	{
		printf("Impossible de se connecter : Salon plein\n");
		return -1;
	}
	
    salon->nb_joueurs++;
	salon->sockets_id[salon->nb_sockets] = socketslot;
	salon->nb_sockets++;
	
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

void notifierJoueurs(Salon_t *salon, int statut) {
	int i;
	for (i = 0; i < salon->nb_sockets; i++) {
		printf("Statut notifié : %d au socket %d \n", statut, salon->sockets_id[i]);
		write(salon->sockets_id[i], &statut, sizeof(int));
	} 
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
