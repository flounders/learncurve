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
