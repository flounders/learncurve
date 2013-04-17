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

#ifndef BOXES_H_
#define BOXES_H_

#include "types.h"

int learnc_is_in_boxes(int number, box *boxes, box *known);
int learnc_box_promote(box *box1, box *box2, voc_card *card);
int learnc_load_box(box *dest, instance *current);

#endif
