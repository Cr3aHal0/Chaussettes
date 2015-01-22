typedef struct
{
    int length;
    int action;
	int salon;
	int joueur;
    int x;
} Message;

char* toString(Message*);
Message* fromString(char*);

