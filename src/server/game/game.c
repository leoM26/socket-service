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

void remove_client_choice(Round_choice* choice)    
{       
    for (int i = 0; i < 20; i++)    
    {    
        if (choice == choices[i])    
        {    
            choices[i] = NULL;    
            return;    
        }    
    }      
}