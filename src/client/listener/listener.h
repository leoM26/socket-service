/*
 * Created on Fri Dec 18 2020
 *
 * Copyright (c) 2020 Léo Albouy & Louis Clement & Max Fournier & Térence Epinat
 */

#ifndef LISTENER_HEADER_FILE_H
#define LISTENER_HEADER_FILE_H

#include "../../commun/paquet.h"

void on_rep_connection(Rep_connexion_data* data);
void on_round_start(Start_round_data* data);
void on_end_game(End_game_data* data);

#endif