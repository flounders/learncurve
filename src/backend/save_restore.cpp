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

int learnc_save_box(box *box_to_save, std::ofstream &fout)
{
    if (box_to_save == NULL)
        return 0;

    int i;

    for (i = 0; i < box_to_save->stack.size(); i++)
        fout << box_to_save->stack[i]->number << "\n";

    return 1;
}

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

int learnc_restore_box(std::vector<int> &card_numbers, std::ifstream &fin)
{
    std::string buf;
    int i;

    while (!fin.eof()) {
        getline(fin, buf);
        if (buf.find_first_not_of("0123456789") == std::string::npos)
            return 1;
        std::istringstream ss(buf);
        ss >> i;
        card_numbers.push_back(i);
    }

    return 1;
}

int learnc_restore_known(box *known, std::ifstream &fin, std::vector<voc_card> &stack)
{
    if (known == NULL)
        return 0;

    int i;
    int address;
    std::vector<int> card_numbers;

    learnc_restore_box(card_numbers, fin);
    for (i = 0; i < card_numbers.size(); i++) {
        address = learnc_find_in_stack(card_numbers[i], stack);
        if (address != 0) {
            known->stack.push_back(&stack[address]);
        }
    }

    return 1;
}

int learnc_restore_boxes(box *boxes, std::ifstream &fin, std::vector<voc_card> &stack)
{
    if (boxes == NULL)
        return 0;

    int i = 0;
    int j, address;
    std::string temp;
    std::vector<int> card_numbers;


    getline(fin, temp);
    while (i < 5) {
        learnc_restore_box(card_numbers, fin);
        for (j = 0; j < card_numbers.size(); j++) {
            address = learnc_find_in_stack(card_numbers[j], stack);
            if (address != 0 && (boxes+i)->stack.size() < (boxes+i)->size)
                (boxes+i)->stack.push_back(&stack[address]);
        }
        card_numbers.clear();
        ++i;
    }

    return 1;
}

int learnc_find_in_stack(int number, std::vector<voc_card> &stack)
{
    if (number <= 0)
        return -1;

    int i;

    for (i = 0; i < stack.size(); i++)
        if (stack[i].number == number)
            return i;

    return -1;
}

int learnc_find_in_stack(int number, std::vector<voc_card *> &stack)
{
    if (number <= 0)
        return 0;

    int i;

    for (i = 0; i < stack.size(); i++)
        if (stack[i]->number == number)
            return i;

    return 0;
}

int learnc_get_storage_path(char *filename, char *dirname)
{
    char buf[PATH_MAX];
    char *file_begin;
    char *last_pos;

    if (filename == NULL || dirname == NULL)
        return 0;

    strncpy(buf, filename, strlen(filename) - 4);
    buf[strlen(filename) - 4] = '\0';


    file_begin = strchr(buf, '/');
    while ((file_begin = strchr(file_begin+1, '/')) != NULL) {
        if (file_begin == NULL)
            break;

        last_pos = file_begin;
    } 
    last_pos++;


    file_begin = getenv("HOME");
    if (file_begin != NULL) {
        snprintf(buf, sizeof (buf), "%s/.config/learncurve/%s", file_begin, last_pos);
    }
    else {
        std::cerr << "learnc_get_storage_path: Encountered a problem with getenv().\n";
        return 0;
    }

    strcpy(dirname, buf);

    return 1;
}

int learnc_make_storage_directory(char *filename)
{
    if (filename == NULL) {
        std::cerr << "learnc_make_storace_directory:"
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
