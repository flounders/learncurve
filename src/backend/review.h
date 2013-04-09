#ifndef REVIEW_H_
#define REVIEW_H_

#include <string>
#include <vector>
#include "types.h"

#define IN_REVIEW   100
#define OUT_REVIEW  200
#define MENU_REVIEW 300

int learnc_review_control(instance &data, std::vector<std::string> input, std::string &page, int &review_state);
int learnc_review_check_answer(std::vector<std::string> userinput, std::vector<std::string> cardinput);
int test_review_check_answer(void);

#endif
