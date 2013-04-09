#ifndef BOXES_H_
#define BOXES_H_

#include "types.h"

int learnc_is_in_boxes(int number, box *boxes, box *known);
int learnc_box_promote(box *box1, box *box2, voc_card *card);
int learnc_load_box(box *dest, instance *current);

#endif
