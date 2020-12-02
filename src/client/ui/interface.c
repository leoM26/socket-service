#include<gtk/gtk.h>

#include "../../commun/paquet.h"
#include "../../server/srvcxnmanager.h"
#include "../clientcxnmanager.h"


GtkBuilder *builder = NULL;

void btn_collaborer_clicked(GtkButton *button, GtkLabel *label) {
    printf("bouton 'Collaborer' clicked\n");
    gtk_label_set_text (GTK_LABEL(label), (const gchar*) "Collaborer");
    Choice_data data ={.choice = 1,.time = 0};
    send_packet(CHOICE,0,&data, get_socket());
}

void btn_trahir_clicked(GtkButton *button, GtkLabel *label) {
    printf("bouton 'Trahir' clicked\n");
    gtk_label_set_text (GTK_LABEL(label), (const gchar*) "Trahir");
    //send_packet(CHOICE,packet->client_id,NULL, connection->sockfd);
}

void btn_send_clicked(GtkButton *button) {
    printf("bouton 'Envoyer réponse' clicked\n");
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
