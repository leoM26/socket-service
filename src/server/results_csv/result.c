#include <stdio.h>
#include "result.h"

void write_header(){
    FILE *fichier = fopen("./exports/results.csv", "w+");
    fprintf(fichier,"id;temps de réaction;choix;round;points round;points totaux\n");
    fclose(fichier);
}

void write_line(Round_choice *data, int round, int points, int points_totaux){
    FILE *fichier = fopen("./exports/results.csv", "a+");
    fprintf(fichier,"%d;%0.2f;%d;%d;%d;%d\n", data->client_id,data->time,data->choice,round, points, points_totaux);
    fclose(fichier);
}