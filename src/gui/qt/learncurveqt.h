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

#ifndef LEARNCURVEQT_H_
#define LEARNCURVEQT_H_

#include <QtGui>
#include <QtWebKit>
#include <vector>
#include <string>
#include "../../backend/types.h"

class LearncurveQt : public QWidget
{
    Q_OBJECT
  private:
    QWebView *webView;
    QPushButton *reviewButton;
    QPushButton *viewBoxesButton;
    QPushButton *doneButton;
    QHBoxLayout *frameLayout;
    QVBoxLayout *buttonLayout;
    QVBoxLayout *controlLayout;
    QHBoxLayout *entryLayout;
    QLineEdit *textEntry;

    std::vector<std::string> input;

  public:
    LearncurveQt();
    bool copySelection();
    bool cutSelection();
    bool pasteSelection();
    bool deleteSelection();

    instance data;
    int reviewState;
  private slots:
    void reviewButtonClicked();
    void viewBoxesButtonClicked();
    void doneButtonClicked();
    void textEntryReturnPressed();
};

#endif
