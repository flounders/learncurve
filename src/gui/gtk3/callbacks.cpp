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

#include <climits>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <gtk/gtk.h>
#include <libxml/xmlreader.h>
#include "../../backend/boxes.h"
#include "../../backend/htmlgen.h"
#include "../../backend/initialize.h"
#include "../../backend/read_vocab_file.h"
#include "../../backend/review.h"
#include "../../backend/save_restore.h"
#include "../../backend/types.h"
#include "control.h"

// callbacks.cpp contains all the callbacks for the GTK3 UI

using namespace std;

static int review_state;

extern "C"
void learnc_gtk_open_cb(gtk_instance *gtk_data)
{
    xmlTextReaderPtr reader;
    GtkWidget *file_dialog;
    ifstream infile;
    char path[PATH_MAX];
    int status;

    if (gtk_data == NULL) {
        cerr << "learnc_gtk_open_cb: Received NULL on gtk_data.\n";
        return;
    }

    file_dialog = gtk_file_chooser_dialog_new("Open File",
                                              GTK_WINDOW(gtk_data->window),
                                              GTK_FILE_CHOOSER_ACTION_OPEN,
                                              GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                              GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                              NULL);

    if (gtk_dialog_run(GTK_DIALOG(file_dialog)) == GTK_RESPONSE_ACCEPT) {
        gtk_data->file_name = (char *) gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_dialog));
        reader = xmlReaderForFile(gtk_data->file_name, NULL, 0);

        if (reader == NULL) {
            gtk_widget_destroy(file_dialog);
            cerr << "learnc_gtk_open_cb: Encountered error opening XML file.\n";
            return;
        }
    }
    else {
        gtk_widget_destroy(file_dialog);
        return;
    }

    status = learnc_parse_file(reader, gtk_data->data.stack);
    if (status == 0) {
        cerr << "learnc_gtk_open_cb: Encountered error with learnc_parse_file().\n";
        return;
    }

    gtk_data->data.known->size = gtk_data->data.stack.size();

    learnc_make_storage_directory(gtk_data->file_name);

    if (learnc_get_storage_path(gtk_data->file_name, path) == 1) {
        strcat(path, "/boxcards");
        infile.open(path);
        if (!infile.fail()) {
            learnc_restore_boxes(gtk_data->data.boxes, infile, gtk_data->data.stack);
            infile.close();
        }
    }
    else {
        cerr << "learnc_gtk_open_cb: Received failure on learnc_get_storage_path().\n";
    }

    if (learnc_get_storage_path(gtk_data->file_name, path) == 1) {
        strcat(path, "/knowncards");
        infile.open(path);
        if (!infile.fail()) {
            learnc_restore_known(gtk_data->data.known, infile, gtk_data->data.stack);
            infile.close();
        }
    }
    else {
        cerr << "learnc_gtk_open_cb: Received failure on learnc_get_storage_path().\n";
    }

    gtk_widget_destroy(file_dialog);

    review_state = OUT_REVIEW;

}

extern "C"
void learnc_gtk_save_cb(gtk_instance *gtk_data)
{
    if (gtk_data == NULL) {
        cerr << "learnc_gtk_save_cb: Received NULL on gtk_data.\n";
        return;
    }

    if (gtk_data->data.boxes == NULL) {
        cerr << "learnc_gtk_save_cb: Boxes is uninitialized.\n";
        return;
    }
    else if (gtk_data->data.known == NULL) {
        cerr << "learnc_gtk_save_cb: Known is uninitialized.\n";
        return;
    }

    ofstream outfile;
    char path[PATH_MAX];

    if (learnc_get_storage_path(gtk_data->file_name, path) == 1) {
        strcat(path, "/boxcards");
        outfile.open(path);
    }
    else {
        cerr << "learnc_gtk_save_cb: Received failure on learnc_get_storage_path().\n";
        return;
    }

    if (learnc_save_boxes(gtk_data->data.boxes, outfile) == 0) {
        cerr << "learnc_gtk_save_cb: Encountered problem with boxes pointer in "
             << "learnc_save_boxes().\n";
    }
    outfile.close();

    if (learnc_get_storage_path(gtk_data->file_name, path) == 1) {
        strcat(path, "/knowncards");
        outfile.open(path);
    }
    else {
        cerr << "learnc_gtk_save_cb: Received failure on learnc_get_storage_path().\n";
        return;
    }
    if (learnc_save_box(gtk_data->data.known, outfile) == 0) {
        cerr << "learnc_gtk_save_cb: Encountered problem with boxes pointer in "
             << "learnc_save_box().\n";
    }

    outfile.close();
}



extern "C"
void learnc_gtk_view_boxes_cb(gtk_instance *gtk_data)
{
    if (review_state != OUT_REVIEW) {
        return;
    }

    learnc_html_view_boxes(gtk_data->data);
    webkit_web_view_reload(gtk_data->webview);

}

extern "C"
void learnc_gtk_cut_cb(gtk_instance *gtk_data)
{
    GtkWidget *widget = gtk_window_get_focus(GTK_WINDOW(gtk_data->window));

    if (WEBKIT_IS_WEB_VIEW(widget)) {
        webkit_web_view_copy_clipboard(WEBKIT_WEB_VIEW(widget));
    }
    else if (GTK_IS_LABEL(widget) && gtk_label_get_selectable(GTK_LABEL(widget))) {
        g_signal_emit_by_name(widget, "copy-clipboard", NULL);
    }
    else if (GTK_IS_ENTRY(widget) || GTK_IS_TEXT_VIEW(widget)) {
        g_signal_emit_by_name(widget, "cut-clipboard", NULL);
    }
}

extern "C"
void learnc_gtk_copy_cb(gtk_instance *gtk_data)
{
    GtkWidget *widget = gtk_window_get_focus(GTK_WINDOW(gtk_data->window));

    if (WEBKIT_IS_WEB_VIEW(widget)) {
        webkit_web_view_copy_clipboard(WEBKIT_WEB_VIEW(widget));
    }
    else if ((GTK_IS_LABEL(widget) && gtk_label_get_selectable(GTK_LABEL(widget)))
             || GTK_IS_ENTRY(widget) || GTK_IS_TEXT_VIEW(widget)) {
        g_signal_emit_by_name(widget, "copy-clipboard", NULL);
    }
}

extern "C"
void learnc_gtk_paste_cb(gtk_instance *gtk_data)
{
    GtkWidget *widget = gtk_window_get_focus(GTK_WINDOW(gtk_data->window));

    if (GTK_IS_ENTRY(widget) || GTK_IS_TEXT_VIEW(widget)) {
        g_signal_emit_by_name(widget, "paste-clipboard", NULL);
    }
}

extern "C"
void learnc_gtk_delete_cb(gtk_instance *gtk_data)
{
    GtkWidget *widget = gtk_window_get_focus(GTK_WINDOW(gtk_data->window));

    if (GTK_IS_ENTRY(widget) || GTK_IS_TEXT_VIEW(widget)) {
        g_signal_emit_by_name(widget, "delete-from-cursor", NULL);
    }
}

extern "C"
void learnc_gtk_about_cb(gtk_instance *gtk_data)
{
/*    gtk_dialog_run(GTK_DIALOG(gtk_data->about));
      gtk_widget_hide(gtk_data->about); */

    const gchar *auth[] = { "Steven Williams <theblessedadventhope@gmail.com>", NULL };

/*
    static GtkWidget *dialog = NULL;

    if (!dialog) {
        GtkAboutDialog *about;


        dialog = gtk_about_dialog_new();
        gtk_window_set_transient_for(GTK_WINDOW(dialog),
                                     GTK_WINDOW(gtk_data->window));
        about = GTK_ABOUT_DIALOG(dialog);

        gtk_about_dialog_set_program_name(about, "Learncurve");
        gtk_about_dialog_set_version(about, "0.1");

        gtk_widget_show_all(dialog);
    }

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_hide(dialog); */

    gtk_show_about_dialog(GTK_WINDOW(gtk_data->window),
                          "program-name", "Learncurve",
                          "version", "0.2-rc",
                          "copyright", "Copyright 2013 Steven Williams",
                          "website", "http://learncurve.sourceforge.net",
                          "authors", auth,
                          NULL);
}

// input is our way of sharing text collected from the
// text entry box with review in its different phases

static vector<std::string> input;

// learnc_gtk_text_entry_cb will pass text straight
// to the review function when we are not in a review
// session, but when we are it will just push that text
// onto input and not send it leaving the learnc_gtk
// _button_done_cb to handle sending our data when we
// are finished.
//
// returns nothing
// takes a pointer to GtkWidget for the text entry box
// and our gtk_instance for other necessary odds and ends

extern "C"
void learnc_gtk_text_entry_cb(GtkWidget *entry, gtk_instance *gtk_data)
{

    string buffer;

    if (review_state != IN_REVIEW) {
        input.clear();
    }

    buffer = gtk_entry_get_text(GTK_ENTRY(entry));
    input.push_back(buffer);

    if (review_state == MENU_REVIEW) {
        learnc_review_control(gtk_data->data, input, review_state);
        webkit_web_view_reload(gtk_data->webview);
        input.clear();
    }

    gtk_entry_set_text(GTK_ENTRY(entry), "");
}

// learnc_gtk_button_done_cb controls the button clicked signal
// but it helps us keep multiple text entries seperated until
// we are ready to send them.
//
// returns nothing
// takes pointer to GtkWidget as first argument for passing button
// and gtk_instance for page loading

extern "C"
void learnc_gtk_button_done_cb(GtkWidget *button, gtk_instance *gtk_data)
{
    static int flag;

    if (flag == 0 && review_state == IN_REVIEW) {
        flag = 1;
        gtk_button_set_label(GTK_BUTTON(button), "Next");
    }
    else if (flag == 1 && review_state == IN_REVIEW) {
        flag = 0;
        gtk_button_set_label(GTK_BUTTON(button), "Done");
    }

    if (review_state == IN_REVIEW) {
        learnc_review_control(gtk_data->data, input, review_state);
        webkit_web_view_reload(gtk_data->webview);
        if (review_state != IN_REVIEW) {
            gtk_button_set_label(GTK_BUTTON(button), "Done");
            flag = 0;
        }
        input.clear();
    }

}

extern "C"
void learnc_gtk_review_cb(gtk_instance *gtk_data)
{
    if (review_state == OUT_REVIEW) {
        learnc_review_control(gtk_data->data, input, review_state);
        webkit_web_view_reload(gtk_data->webview);
    }
}
