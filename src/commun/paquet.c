#include "paquet.h"

void convert_data_to_json(enum code_protocol code, void *data){

    switch (code)
    {
    case CONNEXION:
        Connexion_data *results = (Connexion_data*)data;
        results->test;
        break;
    }
}

void send_packet(enum code_protocol code, int client_id, void *data, int sockfd){
    Paquet paquet;
    paquet.code_protocole = code;
    paquet.client_id = client_id;
    //paquet.json_data = data;
    write(sockfd, &paquet, sizeof(Paquet));
}


