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

#include <climits>
#include "mainwindow.h"
#include "learncurveqt.h"
#include "../../backend/read_vocab_file.h"
#include "../../backend/htmlgen.h"
#include "../../backend/initialize.h"
#include "../../backend/save_restore.h"
#include <fstream>
#include <iostream>

using namespace std;

MainWindow::MainWindow()
{
    createActions();
    createMenus();

    controls = new LearncurveQt;
    setCentralWidget(controls);
    fileName = NULL;
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    editMenu->addAction(deleteAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
}

void MainWindow::createActions()
{
    openAct = new QAction(tr("&Open"), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open a file."));
    connect(openAct, SIGNAL(triggered()), this, SLOT(openFile()));

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save progress."));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    quitAct = new QAction(tr("&Quit"), this);
    quitAct->setShortcuts(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Quit program."));
    connect(quitAct, SIGNAL(triggered()), qApp, SLOT(quit()));

    cutAct = new QAction(tr("&Cut"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut"));
    connect(cutAct, SIGNAL(triggered()), this, SLOT(cut()));

    copyAct = new QAction(tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy"));
    connect(copyAct, SIGNAL(triggered()), this, SLOT(copy()));

    pasteAct = new QAction(tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste"));
    connect(pasteAct, SIGNAL(triggered()), this, SLOT(paste()));

    deleteAct = new QAction(tr("&Delete"), this);
    deleteAct->setShortcuts(QKeySequence::Delete);
    deleteAct->setStatusTip(tr("Delete"));
    connect(deleteAct, SIGNAL(triggered()), this, SLOT(deleteText()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("About"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::openFile()
{
    int status;
    xmlTextReaderPtr reader;
    QString output = QFileDialog::getOpenFileName(this, tr("Open File"), "",
                                                  tr("XML Files (*.xml)"));
    char path[PATH_MAX];
    ifstream inFile;
    QByteArray ba;

    if (output != "") {
        ba = output.toUtf8();
        fileName = ba.data();
        setSafeSpot(fileName);
        reader = xmlReaderForFile(fileName, NULL, 0);
  
        if (reader == NULL) {
            cerr << "MainWindow::openFile(): Encountered error opening XML file.\n";
            return;
        }
    }
    else {
        // bring up a dialog saying this didn't work
        return;
    }

    status = learnc_parse_file(reader, controls->data.stack);
    if (status == 0) {
        cerr << "MainWindow::openFile(): Encountered error with learnc_parse_file().\n";
        return;
    }
    controls->data.known->size = controls->data.stack.size();

// without the line below present fileName is clear, but not NULL
// resultin in a segfault.
    fileName = ba.data();
    learnc_make_storage_directory(fileName);

    if (learnc_get_storage_path(fileName, path) == 1) {
        strcat(path, "/boxcards");
        inFile.open(path);
        if (!inFile.fail()) {
            learnc_restore_boxes(controls->data.boxes, inFile, controls->data.stack);
            inFile.close();
        }
    }
    else {
        cerr << "MainWindow::openFile(): Received failure on learnc_get_storage_path().\n";
    }

    if (learnc_get_storage_path(fileName, path) == 1) {
        strcat(path, "/knowncards");
        inFile.open(path);
        if (!inFile.fail()) {
            learnc_restore_known(controls->data.known, inFile, controls->data.stack);
            inFile.close();
        }
    }
    else {
        cerr << "MainWindow::openFile(): Received failure on learnc_get_storage_path().\n";
    }

}

void MainWindow::save()
{
    ofstream outFile;
    char path[PATH_MAX];

    fileName = (char *) getSafeSpot();

    if (learnc_get_storage_path(fileName, path) == 1) {
        strcat(path, "/boxcards");
        outFile.open(path);
    }
    else {
        cerr << "MainWindow::save(): Received failure on learnc_get_storage_path().\n";
        return;
    }

    if (learnc_save_boxes(controls->data.boxes, outFile) == 0) {
        cerr << "MainWindow::save(): Encountered problem with boxes pointer in "
             << "learnc_save_boxes().\n";
    }
    outFile.close();

    if (learnc_get_storage_path(fileName, path) == 1) {
        strcat(path, "/knowncards");
        outFile.open(path);
    }
    else {
        cerr << "MainWindow::save(): Received failure on learnc_get_storage_path().\n";
        return;
    }

    if (learnc_save_box(controls->data.known, outFile) == 0) {
        cerr << "MainWindow::save(): Encountered problem with boxes pointer in "
             << "learnc_save_box().\n";
    }

    outFile.close();
}

void MainWindow::cut()
{
    controls->cutSelection();
}

void MainWindow::copy()
{
    controls->copySelection();
}

void MainWindow::paste()
{
    controls->pasteSelection();
}

void MainWindow::deleteText()
{
    controls->deleteSelection();
}

void MainWindow::about()
{
    QMessageBox::about(this, "About Learncurve",
                       "Written by Steven Williams and licensed under GPLv2.");
}

void MainWindow::setSafeSpot(char *filename)
{
    safeSpot = filename;
}

const char *MainWindow::getSafeSpot(void)
{
    return safeSpot.c_str();
}
