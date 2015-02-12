#include "message.h"
#include <regex.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char* toString(Message *message) {
    char* buff = (char *) malloc(TAILLE_MAX * sizeof(char));
    char* truc = (char *) malloc(2 * sizeof(char));
    
    strcat(buff, "{");
    if (message->action != -1) {
        strcat(buff, "action=");
        sprintf(truc, "%d", message->action);
        strcat(buff, truc);
        strcat(buff, ";");
    }
    if (message->salon != -1) {
        strcat(buff, "salon=");
        sprintf(truc, "%d", message->salon);
        strcat(buff, truc);
        strcat(buff, ";");
    }
    if (message->couleur != -1) {
        strcat(buff, "couleur=");
        sprintf(truc, "%d", message->couleur);
        strcat(buff, truc);
        strcat(buff, ";");
    }
    if (message->x != -1) {
        strcat(buff, "x=");
        sprintf(truc, "%d", message->x);
        strcat(buff, truc);
        strcat(buff, ";");
    }
    strcat(buff, "}");
    free(truc);

    return buff;
}

char* reserver() {
	char* buffer = (char*) malloc(TAILLE_MAX * sizeof(char));
	return buffer;
}

Message* fromString(char* message) {
    Message *mes = malloc(sizeof(*mes));
    mes->action = -1;
    mes->couleur = -1;
    mes->x = -1;
    mes->salon = -1;

    char* truc = (char *) malloc(20 * sizeof(char));
    char* valeurs = (char *) malloc(2 * sizeof(char));

    regex_t regex;
    int reti;

    //reti = regcomp(&regex, "^[{]([[:alpha:]][=][[:digit:]]([&]{0,1})){1,5}[}]$", 0);
    reti = regcomp(&regex, "([[:alpha:]]+)[=]([[:digit:]]+);?", REG_EXTENDED|REG_NEWLINE);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
    }

    reti = regexec(&regex, message, 0, NULL, 0);
    if (!reti) {
        //printf("Found !");

        /* "P" is a pointer into the string which points to the end of the
           previous match. */
        const char * p = message;
        /* "N_matches" is the maximum number of matches allowed. */
        const int n_matches = 10;
        /* "M" contains the matches found. */
        regmatch_t m[n_matches];

        while (1) {
            int i = 0;
            int nomatch = regexec (&regex, p, n_matches, m, 0);
            if (nomatch) {
                //printf ("No more matches.\n");
                break;
            }
            for (i = 0; i < n_matches; i++) {
                int start;
                int finish;
                if (m[i].rm_so == -1) {
                    break;
                }
                start = m[i].rm_so + (p - message);
                finish = m[i].rm_eo + (p - message);
                if (i == 1) {
                    sprintf (truc, "%.*s", (finish - start), message + start);

                    start = m[2].rm_so + (p - message);
                    finish = m[2].rm_eo + (p - message);
                    strcpy(valeurs, "");
                    sprintf (valeurs, "%.*s", (finish - start), message + start);

                    if (!strcmp(truc, "action")) {
                        mes->action = atoi(valeurs);
                    }
                    if (!strcmp(truc, "salon")) {
                        mes->salon = atoi(valeurs);
                    }
                    else if (!strcmp(truc, "couleur")) {
                        mes->couleur = atoi(valeurs);
                    }
                    else if (!strcmp(truc, "x")) {
                        mes->x = atoi(valeurs);
                    }
                }
                //printf ("'%.*s'\n", (finish - start), message + start);
            }
            p += m[0].rm_eo;
        }
        //printf("salon : %d & joueur : %d & action = %d & x = %d", mes->salon, mes->joueur, mes->action, mes->x);

    }
    else if (reti == REG_NOMATCH) {
        printf("Error : No pattern found for the message : <<%s>> \n", message);
    }
    
    return mes;
}
