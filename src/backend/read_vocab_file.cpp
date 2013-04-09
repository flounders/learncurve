#include <cstring>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <libxml/xmlreader.h>
#include "types.h"
#include "read_vocab_file.h"

int learnc_parse_file(xmlTextReaderPtr reader, std::vector<voc_card> &stack)
{
    if (reader == NULL)
        return 0;

    short state = 0;
    std::string buf;
    char *ptr;
    voc_card tmp;

    while (xmlTextReaderRead(reader)) {
        switch (learnc_element_check(reader)) {
        case ROOT:
        case CARD:
            if (state == 0)
                learnc_card_clear(tmp);
            else {
                stack.push_back(tmp);
                learnc_card_clear(tmp);
            }
            break;
        case NUMBER:
            xmlTextReaderRead(reader);
            tmp.number = atoi((char *) xmlTextReaderConstValue(reader));
            break;
        case FRONT:
            state = FRONT;
            break;
        case BACK:
            state = BACK;
            break;
        case SUB:
            xmlTextReaderRead(reader);
            ptr = (char *) xmlTextReaderConstValue(reader);
            if (ptr != NULL)
                buf = ptr;
            if (state == FRONT)
                tmp.front.push_back(buf);
            else if (state == BACK)
                tmp.back.push_back(buf);
            break;
        default:
            break;
        }
    }

    stack.push_back(tmp);

    return 1;
}
          
int test_parse_file(void)
{
    const char *testxml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><root><card wordtype=\"noun\"><num>1</num><front><sub case=\"nom\">Abraham</sub></front><back><sub>Abraham</sub></back></card><card wordtype=\"noun\"><num>2</num><front><sub case=\"nom\">Angelos</sub><sub case=\"gen\">Angelou</sub></front><back><sub>angel</sub><sub>messenger</sub></back></card><card><num>3</num><front><sub>amen</sub></front><back><sub>verily</sub><sub>truly</sub><sub>amen</sub><sub>so let it be</sub></back></card></root>";

    xmlTextReaderPtr reader;
    int retval = 0;
    std::vector<voc_card> stack;

    reader = xmlReaderForDoc((xmlChar *) testxml, NULL, NULL, 0);
    if (reader == NULL) {
        std::cerr << "test_parse_file: problem with xmlReaderForDoc\n";
        return 0;
    }

    retval = learnc_parse_file(reader, stack);
    if (retval == 0) {
        std::cerr << "test_parse_file: learnc_parse_file failed on reader\n";
        return 0;
    }

    if (stack.size() == 3) 
        ;
    else {
        std::cerr << "test_parse_file: stack vector unexpected size of "
                  << stack.size() << std::endl;
        for (retval = 0; retval < stack.size(); retval++)
            std::cout << stack[retval].number << std::endl;
        return 0;
    }

    xmlFreeTextReader(reader);
    xmlCleanupParser();

    return 1;
}

int learnc_element_check(xmlTextReaderPtr reader)
{
    const char *temp;

    switch (xmlTextReaderNodeType(reader)) {
    case XML_READER_TYPE_ELEMENT:
        temp = (char *)xmlTextReaderConstName(reader);
        if (!strcmp(temp, "card"))
            return CARD;
        if (!strcmp(temp, "num"))
            return NUMBER;
        if (!strcmp(temp, "front"))
            return FRONT;
        if (!strcmp(temp, "back"))
            return BACK;
        if (!strcmp(temp, "sub"))
            return SUB;
        if (!strcmp(temp, "root"))
            return ROOT;
        break;
    case XML_READER_TYPE_TEXT:
        break;
    }

    return 0;
}

void learnc_card_clear(voc_card &card)
{
    card.number = 0;
    card.front.clear();
    card.back.clear();
}
