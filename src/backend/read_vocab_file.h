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

#ifndef READ_VOCAB_FILE_H_
#define READ_VOCAB_FILE_H_

#include <string>
#include <vector>
#include <libxml/xmlreader.h>
#include "types.h"

#define CARD 101
#define NUMBER 102
#define FRONT 103
#define BACK 104
#define SUB 105
#define ROOT 106

int learnc_parse_file(xmlTextReaderPtr reader, std::vector<voc_card> &stack);
int test_parse_file(void);
int learnc_element_check(xmlTextReaderPtr reader);
void learnc_card_clear(voc_card &card);

#endif
