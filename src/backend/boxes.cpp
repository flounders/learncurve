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

using namespace std;

// learnc_is_in_boxes tests to see if a specific card is
// in any of the boxes or the known deck that way it doesn't
// test the same card through the system twice.
//
// returns -1 for error, 0 for not present, and 1 for present
// takes an int number to represent the card number being checked
// for and a pointer to the boxes starting with number one and a
// pointer to the known box

int learnc_is_in_boxes(int number, box *boxes, box *known)
{
    int i, j;

    if (boxes == NULL || known == NULL) {
        cerr << "learnc_is_in_boxes: Received NULL pointer.\n";
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

// test_is_in_boxes is incomplete but is meant to make sure
// learnc_is_in_boxes is working.

int test_is_in_boxes(void)
{
    instance data;

    return 1;
}

// learnc_box_promote takes a card that has just been tested
// and the user got the right result, and pushes it up to the
// next box. Thus promoting the card from the box it was in
// to the next box in the system.
//
// returns 0 for failure and 1 for success
// takes two pointers to box one for source the second for
// destination, and it takes a pointer to a voc_card for
// to id the right card

int learnc_box_promote(box *src, box *dest, voc_card *card)
{
    int i;

    if (card == NULL || src == NULL || dest == NULL) {
        return 0;
    }

    i = learnc_find_in_stack(card->number, src->stack);
    if (i >= 0) {
        dest->stack.push_back(card);
        src->stack.erase(src->stack.begin()+i);
    }
    else {
        return 0;
    }

    return 1;
}

// learnc_load_box is used to load typically the first box
// in the system with pointers to cards to be tested on. 
// Could be used on any of the others, but it isn't designed
// for that.
//
// returns 0 for error and 1 for success
// takes a pointer to box for the destination of where to load
// to, and a pointer to the instance to obtain the stack to
// load from

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
