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
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <sys/stat.h>
#include "types.h"
#include "save_restore.h"

using namespace std;

// save_restore.cpp contains the functions that deal with saving and resuming
// your progress in the box system.

// learnc_save_box takes the numbers of the cards inside the box and writes
// them out to a file
// 
// returns 0 for failure and 1 for success
// takes a pointer to box for the box it is going to save and an ofstream
// object that is passed by reference to write out the numbers with.

int learnc_save_box(box *box_to_save, std::ofstream &fout)
{
    if (box_to_save == NULL)
        return 0;

    unsigned int i;

    for (i = 0; i < box_to_save->stack.size(); i++)
        fout << box_to_save->stack[i]->number << "\n";

    return 1;
}

// learnc_save_boxes saves all of the boxes into one file. It is assisted
// by learnc_save_box. This is done by writing out the integers after a line
// containing a code like "B3#" which stands for Box number 3.
//
// returns 0 for failure and 1 for success
// takes a pointer to box that contains the initial address for all the boxes
// and a ofstream object passed by reference that all of the boxes data is written
// out to.

int learnc_save_boxes(box *boxes, std::ofstream &fout)
{
    if (boxes == NULL)
        return 0;

    int i;
    for (i = 0; i < 5; i++) {
        fout << "B" << i+1 << "#\n";
        learnc_save_box(boxes+i, fout);
    }

    return 1;
}

// learnc_restore_box restores a single box's progress from a list of integers
// that are the card numbers it held last time. These numbers are read from the
// file that was written out earlier.
//
// returns 1, but should have some way of checking for failure
// takes a vector of ints that is passed by reference for storage and an
// ifstream object passed by reference for reading from the storage file.

int learnc_restore_box(std::vector<int> &card_numbers, std::ifstream &fin)
{
    string buf;
    int i;

    while (!fin.eof()) {
        getline(fin, buf);
        if (buf.find_first_not_of("0123456789") != string::npos) {
            break;
        }
        istringstream ss(buf);
        ss >> i;
        card_numbers.push_back(i);
    }

    return 1;
}

// learnc_restore_known puts back all the pointers to the cards that were in known
// before the program closed last time. It does this by getting the integers from a
// file just for known and loading the pointers back in from the stack after it finds
// the cards that match.
//
// returns 0 for failure and 1 for success
// takes a pointer to box for known, an ifstream object to read the file, and a vector
// of voc_card passed by reference that is the stack of an instance.

int learnc_restore_known(box *known, std::ifstream &fin, std::vector<voc_card> &stack)
{
    if (known == NULL)
        return 0;

    unsigned int i;
    int address;
    vector<int> card_numbers;

    learnc_restore_box(card_numbers, fin);
    for (i = 0; i < card_numbers.size(); i++) {
        address = learnc_find_in_stack(card_numbers[i], stack);
        if (address != -1) {
            known->stack.push_back(&stack[address]);
        }
    }

    return 1;
}

// learnc_restore_boxes brings back the progress for all of the boxes back into the program.
//
// returns 0 for failure and 1 for success
// takes a pointer to box for the initial address of all the boxes, an ifstream object
// passed by reference to read the file back in, and a vector of voc_card passed by
// reference that is the stack of an instance.

int learnc_restore_boxes(box *boxes, std::ifstream &fin, std::vector<voc_card> &stack)
{
    if (boxes == NULL)
        return 0;

    unsigned int i = 0, j;
    int address;
    string temp;
    vector<int> card_numbers;


    getline(fin, temp);
    while (i < 5) {
        learnc_restore_box(card_numbers, fin);
        if (!(card_numbers.empty())) {
            for (j = 0; j < card_numbers.size(); j++) {
                address = learnc_find_in_stack(card_numbers[j], stack);
                if (address != -1 && (int) (boxes+i)->stack.size() < (boxes+i)->size)
                    (boxes+i)->stack.push_back(&stack[address]);
            }
            card_numbers.clear();
        }
        ++i;
    }



    return 1;
}

// learnc_find_in_stack finds where a card is located in the stack.
// It does this by the card's number which it looks for in the stack.
// When it is found, it returns the integer value of the index it
// found the card at.
//
// returns -1 for error or failure to find and 0 and any positive
// integer for the index of the card's position in the stack.
// takes an integer for the card number it is looking for, and a
// vector of voc_cards or voc_card pointers passed by reference to
// look for the card in.

int learnc_find_in_stack(int number, std::vector<voc_card> &stack)
{
    if (number <= 0)
        return -1;

    unsigned int i;

    for (i = 0; i < stack.size(); i++)
        if (stack[i].number == number)
            return i;

    return -1;
}

int learnc_find_in_stack(int number, std::vector<voc_card *> &stack)
{
    if (number <= 0)
        return -1;

    unsigned int i;

    for (i = 0; i < stack.size(); i++)
        if (stack[i]->number == number)
            return i;

    return -1;
}

// learnc_get_storage_path takes the filename of the card XML file
// and uses it to determine what the directory name should be to
// store our progress.
//
// returns 0 for failure and 1 for success
// takes two pointers to char, the first for the filename of the
// XML file, and the second for the directory name it will be giving
// back.

int learnc_get_storage_path(const char *filename, char *dirname)
{
    char buf[PATH_MAX];
    char *file_begin;
    char *last_pos;

    if (filename == NULL || dirname == NULL)
        return 0;

    strncpy(buf, filename, strlen(filename));
    buf[strlen(filename)] = '\0';
    file_begin = strstr(buf, ".xml");

    while (file_begin != NULL) {
        last_pos = file_begin;
        file_begin = strstr(file_begin+1, ".xml");
    }

    while (*last_pos != '\0') {
        *last_pos = '\0';
        last_pos++;
    }

    file_begin = strstr(buf, "/");
    while (file_begin != NULL) {
        last_pos = file_begin;
        file_begin = strstr(file_begin+1, "/");
    } 

    file_begin = getenv("XDG_DATA_HOME");
    if (file_begin != NULL) {
        strncpy(dirname, file_begin, PATH_MAX);
        strncat(dirname, "/learncurve", PATH_MAX);
        strncat(dirname, last_pos, PATH_MAX);
    }
    else {
        file_begin = getenv("HOME");
        if (file_begin != NULL) {
            strncpy(dirname, file_begin, PATH_MAX);
            strncat(dirname, "/learncurve", PATH_MAX);
            strncat(dirname, last_pos, PATH_MAX);
        }
        else {
            cerr << "learnc_get_storage_path: Encountered a problem with getenv().\n";
            return 0;
        }
    }

    return 1;
}

// learnc_make_storage_directory does as the name implies; it makes a storage
// directory. It is POSIX specific as of 4-18-13.
//
// returns 0 for failure and 1 for success
// takes a pointer to char that is meant to contain the filename of the XML file
// we read our cards from.

int learnc_make_storage_directory(const char *filename)
{
    if (filename == NULL) {
        cerr << "learnc_make_storage_directory:"
                  << " received NULL pointer for filename.\n";
        return 0;
    }

    char buf[PATH_MAX];
    struct stat st = {0};

    learnc_get_storage_path(filename, buf);
    if (stat(buf, &st) == -1) {
        mkdir(buf, 0700);
    }

    return 1;
}
