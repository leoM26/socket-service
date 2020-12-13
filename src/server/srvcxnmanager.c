
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "srvcxnmanager.h"
#include "../commun/paquet.h"
#include "game/game.h"
#include "config/config.h"

connection_t *connections[MAXSIMULTANEOUSCLIENTS];

void init_sockets_array()
{
    for (int i = 0; i < MAXSIMULTANEOUSCLIENTS; i++)
    {
        connections[i] = NULL;
    }
}

void add(connection_t *connection)
{
    for (int i = 0; i < MAXSIMULTANEOUSCLIENTS; i++)
    {
        if (connections[i] == NULL)
        {
            connections[i] = connection;
            return;
        }
    }
    perror("Too much simultaneous connections");
    exit(-5);
}

connection_t *get_connection(int client_id)
{
    for (int i = 0; i < MAXSIMULTANEOUSCLIENTS; i++)
    {
        if (connections[i] != NULL)
        {
            if (connections[i]->client_id == client_id)
            {
                return connections[i];
            }
        }
    }
    return NULL;
}

void del(connection_t *connection)
{
    for (int i = 0; i < MAXSIMULTANEOUSCLIENTS; i++)
    {
        if (connections[i] == connection)
        {
            connections[i] = NULL;
            return;
        }
    }
    perror("Connection not in pool ");
    exit(-5);
}
/*
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_lock(&lock);
pthread_mutex_unlock(&lock);
 */

/**
 * Thread allowing server to handle multiple client connections
 * @param ptr connection_t 
 * @return 
 */
void *threadProcess(void *ptr)
{
    char buffer_in[BUFFERSIZE];
    char buffer_out[BUFFERSIZE];

    int len;
    connection_t *connection;

    if (!ptr)
        pthread_exit(0);
    connection = (connection_t *)ptr;
    printf("New incoming connection \n");

    add(connection);

    //Welcome the new client
    // printf("Welcome #%i\n", connection->index);
    // sprintf(buffer_out, "Welcome #%i\n", connection->index);
    // write(connection->sockfd, buffer_out, strlen(buffer_out));
    connection->points = 0;

    while ((len = read(connection->sockfd, buffer_in, sizeof(Paquet))) > 0)
    {
        unsigned char *buffer = (unsigned char *)malloc(sizeof(Paquet));
        memcpy(buffer, buffer_in, sizeof(Paquet));
        Paquet *packet = (Paquet *)buffer;

        connection->client_id = packet->client_id;

        if (packet->code_protocole == CONNEXION)
        {
            Rep_connexion_data data = {.wait = true};
            send_packet(REP_CONNEXION, packet->client_id, &data, connection->sockfd);
            printf("client_id : %d\n", packet->client_id);
            printf("action : %d\n", packet->code_protocole);

            connection_t *adversaire_connection = get_connection(get_adversaire(packet->client_id));

            if (adversaire_connection != NULL)
            {
                Room *room = get_room(packet->client_id);
                room->current_round = 0;
                Start_round_data round_data = {.winner = true,.round = room->current_round};
                send_packet(START_ROUND, packet->client_id, &round_data, connection->sockfd);
                send_packet(START_ROUND, adversaire_connection->client_id, &round_data, adversaire_connection->sockfd);
            }
        }

        if (packet->code_protocole == CHOICE)
        {
            Choice_data *data = parse_json(packet->json_data, CHOICE);
            printf("client_id : %d\n", packet->client_id);
            printf("choice : %d\n", data->choice);
            Round_choice *choice_adversaire = get_client_choice(get_adversaire(packet->client_id));
            if (choice_adversaire == NULL)
            {
                Round_choice *choice = malloc(sizeof(Round_choice));
                choice->client_id = packet->client_id;
                choice->choice = data->choice;
                add_round_choice(choice);
            }
            else
            {
                connection_t *adversaire_connection = get_connection(get_adversaire(packet->client_id));
                if (choice_adversaire->choice == data->choice == COLLABORER)
                {
                    adversaire_connection->points++;
                    connection->points++;
                }
                else if (choice_adversaire->choice == data->choice == TRAHIR)
                {
                    adversaire_connection->points -= 5;
                    connection->points -= 5;
                }
                else if (choice_adversaire->choice == COLLABORER && data->choice == TRAHIR)
                {
                    connection->points +=5;
                }
                else
                {
                    adversaire_connection->points += 5;
                }
                Room* room = get_room(packet->client_id);
                room->current_round++;
                remove_client_choice(choice_adversaire);
                if (room->current_round < room->rounds)
                {
                    Start_round_data data = {.winner = true, .round = room->current_round};
                    Start_round_data adversaire_data = {.winner = false, .round = room->current_round};
                    send_packet(START_ROUND,packet->client_id, &data, connection->sockfd);
                    send_packet(START_ROUND,adversaire_connection->client_id, &adversaire_data, adversaire_connection->sockfd);
                }
                else
                {
                    End_game_data data = {.winner = true};
                    End_game_data adversaire_data = {.winner = false};
                    send_packet(END_GAME,packet->client_id,&data,connection->sockfd);
                    send_packet(END_GAME,adversaire_connection->client_id,&adversaire_data,adversaire_connection->sockfd);
                }
            
            }
        }

        //-> Quand un client fait un choix

        //si choix de l'adversaire n'est pas stocké get_client_choice(get_adversaire_id(connection->client_id))

        //add_client_choice(mon_choix)

        //sinon
        //Récupère le choix de l'adversaire
        //Je détermine qui a gagné  0 -> 0 |  1 -> 1 | 0 -> 1
        //IMPORTANT : adversaire_choice = NULL
        //Envoie aux deux client qui a gagné

        //       if (strncmp(buffer_in, "bye", 3) == 0) {
        //           break;
        //       }
        //#if DEBUG
        //       printf("DEBUG-----------------------------------------------------------\n");
        //        printf("len : %i\n", len);
        //
        //       printf("----------------------------------------------------------------\n");
        //#endif
        //        strcpy(buffer_out, "\nServer Echo : ");
        //       strncat(buffer_out, buffer_in, len);
        //
        // if (buffer_in[0] == '@') {
        //     for (int i = 0; i < MAXSIMULTANEOUSCLIENTS; i++) {
        //         if (connections[i] != NULL) {
        //             write(connections[i]->sockfd, buffer_out, strlen(buffer_out));
        //         }
        //     }
        // } else if (buffer_in[0] == '#') {
        //     int client = 0;
        //     int read = sscanf(buffer_in, "%*[^0123456789]%d ", &client);
        //     for (int i = 0; i < MAXSIMULTANEOUSCLIENTS; i++) {
        //         if (client == connections[i]->index) {
        //             write(connections[i]->sockfd, buffer_out, strlen(buffer_out));
        //             break;
        //         } //no client found ? : we dont care !!
        //     }
        // } else {
        //     write(connection->sockfd, buffer_out, strlen(buffer_out));
        // }

        //clear input buffer
        memset(buffer_in, '\0', BUFFERSIZE);
    }
    printf("Connection to client %i ended \n", connection->index);
    close(connection->sockfd);
    del(connection);
    free(connection);
    pthread_exit(0);
}

int create_server_socket()
{
    int sockfd = -1;
    struct sockaddr_in address;
    int port = 7799;

    /* create socket */
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd <= 0)
    {
        fprintf(stderr, "%s: error: cannot create socket\n");
        return -3;
    }

    /* bind socket to port */
    address.sin_family = AF_INET;
    //bind to all ip :
    //address.sin_addr.s_addr = INADDR_ANY;
    //ou 0.0.0.0
    //Sinon  127.0.0.1
    address.sin_addr.s_addr = inet_addr("0.0.0.0");
    address.sin_port = htons(port);

    /* prevent the 60 secs timeout */
    int reuse = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char *)&reuse, sizeof(reuse));

    /* bind */
    if (bind(sockfd, (struct sockaddr *)&address, sizeof(struct sockaddr_in)) < 0)
    {
        fprintf(stderr, "error: cannot bind socket to port %d\n", port);
        return -4;
    }

    return sockfd;
}
