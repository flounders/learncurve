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

#ifndef INITIALIZE_H_
#define INITIALIZE_H_

#ifdef _WIN32 || _WIN64
#include <direct.h>
#include <sys/types.h>
#include <sys/stat.h>
#else
#include <sys/stat.h>
#endif

#include "types.h"

int learnc_init_charset(char *charset);
int learnc_init_chset_setloc(int property, char *charset);
int learnc_init_box(box *boxvar, int number);
int learnc_init_boxes(box **boxes);
int learnc_init_storage(void);
int learnc_init_win32_storage(void);
int learnc_init_win64_storage(void);
int learnc_init_linux_storage(void);
int learnc_init_macosx_storage(void);
void learnc_init_instance(instance &data);

#define BOX1_SIZE 10
#define BOX2_SIZE 20
#define BOX3_SIZE 30
#define BOX4_SIZE 50
#define BOX5_SIZE 80

#endif
