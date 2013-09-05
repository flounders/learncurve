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

#include "learncurveqt.h"
#include "../../backend/review.h"
#include "../../backend/htmlgen.h"
#include "../../backend/initialize.h"
#include <QtGui>
#include <QtWebKit>
#include <string>

using namespace std;

LearncurveQt::LearncurveQt()
{
    webView = new QWebView;
    textEntry = new QLineEdit;

    reviewButton = new QPushButton("&Review");
    viewBoxesButton = new QPushButton("&View Boxes");
    doneButton = new QPushButton("&Done");

    frameLayout = new QHBoxLayout;
    buttonLayout = new QVBoxLayout;
    controlLayout = new QVBoxLayout;
    entryLayout = new QHBoxLayout;

    connect(reviewButton, SIGNAL(clicked()), this, SLOT(reviewButtonClicked()));
    connect(viewBoxesButton, SIGNAL(clicked()), this, SLOT(viewBoxesButtonClicked()));
    connect(doneButton, SIGNAL(clicked()), this, SLOT(doneButtonClicked()));
    connect(textEntry, SIGNAL(returnPressed()), this, SLOT(textEntryReturnPressed()));

    buttonLayout->addWidget(reviewButton);
    buttonLayout->addWidget(viewBoxesButton);
    buttonLayout->setAlignment(Qt::AlignTop);

    entryLayout->addWidget(textEntry);
    entryLayout->addWidget(doneButton);

    controlLayout->addWidget(webView);
    controlLayout->addLayout(entryLayout);

    frameLayout->addLayout(buttonLayout);
    frameLayout->addLayout(controlLayout);

    setLayout(frameLayout);

    learnc_html_welcome_page();
    webView->load(QString(OUTPUT_PAGE_URI));

    learnc_init_instance(data);

    reviewState = OUT_REVIEW;
}

void LearncurveQt::reviewButtonClicked()
{
    if (reviewState == OUT_REVIEW) {
        learnc_review_control(data, input, reviewState);
        webView->reload();
    }
}

void LearncurveQt::viewBoxesButtonClicked()
{
    if (reviewState != OUT_REVIEW) {
        return;
    }

    learnc_html_view_boxes(data);
    webView->reload();
}

void LearncurveQt::doneButtonClicked()
{
    static int flag;

    if (flag == 0 && reviewState == IN_REVIEW) {
        flag = 1;
        doneButton->setText("&Next");
    }
    else if (flag == 1 && reviewState == IN_REVIEW) {
        flag = 0;
        doneButton->setText("&Done");
    }

    if (reviewState == IN_REVIEW) {
        learnc_review_control(data, input, reviewState);
        webView->reload();
        if (reviewState != IN_REVIEW) {
            doneButton->setText("&Done");
            flag = 0;
        }
        input.clear();
    }
}

void LearncurveQt::textEntryReturnPressed()
{
    QString buffer;
    QByteArray ba;
    string conversion;

    if (reviewState != IN_REVIEW) {
        input.clear();
    }

    buffer = textEntry->text();
    ba = buffer.toUtf8();
    conversion = ba.data();
    input.push_back(conversion);

    if (reviewState == MENU_REVIEW) {
        learnc_review_control(data, input, reviewState);
        webView->reload();
        input.clear();
    }

    textEntry->setText("");
}

bool LearncurveQt::copySelection()
{
    QString buffer;
    QClipboard *clipBoard = QApplication::clipboard();

    if (textEntry->hasSelectedText()) {
        textEntry->copy();
        return true;
    }
    if (webView->hasSelection()) {
        buffer = webView->selectedText();
        clipBoard->setText(buffer, QClipboard::Clipboard);
        return true;
    }

    return false;
}

bool LearncurveQt::cutSelection()
{
    QString buffer;
    QClipboard *clipBoard = QApplication::clipboard();

    if (textEntry->hasSelectedText()) {
        textEntry->cut();
        return true;
    }
    if (webView->hasSelection()) {
        buffer = webView->selectedText();
        clipBoard->setText(buffer, QClipboard::Clipboard);
        return true;
    }

    return false;
}

bool LearncurveQt::pasteSelection()
{
    if (textEntry->hasFocus()) {
        textEntry->paste();
        return true;
    }

    return false;
}

bool LearncurveQt::deleteSelection()
{
    if (textEntry->hasSelectedText()) {
        textEntry->del();
        return true;
    }

    return false;
}
