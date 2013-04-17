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
#include <clocale>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include "types.h"
#include "initialize.h"

int learnc_init_charset(char *charset)
{
    int properties[5] = {LC_ALL, LC_CTYPE, LC_MESSAGES,
                         LC_COLLATE, LC_NUMERIC};
    int i = 0;
    int errorcode;

    if (charset == NULL)
        return 0;

    while (i < 5) {
        errorcode = learnc_init_chset_setloc(properties[i], charset);
        if (errorcode == 0)
            return 0;
        ++i;
    }

    return 1;
}

int learnc_init_chset_setloc(int property, char *charset)
{
    char *p;

    if (charset == NULL)
        return 0;

    p = setlocale(property, charset);
    if (p == NULL)
        return 0;

    return 1;
}

int learnc_init_box(box *boxvar, int number)
{
    if (boxvar == NULL) {
        std::cerr << "learnc_init_box: boxvar is NULL.\n";
        return 0;
    }

    if (number < 1 || number > 5) {
        return 0;
    }

    if (number == 1) {
        boxvar->size = BOX1_SIZE;
    }
    else if (number == 2) {
        boxvar->size = BOX2_SIZE;
    }
    else if (number == 3) {
        boxvar->size = BOX3_SIZE;
    }
    else if (number == 4) {
        boxvar->size = BOX4_SIZE;
    }
    else if (number == 5) {
        boxvar->size = BOX5_SIZE;
    }

    boxvar->stack.clear();

    return 1;
}

int learnc_init_boxes(box **boxes)
{
    int i, status;

    *boxes = new box[MAX_BOXES];
    
    for (i = 0; i < MAX_BOXES; i++) {
        status = learnc_init_box((*boxes+i), i+1);
        if (status == 0) {
            std::cerr << "learnc_init_boxes: Encountered error with learnc_init_box().\n";
            return 0;
        }
    }

    return 1;
}

int learnc_init_linux_storage(void)
{
    struct stat st = {0};
    char path[PATH_MAX];
    char *home = getenv("HOME");

    if (home != NULL)
        snprintf(path, PATH_MAX, "%s/.config/learncurve", home);

    if (stat(path, &st) == -1) {
        return !(mkdir(path, 0700));
    }

    return 1;
}

void learnc_init_instance(instance &data)
{
    data.stack.clear();
    learnc_init_boxes(&data.boxes);
    data.known = new box;
    data.known->size = 0;
}
