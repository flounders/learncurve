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

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "htmlgen.h"
#include "types.h"

#ifdef __linux__
#define CSS_FILE "/learncurve/program.css"
#endif

#define HTML_DOCTYPE "<!DOCTYPE html>"
#define HTML_OPEN    "<html>"
#define HTML_CLOSE   "</html>"
#define HEAD_OPEN    "<head>"
#define HEAD_CLOSE   "</head>"
#define BODY_OPEN    "<body>"
#define BODY_CLOSE   "</body>"
#define META_CHARSET "<meta charset=\"UTF-8\">\n"

using namespace std;

// htmlgen.cpp deals with generating HTML for the program
// to display its content with.

// learnc_html_welcome_page generates html for the
// opening page when learncurve is launched
//
// returns 1, but should probably be made a void function
// as there are no NULL pointers to check for. Takes
// no arguments.

int learnc_html_welcome_page(void)
{
    ofstream page;

    learnc_html_gen_open(page);

    page << "<div class=\"welcome\">Welcome to Learncurve!</div>";

    learnc_html_gen_close(page);

    return 1;
}

// learnc_html_card_front generates html for the front
// of a card to be reviewed
//
// returns 1, but should probably be made a void function
// as there are no NULL pointers to check for. Takes
// voc_card as argument for content to load on page.

int learnc_html_card_front(voc_card card)
{
    ofstream page;
    int i;

    learnc_html_gen_open(page);

    page << "<div class=\"number\">";
    page << card.number;
    page << "</div><div class=\"front\">";

    for (i = 0; i < card.front.size(); i++) {
        page << "<li>";
        page << card.front[i];
        page << "</li>";
    }
    page << "</div>";

    learnc_html_gen_close(page);

    return 1;
}

// learnc_html_card_back_and_front generates html for the front
// and back of a card to be viewed. This is used for showing
// what was the correct answer.
//
// returns 1, but should probably be made a void function
// as there are no NULL pointers to check for. Takes
// voc_card as argument for content to load on page.

int learnc_html_card_back_and_front(voc_card card, int answer)
{
    int i;
    ofstream page;

    learnc_html_gen_open(page);

    page << "<div class=\"number\">";
    page << card.number;
    page << "</div><div class=\"front\">";

    for (i = 0; i < card.front.size(); i++) {
        page << "<li>";
        page << card.front[i];
        page << "</li>";
    }
    page << "</div>";

    page << "<div class=\"back\">";

    for (i = 0; i < card.back.size(); i++) {
        page << "<li>";
        page << card.back[i];
        page << "</li>";
    }

    page << "</div>";

    page << "<div class=\"answer\">";
    if (answer == 0) {
        page << "Wrong answer!";
    }
    else if (answer == 1) {
        page << "You got it right!";
    }
    page << "</div>";

    learnc_html_gen_close(page);

    return 1;
}

// learnc_html_view_boxes generates html that shows how many
// cards are in the boxes (known included) and generates a 
// graphic as well.
//
// returns 1, but should probably be made a void function
// as there are no NULL pointers to check for. Takes
// an instance passed by reference as an argument to
// retrieve information to display.

int learnc_html_view_boxes(instance &current)
{
    ofstream page;
    int i;

    learnc_html_gen_open(page);

    for (i = 0; i < 5; i++) {
        page << "Box ";
        page << i+1;
        page << ":<dd><div class=\"progress\" style=\"width:";
        page << (current.boxes[i].stack.size() * 100.0) / current.boxes[i].size;
        page << "%;\"></dd>";
        page << (current.boxes[i].stack.size() * 100.0) / current.boxes[i].size;
        page << "%<br>";
    }

    page << "Known:<dd><div class=\"progress\" style=\"width:";
    page << current.known->stack.size() * 100.0 / current.known->size;
    page << "%;\"></dd>";
    page << current.known->stack.size() * 100.0 / current.known->size;
    page << "%<br>";
    
    learnc_html_gen_close(page);

    return 1;
}

// learnc_html_review_menu generates html for the review menu.
// At this point (4-17-13) gives a simple message informing you
// of your options for selection, but should be changed to show
// which boxes you are able to review and which ones you cannot.
//
// returns 1, but should probably be made a void function
// as there are no NULL pointers to check for. Takes
// no arguments.


int learnc_html_review_menu(void)
{

    ofstream page;

    learnc_html_gen_open(page);

    page << "<div>Enter the box number you would like to review.</div>";

    learnc_html_gen_close(page);
    
    return 1;
}

// learnc_html_input_usage generates html to inform the user
// they entered invalid input and what input they can enter.
//
// returns 1, but should probably be made a void function
// as there are no NULL pointers to check for. Takes
// a string passed by value that tells the user what the
// proper usage is.

int learnc_html_input_usage(const std::string usage)
{
    ofstream page;

    learnc_html_gen_open(page);

    page << "<div>Invalid input.</div>";
    page << "<div>Proper input: ";
    page << usage;
    page << "</div>";

    learnc_html_gen_close(page);

    return 1;
}



// learnc_html_gen_open generates html for the other functions for the
// doctype, head section which indicates character set and page sytling
// and finishes with opening the body to our content.
//
// returns 1, but should probably be made a void function
// as there are no NULL pointers to check for. Takes
// an ofstream object passed by reference to write out the content to.

int learnc_html_gen_open(std::ofstream &page)
{
    char *home_config_path;

    home_config_path = getenv("XDG_CONFIG_HOME");

    page.open(OUTPUT_PAGE);

    page << HTML_DOCTYPE;
    page << HTML_OPEN;
    page << HEAD_OPEN;
    page << META_CHARSET;
    page << "<link rel=\"stylesheet\" type=\"text/css\" href=\"";

    if (home_config_path != NULL) {
        page << home_config_path;
    }
    else {
        home_config_path = getenv("HOME");
        page << home_config_path << "/.config";
    }

#ifdef CSS_FILE
    page << CSS_FILE;
#endif

    page << "\">";
    page << HEAD_CLOSE;
    page << BODY_OPEN;

    return 1;
}

// learnc_html_gen_close generates html for the closing section of a page
// after we have inserted our specific content.
//
// returns 1, but should probably be made a void function
// as there are no NULL pointers to check for. Takes
// an ofstream object passed by reference to write out the content to.

int learnc_html_gen_close(std::ofstream &page)
{
    page << BODY_CLOSE;
    page << HTML_CLOSE;

    page.close();

    return 1;
}
