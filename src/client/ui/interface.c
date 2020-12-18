#include <gtk/gtk.h>

#include "../../commun/paquet.h"
#include "../clientcxnmanager.h"
#include "../config/config.h"

GtkBuilder *builder = NULL;

int choix = 0;
int time_id = 0;
int elapsed_time = 30;

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
    //elapsed_time = 30;
}

//int timer(){
//    GTimer *timer = g_timer_new();
//    g_timer_start(timer);
//    char txt[100];
//    GtkLabel *timelabel = GTK_LABEL(gtk_builder_get_object(builder, "lb_time_msg"));
//    snprintf(txt, 100, "%02i", timer);
//    gtk_label_set_text(timelabel, txt);
//    return 1;
//}

void rep_connection()
{
    GtkLabel *label = GTK_LABEL(gtk_builder_get_object(builder, "lb_evenement_msg"));
    gtk_label_set_text(label, "Vous etes actuellement dans la salle d'attente");
}

void round_start(int winner, int round, int points)
{
    GtkLabel *evenement = GTK_LABEL(gtk_builder_get_object(builder, "lb_evenement_msg"));
    gtk_label_set_text(evenement, "Faites vos jeux !");
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
    GtkLabel *round_label = GTK_LABEL(gtk_builder_get_object(builder, "lb_round_msg"));
    char title_round[3];
    sprintf(title_round, "%d", round);
    gtk_label_set_text(round_label, title_round);

    GtkLabel *points_label = GTK_LABEL(gtk_builder_get_object(builder, "lb_points_msg"));
    char title_points[3];
    sprintf(title_points, "%d", points);
    gtk_label_set_text(points_label, title_points);
}

void end_game(int winner)
{
    GtkLabel *label = GTK_LABEL(gtk_builder_get_object(builder, "lb_evennement_msg"));

    if (winner)
    {
        gtk_label_set_text(label, "Bravo ! Vous etes le gagnant");
    }
    else
    {
        gtk_label_set_text(label, "Dommage ! Vous avez perdu");
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

void btn_send_clicked(GtkButton *button)
{
    printf("bouton 'Envoyer réponse' clicked\n");
    if (choix != 0)
    {
        Choice_data data = {.choice = choix, .time = elapsed_time};
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
