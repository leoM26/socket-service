/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: aurelio
 *
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
GtkBuilder *builder = NULL;
/*
 * 
 */

void on_button_click() {
    printf("bouton 'Yes' clicked\n");
}


int main(int argc, char **argv)
{


    GtkWidget *win;

    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("glade/Interface.glade");
    win = GTK_WIDGET(gtk_builder_get_object(builder, "app_win"));
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(win);
    gtk_main();

    Config cfg;
    read_config(&cfg, "client_config.cfg");

    int sockfd;
    int status = 0;
    char msg[100];
    pthread_t thread;

    sockfd = open_connection(&cfg);

    strcpy(msg, "Hello from Xeon"); //Xeon is the name of the this client
    printf("sending : %s\n", msg);
    write(sockfd, msg, strlen(msg));

    //Creation d'un pthread de lecture
    pthread_create(&thread, 0, threadProcess, &sockfd);
    //write(connection->sock,"Main APP Still running",15);
    pthread_detach(thread);
    do
    {
        fgets(msg, 100, stdin);
        //printf("sending : %s\n", msg);
        status = write(sockfd, msg, strlen(msg));
        //memset(msg,'\0',100);
    } while (status != -1);

    return (EXIT_SUCCESS);
}
