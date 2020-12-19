/*
 * Created on Fri Dec 18 2020
 *
 * Copyright (c) 2020 Léo Albouy & Louis Clement & Max Fournier & Térence Epinat
 */

#include "listener.h"
#include "../ui/interface.h"

/**
 * @brief Listener on connection
 * 
 * @param  data: data of struc Rep_connexion_data
 */
void on_rep_connection(Rep_connexion_data* data){
    if (data->wait)
    {
       rep_connection();
    }
}

/**
 * @brief Listener on start round
 * 
 * @param  data: data of struc Start_round_data
 */
void on_round_start(Start_round_data* data){
    round_start(data->winner,data->round, data->points);
}

/**
 * @brief Listener on end game
 * 
 * @param  data: data in struc End_game_data
 */
void on_end_game(End_game_data* data){
    end_game(data->winner);
}