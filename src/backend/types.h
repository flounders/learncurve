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

#ifndef TYPES_H_
#define TYPES_H_
#include <string>
#include <vector>

#define MAX_BOXES 5

// number is what holds the card number and is important as
// our identifier for each card.
// The vectors of strings front and back deal with the
// content that would be on the front and back of a 3"x5"
// index card, but is not limited to the amount of information
// a 3"x5" can hold. Though it is recommended you keep it to
// a minimum.

struct voc_card {
    int number;
    std::vector<std::string> front;
    std::vector<std::string> back;
};

// box is our representation of a box in Leitner's system.
// size is what restricts how many cards go in the box
// and is set by the learnc_init_box function.
// The stack is what holds our cards and rather than making
// copies and increasing the memory profile significantly
// it holds pointers instead.

struct box {
    int size;
    std::vector<voc_card *> stack;
};

// instance is an organized way of passing the cards and
// boxes.
// stack is what holds the originals of our cards.
// boxes and known are pointers that will be initialized
// later. boxes is meant to point to 5 box elements.

struct instance {
    std::vector<voc_card> stack;
    box *boxes;
    box *known;
};

#endif
