#ifndef HTMLGEN_H_
#define HTMLGEN_H_

#include "types.h"

int learnc_html_card_front(voc_card card, std::string &page);
int learnc_html_card_back_and_front(voc_card card, std::string &page);
int learnc_html_welcome_page(std::string &page);
int learnc_html_view_boxes(instance &current, std::string &page);
int learnc_html_review_menu(std::string &page);
int learnc_html_input_usage(std::string &page, const std::string usage);
int learnc_html_gen_open(std::string &page);
int learnc_html_gen_close(std::string &page);
int learnc_html_remove_close(std::string &page);

#endif
