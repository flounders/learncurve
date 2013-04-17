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

struct voc_card {
    int number;
    std::vector<std::string> front;
    std::vector<std::string> back;
};

struct box {
    int size;
    std::vector<voc_card *> stack;
};

struct instance {
    std::vector<voc_card> stack;
    box *boxes;
    box *known;
};

#endif
