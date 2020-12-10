#ifndef GAME_HEADER_SERVER_H
#define GAME_HEADER_SERVER_H

typedef struct
{
    int client_id;
    int choice;
} Round_choice;

void add_round_choice(Round_choice* choice);

Round_choice* get_client_choice(int client_id);

#endif