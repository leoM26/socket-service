#include <stdlib.h>
#include <libconfig.h>
#include "config.h"

Config* config = NULL;

Config* get_config(){
    return config;
}

void read_config(Config *configuration, char *filename){
    config_t cfg;
    config_setting_t *setting;
    config_init(&cfg);

    if (!config_read_file(&cfg, filename))
    {
        fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
                config_error_line(&cfg), config_error_text(&cfg));
        config_destroy(&cfg);
    }else{
        config_lookup_int(&cfg, "name", &configuration->name);
        config_lookup_string(&cfg, "server_ip", &configuration->ip);
        config_lookup_int(&cfg, "server_port", &configuration->port);
    }
    #if DEBUG
        printf("client name : %d\n", configuration->name);
        printf("server ip : %s\n", configuration->ip);
        printf("server port : %d\n", configuration->port);
    #endif
    config = configuration;
}