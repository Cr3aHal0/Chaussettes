#include <stdlib.h>
#include <stdio.h>


#include "grille.h"




void afficherGrille(int matrice[TAILLE_LIGNE][TAILLE_COLONNE])
{
	int i, j;
	for (i = 0; i < TAILLE_COLONNE; i++)
	{
		//printf(" |");
		for (j = 0; j < TAILLE_LIGNE; j++)
		{	
			printf("|¯");
			printf("%d", matrice[j][i]);
			printf("¯");
		}
		printf("|\n");
		
	}
	for(i = 0; i < TAILLE_LIGNE; i++) printf(" ¯¯¯");
	printf("\n");
	
}


/* Le joueur ne peut placer son jeton qu'uniquement sur les colonnes, le jeton va descendre si il reste de la place*/
int placerJeton(int position, int couleur, int matrice[TAILLE_LIGNE][TAILLE_COLONNE])
{
	if (position < 0 || position > TAILLE_COLONNE)
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

int is_full(int matrice[TAILLE_LIGNE][TAILLE_COLONNE], int x)
{
	return (matrice[x][0] != 0);
}




int is_win(int grille[TAILLE_LIGNE][TAILLE_COLONNE])
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



/*int main()
{
    int i, j, k;

	int grille[TAILLE_LIGNE][TAILLE_COLONNE] = {0};

	afficherGrille(grille);
	int res = placerJeton(0, ROUGE, grille);
	res = placerJeton(0, ROUGE, grille);
	res = placerJeton(0, ROUGE, grille);
	res = placerJeton(0, ROUGE, grille);
	
	res = placerJeton(0, ROUGE, grille);
	res = placerJeton(0, ROUGE, grille);

	res = placerJeton(1, ROUGE, grille);
	res = placerJeton(2, ROUGE, grille);
	res = placerJeton(3, ROUGE, grille);


	afficherGrille(grille);

	int win = is_win(grille);
	if (win > 0) printf("GAGNE\n");
	
	
	
	
	
	
}
*/

