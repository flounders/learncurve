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

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <libxml/xmlreader.h>
#include "types.h"
#include "read_vocab_file.h"

using namespace std;

// learnc_parse_file takes an XML file and walks through its elements.
// As it walks through the document tree, it takes the data from the
// appropriate elements and puts it into a card which when it comes
// across another card element pushes the card it has just worked on
// into the stack.
//
// returns 0 for failure and 1 for success
// takes an xmlTextReaderPtr for walking through our XML file and
// a vector holding voc_cards passed by reference for the stack

int learnc_parse_file(xmlTextReaderPtr reader, std::vector<voc_card> &stack)
{
    if (reader == NULL)
        return 0;

    short state = 0;
    string buf;
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
    vector<voc_card> stack;

    reader = xmlReaderForDoc((xmlChar *) testxml, NULL, NULL, 0);
    if (reader == NULL) {
        cerr << "test_parse_file: problem with xmlReaderForDoc\n";
        return 0;
    }

    retval = learnc_parse_file(reader, stack);
    if (retval == 0) {
        cerr << "test_parse_file: learnc_parse_file failed on reader\n";
        return 0;
    }

    if (stack.size() == 3) 
        ;
    else {
        cerr << "test_parse_file: stack vector unexpected size of "
                  << stack.size() << endl;
        for (retval = 0; retval < stack.size(); retval++)
            cout << stack[retval].number << endl;
        return 0;
    }

    xmlFreeTextReader(reader);
    xmlCleanupParser();

    return 1;
}

// learnc_element_check tests to see what element we are currently
// in and returns a value to indicate which element we are in. This
// function is made for use with learnc_parse_file.
//
// returns a value assosciated with a type of element or 0 for failure
// takes xmlTextReaderPtr for an argument which is what is used to
// walk through the XML file containing our data.

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

// learnc_card_clear is used to reinitialize all of the data in a
// card. It is used in learnc_parse_file to clear the buffer card
// after the card that has just been read in is stored.
//
// returns nothing
// takes a voc_card that is passed by reference

void learnc_card_clear(voc_card &card)
{
    card.number = 0;
    card.front.clear();
    card.back.clear();
}
