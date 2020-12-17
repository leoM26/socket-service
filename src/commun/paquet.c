#include <json-c/json.h>
#include <string.h>
#include "paquet.h"

char *convert_data_to_json(enum code_protocol code, void *data)
{

    json_object *object = json_object_new_object();

    switch (code)
    {
    case CONNEXION:
    {
        return NULL;
        break;
    }
    case REP_CONNEXION:
    {
        Rep_connexion_data *results = (Rep_connexion_data *)data;
        json_object_object_add(object, "wait", json_object_new_boolean(results->wait));
        break;
    }

    case START_ROUND:
    {
        Start_round_data *results = (Start_round_data *)data;
        json_object_object_add(object, "winner", json_object_new_int(results->winner));
        json_object_object_add(object, "round", json_object_new_int(results->round));
        json_object_object_add(object, "points", json_object_new_int(results->points));
        break;
    }
    case CHOICE:
    {
        Choice_data *results = (Choice_data *)data;
        json_object_object_add(object, "choice", json_object_new_int(results->choice));
        json_object_object_add(object, "time", json_object_new_double(results->time));
        break;
    }
    case END_GAME:
    {
        End_game_data *results = (End_game_data *)data;
        json_object_object_add(object, "winner", json_object_new_int(results->winner));
        break;
    }
    case STOP_CONNEXION:
    {
        return NULL;
        break;
    }
    }
    return json_object_get_string(object);
}

void *parse_json(char *json, enum code_protocol code)
{
    json_object *object = json_tokener_parse(json);
    switch (code)
    {
    case REP_CONNEXION:
    {
        Rep_connexion_data *data = (Rep_connexion_data *)malloc(sizeof(Rep_connexion_data));
        json_object *wait_object = json_object_object_get(object, "wait");
        data->wait = json_object_get_boolean(wait_object);
        return data;
        break;
    }
    case START_ROUND:
    {
        Start_round_data *data = (Start_round_data *)malloc(sizeof(Start_round_data));
        json_object *round_object = json_object_object_get(object, "round");
        json_object *winner_object = json_object_object_get(object, "winner");
        json_object *points_object = json_object_object_get(object, "points");
        data->round = json_object_get_int(round_object);
        data->winner = json_object_get_int(winner_object);
        data->points = json_object_get_int(points_object);
        return data;
        break;
    }
    case CHOICE:
    {
        Choice_data *data = (Choice_data *)malloc(sizeof(Choice_data));
        json_object *choice_object = json_object_object_get(object, "choice");
        json_object *time_object = json_object_object_get(object, "time");
        data->choice = json_object_get_int(choice_object);
        data->time = json_object_get_double(time_object);
        return data;
        break;
    }
    case END_GAME:
    {
        End_game_data data;
        json_object_object_get_ex(object, "winner", &data.winner);
        return &data;
        break;
    }
    }
}

void send_packet(enum code_protocol code, int client_id, void *data, int sockfd)
{
    Paquet paquet;
    paquet.code_protocole = code;
    paquet.client_id = client_id;
    char *json = convert_data_to_json(code, data);
    int len;
    if (json != NULL)
    {
        len = strlen(json);
    }
    else
    {
        len = 0;
    }

    memcpy(&paquet.json_data, json, len);
    free(json);
    write(sockfd, &paquet, sizeof(Paquet));
}
