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
#include "save_restore.h"
#include "types.h"

int learnc_is_in_boxes(int number, box *boxes, box *known)
{
    int i, j;

    if (boxes == NULL || known == NULL) {
        std::cerr << "learnc_is_in_boxes: Received NULL pointer.\n";
        return -1;
    }

    for (i = 0; i < 5; i++) {
        for (j = 0; j < (boxes+i)->stack.size(); j++) {
            if ((boxes+i)->stack[j]->number == number) {
                return 1;
            }
        }
    }

    for (j = 0; j < known->stack.size(); j++) {
        if (known->stack[j]->number == number) {
            return 1;
        }
    }

    return 0;
}

int test_is_in_boxes(void)
{
    instance data;

    return 1;
}

int learnc_box_promote(box *box1, box *box2, voc_card *card)
{
    int i;

    if (card == NULL || box1 == NULL || box2 == NULL) {
        return 0;
    }

    i = learnc_find_in_stack(card->number, box1->stack);
    if (i >= 0) {
        box2->stack.push_back(card);
        box1->stack.erase(box1->stack.begin()+i);
    }
    else {
        return 0;
    }

    return 1;
}

int learnc_load_box(box *dest, instance *current)
{
    int i, status;

    if (dest == NULL || current == NULL)
        return 0;

    for (i = 0; i < current->stack.size() && dest->stack.size() < dest->size; i++) {
        status = learnc_is_in_boxes(current->stack[i].number, current->boxes, current->known);
        if (status == 0) {
            dest->stack.push_back(&(current->stack[i]));
        }
        else if (status == 1) {
            ;
        }
    }

    return 1;
}
