
#define TAILLE_LIGNE 7
#define TAILLE_COLONNE 6

enum couleurs {BLANC = 0, ROUGE = 1, JAUNE = 2};




void afficherGrille(int matrice[TAILLE_LIGNE][TAILLE_COLONNE]);
int is_win(int grille[TAILLE_LIGNE][TAILLE_COLONNE]);
int placerJeton(int position, int couleur, int matrice[TAILLE_LIGNE][TAILLE_COLONNE]);



