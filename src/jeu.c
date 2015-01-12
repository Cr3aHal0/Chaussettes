#include "commun.h"
#include "jeu.h"

int grille[TAILLE_LIGNE][TAILLE_COLONNE] = {BLANC}; /* Toute les cases du jeu sont blanches au départ*/



void afficherGrille(int ligne, int colonne, int matrice[LIGNE][COLONNE])
{
	int i, j;
	for (i = 0; i < TAILLE_LIGNE; i++)
	{
		//printf(" |");
		for (j = 0; j < TAILLE_COLONNE; j++)
		{	
			printf("|¯");
			printf("%d", matrice[i][j]);
			printf("¯");
		}
		printf("|\n");
		
	}
	for(i = 0; i < TAILLE_COLONNE; i++) printf(" ¯¯¯");
	
}




int partieGagnee(int tab[TAILLE_LIGNE][TAILLE_COLONNE])
{
    int i, j;
    // ligne
    for (i=0 ; i<TAILLE_LIGNE ; i++)
    {
        for (j=0 ; j<TAILLE_COLONNE - 3 ; j++)
        {
            if (tab[i][j] == ROUGE &&
                tab[i][j+1] == ROUGE &&
                tab[i][j+2] == ROUGE &&
                tab[i][j+3] == ROUGE )
              return  ROUGE;
            if (tab[i][j] == JAUNE &&
                tab[i][j+1] == JAUNE &&
                tab[i][j+2] == JAUNE &&
                tab[i][j+3] == JAUNE)
              return  JAUNE;
        }
    }
    // colonne
    for (i=0 ; i<TAILLE_LIGNE - 3 ; i++)
    {
        for (j=0 ; j<TAILLE_COLONNE ; j++)
        {
            if (tab[i][j] == ROUGE &&
                tab[i+1][j] == ROUGE &&
                tab[i+2][j] == ROUGE &&
                tab[i+3][j] == ROUGE )
              return  ROUGE;
            if (tab[i][j] == JAUNE &&
                tab[i+1][j] == JAUNE &&
                tab[i+2][j] == JAUNE &&
                tab[i+3][j] == JAUNE)
              return  JAUNE;
        }
    }
    // diagonale ds un sens
    for (i=0 ; i<TAILLE_LIGNE - 3 ; i++)
    {
        for (j=0 ; j<TAILLE_COLONNE - 3 ; j++)
        {
            if (tab[i][j] == ROUGE &&
                tab[i+1][j+1] == ROUGE &&
                tab[i+2][j+2] == ROUGE &&
                tab[i+3][j+3] == ROUGE )
              return  ROUGE;
            if (tab[i][j] == JAUNE &&
                tab[i+1][j+1] == JAUNE &&
                tab[i+2][j+2] == JAUNE &&
                tab[i+3][j+3] == JAUNE)
              return  JAUNE;
        }
    }
    // diagonale ds l'autre sens
    for (i=TAILLE_LIGNE-1 ; i>2 ; i--)
    {
        for (j=0 ; j<TAILLE_COLONNE - 3 ; j++)
        {
            if (tab[i][j] == ROUGE &&
                tab[i-1][j+1] == ROUGE &&
                tab[i-2][j+2] == ROUGE &&
                tab[i-3][j+3] == ROUGE )
              return  ROUGE;
            if (tab[i][j] == JAUNE &&
                tab[i-1][j+1] == JAUNE &&
                tab[i-2][j+2] == JAUNE &&
                tab[i-3][j+3] == JAUNE)
              return  JAUNE;
        }
    }
    return BLANC;
}


/* Le joueur ne peut placer son jeton qu'uniquement sur les colonnes, le jeton va descendre si il reste de la place*/
int placerJeton(int position, int couleur, int matrice[TAILLE_LIGNE][TAILLE_COLONNE])
{
	if (position < 0 && position > TAILLE_LIGNE)
	{
		printf("Erreur : Jeton en dehors du jeu")
		return -1;
	}
	//Si la colonne est pleine
	else if (matrice[0][position] =! BLANC)
	{
		printf("Erreur : Colonne pleine");
		return 0;
	}		
	else
	{	
		//On place le jeton 
		for (i = 0; i < TAILLE_COLONNE; i++)
		{
			//Si dans le parcours de la colonne on trouve un emplacement vide (BLANC) on y place le pion
			if(matrice[i][position] == BLANC){
				matrice[i][position] == couleur;
			}
		};
		return 1;
	}

	


}
