#define TAILLE_MAX 1000

typedef struct
{
    int length;
    int action;
	int salon;
	int couleur;
    int x;
} Message;

typedef enum  Action {
	GAME_START = 0,
	PLAYER_TURN = 1,
	PLAYER_PUT_TOKEN = 2,
	PLAYER_WIN = 3
} Action;

char* toString(Message*);
Message* fromString(char*);

