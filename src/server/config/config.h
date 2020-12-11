#ifndef SRC_SERVER_UTILS_CONFIG_H_
#define SRC_SERVER_UTILS_CONFIG_H_

#include <stdbool.h>

typedef struct
{
    const char *name;
    int rounds;
    int current_round;
    int *clients_name;
} Room;

typedef struct
{
    int nb_room;
    Room *rooms;
} GameConfiguration;

typedef struct
{
    const char *bind_ip;
    int bind_port;
    int max_simultaneous_connection;
    GameConfiguration *game_config;
} Config;

Config *init_configuration(void);
void read_config(Config *, char *filename);
Room* get_room(int client_id);
int get_adversaire(int client_id);

#endif //SRC_SERVER_UTILS_CONFIG_H_