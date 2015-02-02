#include <stdlib.h>
#include <stdio.h>


#include "grille.h"




void afficherGrille(Couleur matrice[TAILLE_LIGNE][TAILLE_COLONNE])
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

void initGrille(Couleur matrice[TAILLE_LIGNE][TAILLE_COLONNE])
{
    int x, y;
    for (x = 0; x < TAILLE_LIGNE; x++) {
        for(y = 0; y < TAILLE_COLONNE; y++) {
        	matrice[x][y] = 0;
        }
    }
}

/*
char* matrix_to_buffer(Couleur matrice[TAILLE_LIGNE][TAILLE_COLONNE])
{
	int i, j;
	char* buffer = (char*)malloc((sizeof(char)*truc)+1);
	for (i = 0; i < colonne; i++)
	{
		//printf(" |");
		for (j = 0; j < ligne; j++)
		{	
			char buffer_i_j[1];
			strcat(buffer, "|¯");
			sprintf(buffer_i_j, "%d", matrice[j][i]);
			strcat(buffer, buffer_i_j);
			strcat(buffer, "¯");
		}
		strcat(buffer, "|\n");
		
	}
	for(i = 0; i < ligne; i++) strcat(buffer, " ¯¯¯");
	strcat(buffer, "\n");
	
	return buffer;
	
}*/




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

