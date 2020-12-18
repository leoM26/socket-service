/*
 * Created on Fri Dec 18 2020
 *
 * Copyright (c) 2020 Léo Albouy & Louis Clement & Max Fournier & Térence Epinat
 */

#include <stdlib.h>
#include "game.h"

Round_choice* choices[20];

/**
 * @brief  Added round choice
 * 
 * @param  choice: choice in struct Round_choice
 */
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

/**
 * @brief  Get client choice
 * 
 * @param  client_id: identifier of client 
 * @return *Round_choice
 */
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

/**
 * @brief  Remove client choice
 * 
 * @param  choice: choice in struct Round_choice
 */
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