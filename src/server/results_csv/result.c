/*
 * Created on Fri Dec 18 2020
 *
 * Copyright (c) 2020 Léo Albouy & Louis Clement & Max Fournier & Térence Epinat
 */

#include <stdio.h>
#include "result.h"

/**
 * @brief  Write header in CSV results
 *   
 */
void write_header(){
    FILE *fichier = fopen("./exports/results.csv", "w+");
    fprintf(fichier,"id;temps de réaction;choix;round;points round;points totaux\n");
    fclose(fichier);
}

/**
 * @brief  Write line in CSV results
 *   
 * @param  data:
 * @param  round: current round
 * @param  points: points of player
 * @param  points_totaux: total pionts of game 
 */
void write_line(Round_choice *data, int round, int points, int points_totaux){
    FILE *fichier = fopen("./exports/results.csv", "a+");
    fprintf(fichier,"%d;%0.2f;%d;%d;%d;%d\n", data->client_id,data->time,data->choice,round, points, points_totaux);
    fclose(fichier);
}