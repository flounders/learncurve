#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QtGui>
#include <string>
#include "learncurveqt.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
  public:
    MainWindow();
    void createMenus();
    void createActions();
  private:
    LearncurveQt *controls;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;

    QAction *openAct;
    QAction *saveAct;
    QAction *quitAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *deleteAct;
    QAction *aboutAct;

    char *fileName;
    std::string safeSpot;

    void setSafeSpot(char *filename);
    const char *getSafeSpot(void);
  private slots:
    void openFile();
    void save();
    void cut();
    void copy();
    void paste();
    void deleteText();
    void about();
};

#endif
