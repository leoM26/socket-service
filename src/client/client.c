/*
 * Created on Fri Dec 18 2020
 *
 * Copyright (c) 2020 Léo Albouy & Louis Clement & Max Fournier & Térence Epinat
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include<gtk/gtk.h>

#include "clientcxnmanager.h"
#include "../commun/paquet.h"
#include "ui/interface.h"

/**
 * @brief  Debug thread on terminal
 *   
 * @param  socket: 
 */
void thread_terminal(int *socket) {

    int status;
    char msg[100];
  do
    {
        fgets(msg, 100, stdin);
        //printf("sending : %s\n", msg);
        //status = write(*socket, msg, strlen(msg));
        //memset(msg,'\0',100);
    } while (status != -1);
}

/**
 * @brief  Main client
 *   
 * @param  argc: 
 * @param  argv: 
 */
int main(int argc, char **argv)
{
    Config cfg;
    read_config(&cfg, "client_config.cfg");

    int sockfd;
    int status = 0;
    char msg[100];
    pthread_t thread,thread_2;

    interface_start(argc,argv);
    sockfd = open_connection(&cfg);

    //strcpy(msg, "Hello from Xeon"); //Xeon is the name of the this client
    //printf("sending : %s\n", msg);
    //write(sockfd, msg, strlen(msg));

   //Creation d'un pthread de lecture
    pthread_create(&thread, 0, threadProcess, &sockfd);
    //write(connection->sock,"Main APP Still running",15);
    pthread_detach(thread);

    send_packet(CONNEXION,cfg.name,NULL,sockfd);

    send_packet(START_GAME,cfg.name,NULL,sockfd);

    //Creation d'un pthread de lecture
    pthread_create(&thread_2, 0, thread_terminal, &sockfd);
    //write(connection->sock,"Main APP Still running",15);
    pthread_detach(thread_2);


    gtk_main();

    return (EXIT_SUCCESS);
}
