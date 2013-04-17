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

#ifndef SAVE_RESTORE_H_
#define SAVE_RESTORE_H_

#include <fstream>
#include <vector>
#include "types.h"

int learnc_save_box(box *box_to_save, std::ofstream &fout);
int learnc_save_boxes(box *boxes, std::ofstream &fout);
int learnc_restore_box(std::vector<int> &card_numbers, std::ifstream &fin);
int learnc_restore_known(box *known, std::ifstream &fin, std::vector<voc_card> &stack);
int learnc_restore_boxes(box *boxes, std::ifstream &fin, std::vector<voc_card> &stack);
int learnc_find_in_stack(int number, std::vector<voc_card> &stack);
int learnc_find_in_stack(int number, std::vector<voc_card *> &stack);
int learnc_make_storage_directory(char *filename);
int learnc_get_storage_path(char *filename, char *dirname);

#endif
