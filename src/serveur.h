#include "salon.h"

typedef struct {
    Salon_t* salons;
} Server;

void chargerSalons(Server*);
void freeSalons(Server*);
