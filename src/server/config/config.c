/*
 * Created on Fri Dec 18 2020
 *
 * Copyright (c) 2020 Léo Albouy & Louis Clement & Max Fournier & Térence Epinat
 */

#include <stdlib.h>
#include <libconfig.h>
#include <assert.h>
#include <string.h>
#include <libgen.h>
#include <unistd.h>

#include "config.h"

Config *conf = NULL;

/**
 * @brief  Parse game configuration
 *   
 * @param  game_configuration: game configuration in struct GameConfiguration
 * @param  settings: settings in struct config_setting_t
 */
void parse_game_configuration(GameConfiguration *game_configuration, config_setting_t *settings)
{
    game_configuration->nb_room = config_setting_length(settings);
    game_configuration->rooms = (Room *)malloc((int)game_configuration->nb_room * sizeof(Room));
    Room *wp = game_configuration->rooms;
    for (int i = 0; i < (int)game_configuration->nb_room; ++i)
    {
        config_setting_t *current_room_config = config_setting_get_elem(settings, i);
        config_setting_lookup_string(current_room_config, "name", (const char **)&wp->name);
        config_setting_lookup_int(current_room_config, "rounds", (int *)&wp->rounds);
        const config_setting_t *clients_room_config = config_setting_get_member(current_room_config, "clients");
        const int nb_players = config_setting_length(clients_room_config);
        wp->clients_name = (int *)malloc(nb_players * sizeof(int));
        for (int j = 0; j < nb_players; j++)
        {
            const config_setting_t *client_name_config = config_setting_get_elem(clients_room_config, j);
            config_setting_lookup_int(client_name_config, "name", (int *)&wp->clients_name[j]);
        }
        game_configuration->rooms[i] = *wp;
        wp++;
    }
}

/**
 * @brief  Read configuration file for server
 *   
 * @param  configuration: current configuration
 * @param  filename: name of configuration file
 */
void read_config(Config *config, char *filename)
{
    config_t cfg;
    config_setting_t *setting;
    config_init(&cfg);
    conf = config;

    if (!config_read_file(&cfg, filename))
    {
        fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
                config_error_line(&cfg), config_error_text(&cfg));
        config_destroy(&cfg);
    }
    else
    {
        config_lookup_string(&cfg, "bind_ip", &conf->bind_ip);
        config_lookup_int(&cfg, "bind_port", (int *)&conf->bind_port);
        config_lookup_int(&cfg, "max_simultaneous_connection", (int *)&conf->max_simultaneous_connection);

        setting = config_lookup(&cfg, "game_configuration");
        GameConfiguration *game_configuration = (GameConfiguration *)malloc(sizeof(GameConfiguration));
        parse_game_configuration(game_configuration, setting);
        conf->game_config = game_configuration;
    }
}

/**
 * @brief Get room
 *   
 * @param  client_id: identifier of client
 * @return *Room 
 */
Room* get_room(int client_id){
    GameConfiguration* game_config = conf->game_config ;
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

/**
 * @brief  Get opponent
 * 
 * @param  client_id: identifier of client
 * @return room
 */
int get_adversaire(int client_id){

    Room* room = get_room(client_id);

    for (int i = 0; i < 2; i++)
    {
        if (room->clients_name[i] != client_id)
            return room->clients_name[i];
    }
}