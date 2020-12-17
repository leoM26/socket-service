#include <stdio.h>
#include "result.h"

void write_header(){
    FILE *fichier = fopen("./exports/results.csv", "w+");
    fprintf(fichier,"id;temps de réaction;choix;round\n");
    fclose(fichier);
}

void write_line(Round_choice *data, int round){
    FILE *fichier = fopen("./exports/results.csv", "a+");
    fprintf(fichier,"%d;%0.2f;%d;%d\n", data->client_id,data->time,data->choice,round);
    fclose(fichier);
}