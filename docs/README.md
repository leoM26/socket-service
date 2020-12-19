# Protocole

| Code | Client     | Serveur      | Détails                                                           |
|------|------------|--------------|-------------------------------------------------------------------|
|  0   | CONNEXION  |              | *void*                                                            |
|  1   |            | REP_CONNEXION| *Rep_connexion_data*                                              |
|  2   | START_GAME |              | *void*                                                            |
|  3   |            | START_ROUND  | *Start_round_data*                                                |
|  4   |  CHOICE    |              | *Choice_data*                                                     |
|  5   |            | END_GAME     | *End_game_data*                                                   |
|  6   |STOP_CONNEXION|            | *void*                                                            |


# Structure

## Paquet
```C
typedef struct {
    int code_protocole;
    int client_id;
    char json_data[256];
}Paquet;
```

## Rep_connexion_data
```C
typedef struct {
    bool wait;
}Rep_connexion_data;
```

## Start_round_data
```C
typedef struct {
    int winner;
    int round;
    int points;
}Start_round_data;
```

## Choice_data
```C
typedef struct {
    int choice;
    double time;
}Choice_data;
```

## End_game_data
```C
typedef struct {
    int winner;
}End_game_data;
```