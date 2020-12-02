#include <json-c/json.h>
#include <string.h>
#include "paquet.h"

char* convert_data_to_json(enum code_protocol code, void *data){

    json_object *object = json_object_new_object();


    switch (code)
    {
    case CONNEXION:{
        return NULL;
        break;
    }
    case REP_CONNEXION:{
        Rep_connexion_data *results = (Rep_connexion_data*)data;
        json_object_object_add(object,"wait",json_object_new_boolean(results->wait));
        break;
    }

    case START_ROUND:{
        Start_round_data *results = (Start_round_data*)data;
        json_object_object_add(object,"game",json_object_new_boolean(results->game));
        break;
    }
    case CHOICE:{
        Choice_data *results = (Choice_data*)data;
        json_object_object_add(object,"choice",json_object_new_int(results->choice));
        json_object_object_add(object,"time",json_object_new_double(results->time));
        break;
    }
    case END_ROUND:{
        End_round_data *results = (End_round_data*)data;
        break;
    }
    case END_GAME:{
        End_game_data *results = (End_game_data*)data;
        json_object_object_add(object,"winner",json_object_new_boolean(results->winner));
        break;
    }
    case STOP_CONNEXION:{
        return NULL;
        break;
    }
    }
    return json_object_get_string(object);
}


void *parse_json(char *json, enum code_protocol code){
    switch (code)
    {
    case REP_CONNEXION:{
        json_object* object = json_tokener_parse(json);
        Rep_connexion_data data;
        json_object_object_get_ex(object, "wait", &data.wait);
        return &data;
        break;
    }
    case START_ROUND:{
        json_object* object = json_tokener_parse(json);
        Start_round_data data;
        json_object_object_get_ex(object, "game", &data.game);
        return &data;
        break;
    }


    }
}

void send_packet(enum code_protocol code, int client_id, void *data, int sockfd){
    Paquet paquet;
    paquet.code_protocole = code;
    paquet.client_id = client_id;
    char* json = convert_data_to_json(code, data);
    int len;
    if (json!=NULL)
    {
         len = strlen(json);
    }
    else
    {
        len = 0;
    }
    
    
    memcpy(&paquet.json_data,json,len);
    free(json);
    write(sockfd, &paquet, sizeof(Paquet));
}


