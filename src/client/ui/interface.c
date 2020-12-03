#include<gtk/gtk.h>

#include "../../commun/paquet.h"
#include "../../server/srvcxnmanager.h"
#include "../clientcxnmanager.h"


GtkBuilder *builder = NULL;

int choix = 0;

void btn_collaborer_clicked(GtkButton *button, GtkLabel *label) {
    printf("bouton 'Collaborer' clicked\n");
    gtk_label_set_text (GTK_LABEL(label), (const gchar*) "Collaborer");
   choix =1;
}

void btn_trahir_clicked(GtkButton *button, GtkLabel *label) {
    printf("bouton 'Trahir' clicked\n");
    gtk_label_set_text (GTK_LABEL(label), (const gchar*) "Trahir");
    Choice_data data ={.choice = 2,.time = 0};
    choix = 2;
}

void btn_send_clicked(GtkButton *button) {
    printf("bouton 'Envoyer réponse' clicked\n");
    if (choix != 0)
    {
    Choice_data data ={.choice = choix,.time = 0};
    send_packet(CHOICE,NULL,&data, get_socket());
    }
}

void on_window_main_show() {
    printf("window open\n");
}

void on_window_main_destroy() {
    printf("window close\n");
    gtk_main_quit();
}

void interface_start(int argc,char **argv) {

    GtkWidget *win;
    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("glade/Interface.glade");
    win = GTK_WIDGET(gtk_builder_get_object(builder, "app_win"));
    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show(win);
}
