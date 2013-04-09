#include <iostream>
#include <string>
#include <vector>
#include "backend/htmlgen.h"
#include "backend/initialize.h"
#include "backend/read_vocab_file.h"
#include "backend/review.h"
#include "backend/types.h"
#include "gui/gtk3/control.h"

int main(int argc, char *argv[])
{

    learnc_init_charset((char *) "en_US.UTF-8");
    learnc_init_linux_storage();

    learnc_gtk3_gui_init(argc, &argv);

    return 0;
}
