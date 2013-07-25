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

#ifndef HTMLGEN_H_
#define HTMLGEN_H_

#include "types.h"

#ifdef __linux__
#define OUTPUT_PAGE     "/tmp/page.html"
#define OUTPUT_PAGE_URI "file:///tmp/page.html"
#endif

int learnc_html_card_front(voc_card card);
int learnc_html_card_back_and_front(voc_card card, int answer);
int learnc_html_welcome_page(void);
int learnc_html_view_boxes(instance &current);
int learnc_html_review_menu(void);
int learnc_html_input_usage(const std::string usage);
int learnc_html_gen_open(std::ofstream &page);
int learnc_html_gen_close(std::ofstream &page);

#endif
