#ifndef TYPES_H_
#define TYPES_H_
#include <string>
#include <vector>

#define MAX_BOXES 5

struct voc_card {
    int number;
    std::vector<std::string> front;
    std::vector<std::string> back;
};

struct box {
    int size;
    std::vector<voc_card *> stack;
};

struct instance {
    std::vector<voc_card> stack;
    box *boxes;
    box *known;
};

#endif
