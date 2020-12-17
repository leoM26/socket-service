#include "listener.h"
#include "../ui/interface.h"

void on_rep_connection(Rep_connexion_data* data){
    if (data->wait)
    {
       rep_connection();
    }
}

void on_round_start(Start_round_data* data){
    round_start(data->winner,data->round, data->points);
}

void on_end_game(End_game_data* data){
    end_game(data->winner);
}