/*
 * Created on Fri Dec 18 2020
 *
 * Copyright (c) 2020 Léo Albouy & Louis Clement & Max Fournier & Térence Epinat
 */

#include "../../commun/paquet.h"
#include "../game/game.h"
#include "../srvcxnmanager.h"

void write_header();

void write_line(Round_choice *data, int round, int points, int points_totaux);