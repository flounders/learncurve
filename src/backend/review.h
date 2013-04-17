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
