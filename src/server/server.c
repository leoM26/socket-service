/*
 * Created on Fri Dec 18 2020
 *
 * Copyright (c) 2020 Léo Albouy & Louis Clement & Max Fournier & Térence Epinat
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <stdbool.h>

#include "srvcxnmanager.h"
#include "../commun/paquet.h"


/**
 * @brief  Main of server 
 *   
 * @param  argc: 
 * @param  argv: 
 */
int main(int argc, char** argv) {


    Config cfg;
    read_config(&cfg, "server_config.cfg");

    int sockfd = -1;
    int index = 1;
    connection_t *connection;
    pthread_t thread;


    /* init array*/
    init_sockets_array();
    /* create socket */
    sockfd = create_server_socket();

    /* listen on port , stack size 50 for incoming connections*/
    if (listen(sockfd, 50) < 0) {
        fprintf(stderr, "%s: error: cannot listen on port\n", argv[0]);
        return -5;
    }

    printf("ready and listening\n");

    //Wait for connection
    while (true) {
        /* accept incoming connections */
        connection = (connection_t *) malloc(sizeof (connection_t));
        connection->sockfd = accept(sockfd, &connection->address, &connection->addr_len);
        connection->index = index++;
        if (connection->sockfd <= 0) {
            free(connection);
        } else {
            /* start a new thread but do not wait for it */
            pthread_create(&thread, 0, threadProcess, (void *) connection);
            pthread_detach(thread);
        }
    }
    return (EXIT_SUCCESS);
}

