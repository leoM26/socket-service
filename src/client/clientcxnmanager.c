#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>

#include "clientcxnmanager.h"
#include "../commun/paquet.h"

int Socket;


void *threadProcess(void *ptr)
{
    char buffer_in[BUFFERSIZE];
    int sockfd = *((int *)ptr);
    int len;


    while ((len = read(sockfd, buffer_in, sizeof(Paquet))) != 0)
    {
        unsigned char *buffer = (unsigned char *)malloc(sizeof(Paquet));
        memcpy(buffer, buffer_in, sizeof(Paquet));
        Paquet *packet = (Paquet *)buffer;

        if (packet->code_protocole == REP_CONNEXION)
        {
            printf("client_id : %d\n", packet->client_id);
            printf("action : %d\n", packet->code_protocole);
            printf("json : %s\n", packet->json_data);
        }

        if (packet->code_protocole == START_ROUND)
        {
            printf("client_id : %d\n", packet->client_id);
            printf("action : %d\n", packet->code_protocole);
            printf("json : %s\n", packet->json_data);
        }

        
    
        if (strncmp(buffer_in, "exit", 4) == 0) {
            break;
        }

        printf("receive %d chars\n", len);
        printf("%.*s\n", len, buffer_in);
    }
    close(sockfd);
    printf("client pthread ended, len=%d\n", len);
}

int open_connection(Config *cfg)
{
    int sockfd;

    struct sockaddr_in serverAddr;
    int port = cfg->port;

    // Create the socket.
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    //Configure settings of the server address
    // Address family is Internet
    serverAddr.sin_family = AF_INET;
    //Set port number, using htons function
    serverAddr.sin_port = htons(port);
    //Set IP address to localhost
    //char *ip = cfg->ip;
    serverAddr.sin_addr.s_addr = inet_addr(cfg->ip);

    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    //Connect the socket to the server using the address
    if (connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) != 0)
    {
        printf("Fail to connect to server");
        exit(-1);
    };
    Socket = sockfd;
    return sockfd;
}

int get_socket(void){
    return Socket;
}
