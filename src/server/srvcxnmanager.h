/*
 * Created on Fri Dec 18 2020
 *
 * Copyright (c) 2020 Léo Albouy & Louis Clement & Max Fournier & Térence Epinat
 */

#ifndef SRVCXNMANAGER_H
#define SRVCXNMANAGER_H

#include "config/config.h"
#include <netinet/in.h>

#define BUFFERSIZE 2048
#define MAXSIMULTANEOUSCLIENTS 100

typedef struct {
    int sockfd;
    struct sockaddr address;
    int addr_len;
    int index;
    int client_id;
    int points;
} connection_t;


void init_sockets_array();
void add(connection_t *connection);
void del(connection_t *connection);
void *threadProcess(void *ptr);
int create_server_socket() ;


#endif /* SRVCXNMANAGER_H */

