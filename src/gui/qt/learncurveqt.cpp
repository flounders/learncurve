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