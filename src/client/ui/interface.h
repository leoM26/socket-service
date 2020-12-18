/*
 * Created on Fri Dec 18 2020
 *
 * Copyright (c) 2020 Léo Albouy & Louis Clement & Max Fournier & Térence Epinat
 */

#ifndef INTERFACE_HEADER_FILE_H
#define INTERFACE_HEADER_FILE_H

void rep_connection();
void round_start(int winner, int round, int points);
void end_game(int winner);
void interface_start(int argc,char **argv);
#endif