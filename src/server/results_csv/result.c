#include <stdio.h>
#include "result.h"

void write_header(){
    char *header = "id;temps de réaction;choix;round\n";
    FILE *fichier = fopen("./exports/results.csv", "w+");
    fwrite(header,35,1,fichier);
    fclose(fichier);
}

void write_line(Round_choice *data, int round){
    char *txt = malloc(100 * sizeof(char));
    FILE *fichier = fopen("./exports/results.csv", "a+");
    sprintf(txt,"%d,%0.2f,%d,%d\n", data->client_id,data->time,data->choice,round);
    fwrite(txt,100,1,fichier);
    fclose(fichier);
}