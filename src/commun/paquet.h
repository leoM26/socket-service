#ifndef PAQUET_HEADER_FILE_H
#define PAQUET_HEADER_FILE_H

#include <stdbool.h>
typedef struct {
    int code_protocole;
    int client_id;
    char json_data[256];
}Paquet;

typedef struct {
    bool wait;
}Rep_connexion_data;

typedef struct {
    bool winner;
    int round;
}Start_round_data;

typedef struct {
    int choice;
    double time;
}Choice_data;


typedef struct {
    bool winner;
    int round;
}End_game_data;




enum code_protocol {
    CONNEXION=0,//connexion ON
    REP_CONNEXION=1,//envoie attente oui ou non
    START_GAME=2,//envoie le début du jeu
    START_ROUND=3,//envoie qui commence, envoie le gagnant à la fin du round précédent
    CHOICE=4,//envoie choix (1 pour collaborer et 2 pour trahir), temps de réaction
    END_GAME=5,//envoie gagnant
    STOP_CONNEXION=6//connexion OFF
};

void *parse_json(char *json, enum code_protocol code);

void send_packet(enum code_protocol code, int client_id, void *data, int sockfd);
#endif