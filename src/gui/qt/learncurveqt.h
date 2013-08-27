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
  public:
    LearncurveQt();
    instance data;
    int reviewState;
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
  private slots:
    void reviewButtonClicked();
    void viewBoxesButtonClicked();
    void doneButtonClicked();
    void textEntryReturnPressed();
};

#endif
