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

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "htmlgen.h"
#include "types.h"

#define HTML_DOCTYPE "<!DOCTYPE html>"
#define HTML_OPEN    "<html>"
#define HTML_CLOSE   "</html>"
#define HEAD_OPEN    "<head>"
#define HEAD_CLOSE   "</head>"
#define BODY_OPEN    "<body>"
#define BODY_CLOSE   "</body>"
#define META_CHARSET "<meta charset=\"UTF-8\">\n"

int learnc_html_welcome_page(std::string &page)
{
    learnc_html_gen_open(page);

    page += "<div class=\"welcome\">Welcome to Learncurve!</div>";

    learnc_html_gen_close(page);

    return 1;
}

int learnc_html_card_front(voc_card card, std::string &page)
{
    std::ostringstream convert;
    int i;

    learnc_html_gen_open(page);

    page += "<div class=\"number\">";
    convert << card.number;
    page += convert.str();
    page += "</div><div id=front>";

    for (i = 0; i < card.front.size(); i++) {
        page += "<li>";
        page += card.front[i];
        page += "</li>";
    }
    page += "</div>";

    learnc_html_gen_close(page);

    return 1;
}

int learnc_html_card_back_and_front(voc_card card, std::string &page)
{
    int i;

    learnc_html_card_front(card, page);

    learnc_html_remove_close(page);

    page += "<div class=\"back\">";

    for (i = 0; i < card.back.size(); i++) {
        page += "<li>";
        page += card.back[i];
        page += "</li>";
    }

    page += "</div>";

    learnc_html_gen_close(page);

    return 1;
}

int learnc_html_view_boxes(instance &current, std::string &page)
{
    std::ostringstream convert;
    int i;

    learnc_html_gen_open(page);

    for (i = 0; i < 5; i++) {
        page += "Box ";
        convert << i+1;
        page += convert.str();
        convert.str("");
        page += ":<dd><div class=\"progress\" style=\"width:";
        convert << (current.boxes[i].stack.size() / current.boxes[i].size) * 100.0;
        page += convert.str();
        page += "%;\"></dd>";
        page += convert.str();
        page += "%<br>";
        convert.str("");
    }

    page += "Known:<dd><div class=\"progress\" style=\"width:";
    convert << current.known->stack.size() / current.known->size * 100.0;
    page += convert.str();
    page += "%;\"></dd>";
    page += convert.str();
    page += "%<br>";
    
    learnc_html_gen_close(page);

    return 1;
}

int learnc_html_review_menu(std::string &page)
{
    learnc_html_gen_open(page);

    page += "<div>Enter the box number you would like to review.</div>";

    learnc_html_gen_close(page);

    return 1;
}

int learnc_html_input_usage(std::string &page, const std::string usage)
{
    learnc_html_gen_open(page);

    page += "<div>Invalid input.</div>";
    page += "<div>Proper input: ";
    page += usage;
    page += "</div>";

    learnc_html_gen_close(page);

    return 1;
}

int learnc_html_gen_open(std::string &page)
{
    std::ifstream css_file;
    std::string buf;

    css_file.open("/home/swilliams/workspace/learncurve++/src/backend/program.css");

    page = HTML_DOCTYPE;
    page += HTML_OPEN;
    page += HEAD_OPEN;
    page += META_CHARSET;
    page += "<style>\n";
    while (!css_file.eof()) {
        getline(css_file, buf);
        page += buf;
        page += '\n';
    }
    page += "</style>\n";
    page += HEAD_CLOSE;
    page += BODY_OPEN;

    css_file.close();

    return 1;
}

int learnc_html_gen_close(std::string &page)
{
    page += BODY_CLOSE;
    page += HTML_CLOSE;

    return 1;
}

int learnc_html_remove_close(std::string &page)
{
    std::string ext = HTML_CLOSE;

    if (page.size() > ext.size() &&
        page.substr(page.size() - ext.size()) == HTML_CLOSE) {

        page = page.substr(0, page.size() - ext.size());
    }

    ext = BODY_CLOSE;
    if (page.size() > ext.size() &&
        page.substr(page.size() - ext.size()) == BODY_CLOSE) {

        page = page.substr(0, page.size() - ext.size());
    }

    return 1;
}
