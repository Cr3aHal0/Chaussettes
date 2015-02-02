#define TAILLE_MAX 1000

typedef struct
{
    int length;
    int action;
	int salon;
	int joueur;
    int x;
} Message;

typedef enum  Action {
	PLAYER_TURN = 0,
	PLAYER_PUT_TOKEN = 1,
	PLAYER_WIN = 2
} Action;

char* toString(Message*);
Message* fromString(char*);

