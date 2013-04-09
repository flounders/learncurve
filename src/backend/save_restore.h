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
