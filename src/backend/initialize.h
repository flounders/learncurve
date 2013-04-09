#ifndef INITIALIZE_H_
#define INITIALIZE_H_

#include "types.h"

int learnc_init_charset(char *charset);
int learnc_init_chset_setloc(int property, char *charset);
int learnc_init_box(box *boxvar, int number);
int learnc_init_boxes(box **boxes);
int learnc_init_linux_storage(void);

#define BOX1_SIZE 10
#define BOX2_SIZE 20
#define BOX3_SIZE 30
#define BOX4_SIZE 50
#define BOX5_SIZE 80

#endif
