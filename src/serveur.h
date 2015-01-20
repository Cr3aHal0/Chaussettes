#include "salon.h"
#include <netinet/in.h>

typedef struct {
    Salon_t* salons;
    struct in_addr *addr;
    int nb_clients;
} Server;

void chargerSalons(Server*);
void freeSalons(Server*);
int rejoindreSalon(Server*, struct in_addr, int);
