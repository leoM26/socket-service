<!--
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]
--!>

<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/leoM26/socket-service">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">Projet C</h3>

  <p align="center">
    Dilemme du prisonnier
    <br />
    <a href=""><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="">View Demo</a>
    ·
    <a href="">Report Bug</a>
    ·
    <a href="">Request Feature</a>
  </p>
</p>

<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary><h2 style="display: inline-block">Sommaire</h2></summary>
  <ol>
    <li>
      <a href="#contexte">Contexte</a>
    </li>
    <li>
      <a href="#installation">Installation</a>
      <ul>
        <li><a href="#prérequis">Prérequis</a></li>
        <li><a href="#git-clone">Git clone</a></li>
      </ul>
    </li>
    <li>
    <a href="#configurations">Configurations</a>
    <ul>
        <li><a href="#pour-le-serveur">Serveur</a></li>
        <li><a href="#pour-les-clients">Clients</a></li>
      </ul>
    </li>
    <li><a href="#règle-du-jeu">Règle jeu</a></li>
    <li><a href="#résultat-jeu">Résultat jeu</a></li>
  </ol>
</details>

# Dilemme du prisonnier 

## Contexte
## Installation

### Prérequis :

Vérifier les bibliothèques sur Fedora: 
- libconfig-devel
- json-c-devel

### Git clone :

```bash
git clone https://github.com/leoM26/socket-service.git
cd socket-service/
make all
#Pour le serveur
./output/server
#Pour les clients
./output/client
```

## Configurations

### Pour le serveur : 

 Il est possible d'ajuster des éléments de configuration dans le fichier `server_config.cfg`.

```
bind_ip = "0.0.0.0"; #Exposer le serveur sur cette interface
bind_port = 7799; #Port utilisé pour le socket
max_simultaneous_connection = 50; 

game_configuration =
(
  {
    name = "room_1"; #Nom de la salle qui confronte client 1 et 2.
    rounds = 10; #Nombre maximum de round.
    clients = (
      {name = 1;},
      {name = 2;}
    );
  },
  {
    name = "room_2"; #Nom de la salle qui confronte client 3 et 4.
    rounds = 10; #Nombre maximum de round.
    clients = (
      {name = 3;},
      {name = 4;}
    );
  }
);
```

### Pour les clients :

 Vous pouvez ajuster l'adresse IP pour jouer en réseau ainsi que l'id du client dans `client_config.cfg`.

```
name = #indiquer l'id de votre client;
server_ip = "#indiquer votre adresse réseau"; 
server_port = 7799; #Port utilisé pour le socket
```
## Règle du jeu

Les règles du jeu sont simples, vous êtes confronté avec un autre prisonnier qui souhaite sortir au plus vite ! 
S'oppose à vous 2 propositions : `Collaborer` ou `Trahir`. Ce choix sera décisif selon celui de votre adversaire.

Si vous choissisez tous les deux `Collaborer` : Vous gagnerez **1** point chacun (pas de prise de risque).
Si vous choissisez tous les deux `Trahir` : Vous perderez **5** points chacun.

Si vous choissisez `Collaborer` et votre adversaire `Trahir` : Vous ne gagnerez pas de point alors que votre adversaire en gagnera **5** points.
Si vous choissisez `Trahir` et votre adversaire `Collaborer` : Vous gagnerez **5** points alors que votre adversaire n'en gagnera pas.
## Résultat jeu

Les résultats de votre partie seront enregistrés dans le dossier `exports` dans un fichier nommé `results.csv`.

