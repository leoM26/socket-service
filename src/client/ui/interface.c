#include <gtk/gtk.h>

#include "../../commun/paquet.h"
#include "../clientcxnmanager.h"
#include "../config/config.h"

GtkBuilder *builder = NULL;

int choix = 0;
int elapsed_time = 30;
int time_id = 0;

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
    choix = 1;
}

void btn_trahir_clicked(GtkButton *button, GtkLabel *label)
{
    printf("bouton 'Trahir' clicked\n");
    gtk_label_set_text(GTK_LABEL(label), (const gchar *)"Trahir");
    Choice_data data = {.choice = 2, .time = 0};
    choix = 2;
}

void btn_mise1_clicked(GtkButton *button, GtkLabel *label)
{
    printf("bouton 'Mise 1' clicked\n");
    gtk_label_set_text(GTK_LABEL(label), (const gchar *)"Mise 1");
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
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(win);
    time_id = g_timeout_add(1000, (GSourceFunc)timer_handler, NULL);
}
