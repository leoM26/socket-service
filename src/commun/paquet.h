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
    bool game;
}Start_round_data;

typedef struct {
    int choice;
    double time;
}Choice_data;

typedef struct {

}End_round_data;

typedef struct {
    bool winner;
    int round;
}End_game_data;




enum code_protocol {
    CONNEXION=0,//connexion ON
    REP_CONNEXION=1,//envoie attente oui ou non
    START_GAME=2,//envoie le début du jeu
    START_ROUND=3,//envoie qui commence
    CHOICE=4,//envoie choix, temps de réaction
    END_ROUND=5,//envoie la fin du jeu
    END_GAME=6,//envoie gagnant
    STOP_CONNEXION=7//connexion OFF
};


void send_packet(enum code_protocol code, int client_id, void *data, int sockfd);
#endif