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

        review_state = IN_REVIEW;
        return 1;

        break;
    case IN_REVIEW:
/*        if (current_box < 4) {
            if (((data->boxes)+current_box)->stack.size() == 0 || ((data->boxes)+current_box+1)->stack.size() == data->boxes+current_box+1->size) {
                review_state = OUT_REVIEW;
                return 1;
            }
        }
        else if (current_box == 4) {
            if (((data->boxes)+current_box)->stack.size() == 0) {
                review_state = OUT_REVIEW;
                return 1;
            }
            // keep going
            } */
        review_state = OUT_REVIEW;
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
