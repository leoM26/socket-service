/*
 * Created on Fri Dec 18 2020
 *
 * Copyright (c) 2020 Léo Albouy & Louis Clement & Max Fournier & Térence Epinat
 */

#ifndef CONFIG_HEADER_CLIENT_H
#define CONFIG_HEADER_CLIENT_H

typedef struct
{
    int name;
    char *ip;
    int port;
} Config;

Config* get_config();

void read_config(Config *configuration, char *filename);
#endif