/* Learncurve is a flash card like review program.
Copyright (C) 2013  Steven Michael Williams

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA. */

#include <gtk/gtk.h>
#include <iostream>
#include <string>
#include <webkit/webkit.h>
#include "../../backend/htmlgen.h"
#include "../../backend/initialize.h"
#include "control.h"

int learnc_gtk3_gui_init(int &argc, char **argv[])
{
    GtkBuilder *builder;
    gtk_instance cb_args;
    GtkWidget *webcon;
    std::string page;

    gtk_init(&argc, argv);

    learnc_gtk3_instance_init(&cb_args);

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, LEARNC_GTK3_GLADE,
                              NULL);

    if (builder == NULL) {
        std::cerr << "learnc_gtk3_gui_init: Encountered error adding glade file.\n";
        return 0;
    }

    cb_args.window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    webcon = GTK_WIDGET(gtk_builder_get_object(builder, "scrolledwindow"));
//    cb_args.about = GTK_WIDGET(gtk_builder_get_object(builder, "aboutdialog"));

    cb_args.webview = WEBKIT_WEB_VIEW(webkit_web_view_new());
    gtk_container_add(GTK_CONTAINER(webcon), GTK_WIDGET(cb_args.webview));
    learnc_html_welcome_page(page);
    webkit_web_view_load_html_string(cb_args.webview, page.c_str(),
                                     "../../backend");

    gtk_widget_show_all(cb_args.window);

    gtk_builder_connect_signals(builder, &cb_args);

    g_object_unref(G_OBJECT(builder));

    gtk_main();

    return 1;
}

int learnc_gtk3_instance_init(gtk_instance *data)
{
    if (data == NULL)
        return 0;

    data->file_name = NULL;
    data->webview = NULL;
    data->window = NULL;
    learnc_init_instance(data->data);

    return 1;
}
