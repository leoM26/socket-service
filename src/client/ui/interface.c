/*
 * Created on Fri Dec 18 2020
 *
 * Copyright (c) 2020 Léo Albouy & Louis Clement & Max Fournier & Térence Epinat
 */

#include <gtk/gtk.h>

#include "../../commun/paquet.h"
#include "../clientcxnmanager.h"
#include "../config/config.h"

GtkBuilder *builder = NULL;

int choix = 0;
int time_id = 0;
float elapsed_time = 0;

/**
 * @brief Timer for reaction time
 *   
 */
int timer_handler()
{
    elapsed_time += 0.1;
    char txt[100];
    GtkLabel *timelabel = GTK_LABEL(gtk_builder_get_object(builder, "lb_time_msg"));
    snprintf(txt, 100, "%0.1f", elapsed_time);
    gtk_label_set_text(timelabel, txt);
    return 1;
}

/**
 * @brief Reply connection
 *   
 */
void rep_connection()
{
    GtkLabel *label = GTK_LABEL(gtk_builder_get_object(builder, "lb_evenement_msg"));
    gtk_label_set_text(label, "Vous etes actuellement dans la salle d'attente");
}

/**
 * @brief  Start round
 *   
 * @param  winner: display winner of round
 * @param  round: display current round
 * @param  points: display points of player
 */
void round_start(int winner, int round, int points)
{
    GtkLabel *evenement = GTK_LABEL(gtk_builder_get_object(builder, "lb_evenement_msg"));
    gtk_label_set_text(evenement, "Un nouveau round commence !");
    if (time_id > 0)
    {
        g_source_remove(time_id);
    }
    if (round != 0)
    {
        GtkLabel *label = GTK_LABEL(gtk_builder_get_object(builder, "lb_winner_msg"));
        if (winner == 3)
        {
            gtk_label_set_text(label, "Personne n'a gagné ce round");
            gtk_label_set_text(evenement, "Vous gagnez 1 point");
        }
        else if (winner == 4)
        {
            gtk_label_set_text(label, "Personne n'a gagné ce round");
            gtk_label_set_text(evenement, "Vous perdez 5 points");
        }

        else if (winner == 1)
        {
            gtk_label_set_text(label, "Vous avez gagné ce round !");
            gtk_label_set_text(evenement, "Vous gagnez 5 points");
        }
        else if (winner == 2)
        {
            gtk_label_set_text(label, "Vous avez perdu ce round !");
            gtk_label_set_text(evenement, "Vous ne gagnez pas de point");
        }
    }
    sleep(5);
    elapsed_time = 0;
    time_id = g_timeout_add(100, (GSourceFunc)timer_handler, NULL);
    gtk_label_set_text(evenement, "Faites vos jeux !");
    GtkLabel *round_label = GTK_LABEL(gtk_builder_get_object(builder, "lb_round_msg"));
    char title_round[3];
    sprintf(title_round, "%d", round);
    gtk_label_set_text(round_label, title_round);

    GtkLabel *points_label = GTK_LABEL(gtk_builder_get_object(builder, "lb_points_msg"));
    char title_points[3];
    sprintf(title_points, "%d", points);
    gtk_label_set_text(points_label, title_points);
}

/**
 * @brief End game 
 *   
 * @param  winner: display winner at the end of the game 
 */
void end_game(int winner)
{
    GtkLabel *label = GTK_LABEL(gtk_builder_get_object(builder, "lb_evenement_msg"));

    if (winner == 1)
    {
        gtk_label_set_text(label, "Bravo ! Vous etes le gagnant");
    }
    else if (winner == 0)
    {
        gtk_label_set_text(label, "Dommage ! Vous avez perdu");        
    }
    else
    {
        gtk_label_set_text(label, "Egalité !"); 
    }
    
    GtkLabel *round_label = GTK_LABEL(gtk_builder_get_object(builder, "lb_round_msg"));
    gtk_label_set_text(round_label, "Partie terminé");
    g_source_remove(time_id);
}

/**
 * @brief  Button collaborer clicked
 * 
 * @param  button: button clicked
 * @param  label: change text of label
 */
void btn_collaborer_clicked(GtkButton *button, GtkLabel *label)
{
    printf("bouton 'Collaborer' clicked\n");
    gtk_label_set_text(GTK_LABEL(label), (const gchar *)"Collaborer");
    choix = 2;
}

/**
 * @brief  Button Trahir clicked
 * 
 * @param  button: button clicked
 * @param  label: change text of label
 */
void btn_trahir_clicked(GtkButton *button, GtkLabel *label)
{
    printf("bouton 'Trahir' clicked\n");
    gtk_label_set_text(GTK_LABEL(label), (const gchar *)"Trahir");
    choix = 1;
}

/**
 * @brief  Button Send clicked
 *  
 * @param  button: button clicked
 */
void btn_send_clicked(GtkButton *button)
{
    printf("bouton 'Envoyer réponse' clicked\n");
    if (choix != 0)
    {
        Choice_data data = {.choice = choix, .time = elapsed_time};
        send_packet(CHOICE, get_config()->name, &data, get_socket());
    }
}

/**
 * @brief  Debug display main window
 *  
 */
void on_window_main_show()
{
    printf("window open\n");
}

/**
 * @brief  Debug close main window
 *  
 */
void on_window_main_destroy()
{
    printf("window close\n");
    gtk_main_quit();
}

/**
 * @brief  Init & start main window
 *   
 * @param  argc: 
 * @param  argv: 
 */
void interface_start(int argc, char **argv)
{
    GtkWidget *win;
    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("glade/Interface.glade");
    win = GTK_WIDGET(gtk_builder_get_object(builder, "app_win"));
    g_object_set(gtk_settings_get_default(), "gtk-application-prefer-dark-theme", TRUE, NULL);
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(win);
}
