#include <gtk/gtk.h>

#include "../../commun/paquet.h"
#include "../clientcxnmanager.h"
#include "../config/config.h"

GtkBuilder *builder = NULL;

int choix = 0;
int elapsed_time = 30;
int time_id = 0;

void rep_connection()
{
    GtkLabel *label = GTK_LABEL(gtk_builder_get_object(builder, "lb_evenement_msg"));
    gtk_label_set_text(label, "Vous etes actuellement dans la salle d'attente");
}

void round_start(bool winner, int round)
{
    GtkLabel *label = GTK_LABEL(gtk_builder_get_object(builder, "lb_evenement_msg"));
    gtk_label_set_text(label, "Faites vos jeux !");
    if (round != 0)
    {
        GtkLabel *label = GTK_LABEL(gtk_builder_get_object(builder, "lb_winner_msg"));
        if (winner)
        {
            gtk_label_set_text(label, "Vous avez gagné ce round !");
        }
        else
        {
            gtk_label_set_text(label, "Vous avez perdu ce round !");
        }
    }
    GtkLabel *round_label = GTK_LABEL(gtk_builder_get_object(builder, "lb_round_msg"));
    char title[3];
    sprintf(title, "%d", round);
    gtk_label_set_text(round_label, title);
}

void end_game(int winner)
{
    GtkLabel *label = GTK_LABEL(gtk_builder_get_object(builder, "lb_evennement_msg"));

    if (winner = 3)
    {
        gtk_label_set_text(label, "Personne n'a gagné ce round");
    }
    else if (winner = 1)
    {
        gtk_label_set_text(label, "Vous avez gagné ce round !");
    }
    else if (winner = 2)
    {
        gtk_label_set_text(label, "Vous avez perdu ce round !");
    }
}

int timer_handler()
{
    if (elapsed_time > 0)
    {
        elapsed_time--;
        char txt[100];
        GtkLabel *timelabel = GTK_LABEL(gtk_builder_get_object(builder, "lb_time_msg"));
        snprintf(txt, 100, "%02i", elapsed_time);
        gtk_label_set_text(timelabel, txt);
        return 1;
    }
}

void btn_collaborer_clicked(GtkButton *button, GtkLabel *label)
{
    printf("bouton 'Collaborer' clicked\n");
    gtk_label_set_text(GTK_LABEL(label), (const gchar *)"Collaborer");
    choix = 2;
}

void btn_trahir_clicked(GtkButton *button, GtkLabel *label)
{
    printf("bouton 'Trahir' clicked\n");
    gtk_label_set_text(GTK_LABEL(label), (const gchar *)"Trahir");
    choix = 1;
}

void btn_mise1_clicked(GtkButton *button, GtkLabel *label)
{
    printf("bouton 'Mise 1' clicked\n");
    gtk_label_set_text(GTK_LABEL(label), (const gchar *)"Mise 1");
}

void btn_mise2_clicked(GtkButton *button, GtkLabel *label)
{
    printf("bouton 'Mise 2' clicked\n");
    gtk_label_set_text(GTK_LABEL(label), (const gchar *)"Mise 2");
}

void btn_mise3_clicked(GtkButton *button, GtkLabel *label)
{
    printf("bouton 'Mise 3' clicked\n");
    gtk_label_set_text(GTK_LABEL(label), (const gchar *)"Mise 3");
}

void btn_mise4_clicked(GtkButton *button, GtkLabel *label)
{
    printf("bouton 'Mise 4' clicked\n");
    gtk_label_set_text(GTK_LABEL(label), (const gchar *)"Mise 4");
}

void btn_mise5_clicked(GtkButton *button, GtkLabel *label)
{
    printf("bouton 'Mise 5' clicked\n");
    gtk_label_set_text(GTK_LABEL(label), (const gchar *)"Mise 5");
}

void btn_send_clicked(GtkButton *button)
{
    printf("bouton 'Envoyer réponse' clicked\n");
    if (choix != 0)
    {
        Choice_data data = {.choice = choix, .time = 0};
        send_packet(CHOICE, get_config()->name, &data, get_socket());
    }
}

void on_window_main_show()
{
    printf("window open\n");
}

void on_window_main_destroy()
{
    printf("window close\n");
    gtk_main_quit();
}

void interface_start(int argc, char **argv)
{

    GtkWidget *win;
    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("glade/Interface.glade");
    win = GTK_WIDGET(gtk_builder_get_object(builder, "app_win"));
    g_object_set(gtk_settings_get_default(), "gtk-application-prefer-dark-theme", TRUE, NULL);
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(win);
    time_id = g_timeout_add(1000, (GSourceFunc)timer_handler, NULL);
}
