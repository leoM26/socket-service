#include <stdlib.h>
#include "game.h"

Round_choice* choices[20];

void add_round_choice(Round_choice* choice){
    for (int i = 0; i < 20; i++)
    {
        if (choices[i] == NULL)
        {
            choices[i] = choice;
            return;
        }
        
    }
    
}

Round_choice* get_client_choice(int client_id){
    for (int i = 0; i < 20; i++)
    {
        if (choices[i] != NULL)
        {
            if (choices[i]->client_id == client_id)
            {
                return choices[i];
            }
            
        }
        
    }
    return NULL;
}




//-> Quand un client fait un choix

//si choix de l'adversaire n'est pas stocké get_client_choice(get_adversaire_id(connection->client_id))

    //add_client_choice(mon_choix)

//sinon
    //Récupère le choix de l'adversaire
    //Je détermine qui a gagné  0 -> 0 |  1 -> 1 | 0 -> 1
    //IMPORTANT : adversaire_choice = NULL
    //Envoie aux deux client qui a gagné