#ifndef GAME_HEADER_SERVER_H
#define GAME_HEADER_SERVER_H

typedef struct
{
    int client_id;
    int choice;
    double time;
} Round_choice;

enum choice{
    TRAHIR = 1,
    COLLABORER = 2,
};

void add_round_choice(Round_choice* choice);

Round_choice* get_client_choice(int client_id);

void remove_client_choice(Round_choice* choice);

#endif