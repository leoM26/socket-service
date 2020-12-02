#include <stdlib.h>
#include <libconfig.h>
#include "config.h"

Config* config = NULL;

Room* get_room(int client_id){
    GameConfiguration* game_config = config->game_config ;
    for (int i = 0; i < game_config->nb_room; i++)
    {
        Room *current_room = &game_config->rooms[i];
        for (int j = 0; j < 2; j++)
        {
            if (current_room->clients_name[j] == client_id)
            {
                return current_room;
            }
            
        }
        
    }
    
}


int get_adversaire(int client_id){

    Room* room = get_room(client_id);

    for (int i = 0; i < 2; i++)
    {
        if (room->clients_name[i] != client_id)
            return room->clients_name[i];
    } 
}

void parse_game_configuration(GameConfiguration *game_configuration, config_setting_t *setting)
{
    game_configuration = malloc(sizeof(GameConfiguration));
    game_configuration->nb_room = config_setting_length(setting);
    game_configuration->rooms = malloc((int)game_configuration->nb_room * sizeof(Room));
    Room *wp = game_configuration->rooms;
    for (int i = 0; i < game_configuration->nb_room; ++i)
    {
        config_setting_t *current_room_config = config_setting_get_elem(setting, i);
        config_setting_lookup_string(current_room_config, "name", &wp->name);
        printf("%s\n", wp->name);
        config_setting_t *clients_room_config = config_setting_get_member(current_room_config, "clients");
        wp->clients_name = (char **)malloc((int)2 * sizeof(char *));
        for (int j = 0; j < 2; j++)
        {
            wp->clients_name[j] = (int*)malloc(2 * sizeof(int));
            config_setting_t *client_name_config = config_setting_get_elem(clients_room_config, j);
            config_setting_lookup_int(client_name_config, "name", &wp->clients_name[j]);
        }
        game_configuration->rooms[i] = *wp;
        wp++;
    }
}

void *read_config(Config *configuration, char *filename)
{
    config_t cfg;
    config_setting_t *setting;
    config_init(&cfg);
    configuration = malloc(sizeof(Config));

    if (!config_read_file(&cfg, filename))
    {
        fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
                config_error_line(&cfg), config_error_text(&cfg));
        config_destroy(&cfg);
    }
    else
    {
        config_lookup_string(&cfg, "bind_ip", &configuration->bind_ip);
        config_lookup_int(&cfg, "bind_port", &configuration->bind_port);
        config_lookup_int(&cfg, "max_simultaneous_connection", &configuration->max_simultaneous_connection);

        setting = config_lookup(&cfg, "game_configuration");
        GameConfiguration *game_configuration;
        parse_game_configuration(&game_configuration, setting);
        configuration->game_config = game_configuration;
        config = configuration;
#if DEBUG
        printf("bind ip : %s\n", configuration->bind_ip);
        printf("bind port : %d\n", configuration->bind_port);
#endif
    }
}