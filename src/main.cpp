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

#include <iostream>
#include <string>
#include <vector>
#include "backend/htmlgen.h"
#include "backend/initialize.h"
#include "backend/read_vocab_file.h"
#include "backend/review.h"
#include "backend/types.h"
#include "gui/qt/mainwindow.h"

// main is where everything starts and ends
// TODO add processing for command-line arguments and freeing all allocated memory

int main(int argc, char *argv[])
{

    learnc_init_charset((char *) "en_US.UTF-8");

#ifdef __linux__
    learnc_init_linux_storage();
#endif

    QApplication app(argc, argv);
    MainWindow window;

    window.show();

    return app.exec();
}
