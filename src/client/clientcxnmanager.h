/*
 * Created on Fri Dec 18 2020
 *
 * Copyright (c) 2020 Léo Albouy & Louis Clement & Max Fournier & Térence Epinat
 */

#ifndef CLIENTCXNMANAGER_H
#define CLIENTCXNMANAGER_H

#define BUFFERSIZE 2048

#include "config/config.h"

void *threadProcess(void * ptr);
int open_connection(Config * cfg);
int get_socket(void);

#endif /* CLIENTCXNMANAGER_H */

