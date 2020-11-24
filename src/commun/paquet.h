typedef struct {
    int code_protocole;
    int client_id;
    char json_data[256];
}Paquet;

typedef struct {
    int choice;
    double time;
}Choice_data;

typedef struct {
    char test[10];
}Connexion_data;

enum code_protocol {
    CONNEXION=0,//envoie texte
    REP_CONNEXION=1,//envoie attente oui ou non
    START_GAME=2,
    START_ROUND=3,
    CHOICE=4,//envoie choix, temps de réaction
    END_ROUND=5,
    END_GAME=6,//envoie gagnant
    STOP_CONNEXION=7
};