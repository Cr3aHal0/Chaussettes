
#define TAILLE_LIGNE 7
#define TAILLE_COLONNE 6

typedef enum  Couleur {BLANC, ROUGE, JAUNE} Couleur;




void afficherGrille(Couleur matrice[TAILLE_LIGNE][TAILLE_COLONNE]);
int is_win(Couleur grille[TAILLE_LIGNE][TAILLE_COLONNE]);
int placerJeton(int position, Couleur couleur, Couleur matrice[TAILLE_LIGNE][TAILLE_COLONNE]);



