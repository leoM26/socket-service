#ifndef CONFIG_HEADER_SERVER_H
#define CONFIG_HEADER_SERVER_H
typedef struct{
    char *name;
    int *clients_name;
    int rounds;
    int current_round;
} Room;

typedef struct
{
    int *nb_room;
    Room *rooms;
} GameConfiguration;

typedef struct
{
    char *bind_ip;
    int *bind_port;
    int *max_simultaneous_connection;
    GameConfiguration *game_config;
} Config;

void read_config(Config *configuration, char *filename);

int get_adversaire(int client_id);

Room* get_room(int client_id);

#endif