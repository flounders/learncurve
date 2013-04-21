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

#ifndef CONTROL_H_
#define CONTROL_H_

#include <gtk/gtk.h>
#include <webkit/webkit.h>
#include "../../backend/types.h"

#define LEARNC_GTK3_GLADE "/home/swilliams/workspace/learncurve++/src/gui/gtk3/main_gtk3.glade"

// gtk_instance is only for the GTK UI as it makes it the only
// way to pass arguments through GTK applications at all.
// file_name is what our cards file is. data comes from the backend
// and works with it. window is needed for different odds and ends.
// about is easier to pass this way. The webview needed to be included
// so different callbacks could handle page loading.

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
