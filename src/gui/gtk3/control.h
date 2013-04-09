#ifndef CONTROL_H_
#define CONTROL_H_

#include <gtk/gtk.h>
#include <webkit/webkit.h>
#include "../../backend/types.h"

#define LEARNC_GTK3_GLADE "/home/swilliams/workspace/learncurve++/src/gui/gtk3/main_gtk3.glade"

struct gtk_instance {
    char *file_name;
    instance data;
    GtkWidget *window;
    GtkWidget *about;
    WebKitWebView *webview;
};

int learnc_gtk3_gui_init(int &argc, char **argv[]);
int learnc_gtk3_instance_init(gtk_instance *data);

#endif
