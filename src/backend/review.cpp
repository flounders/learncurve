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

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "boxes.h"
#include "htmlgen.h"
#include "review.h"
#include "types.h"

static int current_box;

int learnc_review_control(instance &data, std::vector<std::string> input, std::string &page, int &review_state)
{
    int address = 0;
//    int i;

    if (data.boxes == NULL || data.known == NULL) {
        return 0;
    }
    if (data.stack.empty()) {
        return 0;
    }

    switch (review_state) {
    case OUT_REVIEW:
        learnc_html_review_menu(page);
        review_state = MENU_REVIEW;
        input.clear();
        return 1;
        break;
    case MENU_REVIEW:
        if (input.size() == 0) {
            learnc_html_input_usage(page, "Enter a single digit from 1-5.");
            return 0;
        }
        else if (input.size() > 0) {
            if (input[0].find_first_not_of("12345") == std::string::npos) {
                std::istringstream convert(input[0]);
                convert >> address;
                if (address < 1 || address > 5) {
                    learnc_html_input_usage(page, "Enter a single digit from 1-5.");
                    return 0;
                }
                else if (address != 0) {
                    current_box = address - 1;
                }
            }
            else {
                learnc_html_input_usage(page, "Enter a single digit from 1-5.");
                std::cerr << "learnc_review_control: Invalid menu choice string.\n";
                return 0;
            }
    
            if (address == 0) {
                learnc_html_input_usage(page, "Enter a single digit from 1-5.");
                return 0;
            }
            else {
                std::cerr << "learnc_review_control: address = " << address
                          << std::endl;
            }
        }

        if (current_box == 0) {
            learnc_load_box(data.boxes, &data);
            learnc_html_card_front(*(data.boxes->stack[0]), page);
        }
        else {
            learnc_html_card_front(*(((data.boxes)+current_box)->stack[0]), page);
        }

        review_state = IN_REVIEW;
        return 1;

        break;
    case IN_REVIEW:
        static int check_state;
        int answer;
        if (current_box < 4) {
            if (((data.boxes)+current_box)->stack.empty()|| ((data.boxes)+current_box+1)->stack.size() == ((data.boxes)+current_box+1)->size) {
                review_state = OUT_REVIEW;
                return 1;
            }
            else if (check_state == 0) {
                answer = learnc_review_check_answer(input, ((data.boxes)+current_box)->stack[0]->back);
                std::cout << "Anwser was " << answer << std::endl;
                learnc_html_card_back_and_front(*(((data.boxes)+current_box)->stack[0]), page);
                if (answer == 1) {
                    learnc_box_promote((data.boxes)+current_box, (data.boxes)+current_box+1, ((data.boxes)+current_box)->stack[0]);
                }
                else if (answer == 0) {
                    ((data.boxes)+current_box)->stack.erase(((data.boxes)+current_box)->stack.begin());
                }
                check_state = 1;
            }
            else if (check_state == 1) {
                learnc_html_card_front(*(((data.boxes)+current_box)->stack[0]), page);
                check_state = 0;
            }
        }
        else if (current_box == 4) {
            if (((data.boxes)+current_box)->stack.empty()) {
                review_state = OUT_REVIEW;
                return 1;
            }
            else if (check_state == 0) {
                answer = learnc_review_check_answer(input, ((data.boxes)+current_box)->stack[0]->back);
                learnc_html_card_back_and_front(*(((data.boxes)+current_box)->stack[0]), page);
                if (answer == 1) {
                    learnc_box_promote((data.boxes)+current_box, data.known, ((data.boxes)+current_box)->stack[0]);
                }
                else if (answer == 0) {
                    ((data.boxes)+current_box)->stack.erase(((data.boxes)+current_box)->stack.begin());
                }
                check_state = 1;
            }
            else if (check_state == 1) {
                learnc_html_card_front(*(((data.boxes)+current_box)->stack[0]), page);
                check_state = 0;
            }
            // keep going
        }
        break; 
    }

    return 0;
}

int learnc_review_check_answer(const std::vector<std::string> userinput, const std::vector<std::string> cardinput)
{
    int i, j;
    int rightcount = 0;

    if (userinput.size() != cardinput.size()) {
        return 0;
    }

    for (i = 0; i < userinput.size(); i++) {
        for (j = 0; j < userinput.size(); j++) {
            if (i != j && userinput[i] == userinput[j]) {
                return 0;
            }
        }
    }



    for (i = 0; i < userinput.size(); i++) {
        for (j = 0; j < cardinput.size(); j++) {
            if (userinput[i] == cardinput[j]) {
                rightcount++;
            }
        }
    }

    if (rightcount == cardinput.size()) {
        return 1;
    }

    return 0;
}

int test_review_check_answer(void)
{
    std::vector<std::string> set1;
    std::vector<std::string> set2;
    int returncode = -500;



// test case 1
    set1.push_back("Abraham");
    set1.push_back("Abrah");

    set2.push_back("Abraham");
    set2.push_back("Abrah");



    returncode = learnc_review_check_answer(set1, set2);
    if (returncode == 0) {
        std::cerr << "test_review_check_answer(): learnc_review_check_answer() failed on test case #1.\n";
        return 0;
    }

    set1.clear();



// test case 2
    set1.push_back("Abraham");

    returncode = learnc_review_check_answer(set1, set2);
    if (returncode == 1) {
        std::cerr << "test_review_check_answer(): learnc_review_check_answer() failed on test case #2.\n";
        return 0;
    }

// test case 3
    set1.push_back("Abraham");

    returncode = learnc_review_check_answer(set1, set2);
    if (returncode == 1) {
        std::cerr << "test_review_check_answer(): learnc_review_check_answer() failed on test case #3.\n";
        return 0;
    }

    return 1;
}
