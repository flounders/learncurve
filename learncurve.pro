QT += gui core webkit

TEMPLATE = app
TARGET = 
DEPENDPATH +=
INCLUDEPATH +=

INCLUDEPATH += /usr/include/libxml2

macx {
LIBS += /usr/lib/libxml2.dylib
}

unix:!macx{
LIBS += /usr/lib64/libxml2.so.2
}

HEADERS += src/backend/boxes.h src/backend/htmlgen.h src/backend/initialize.h\
           src/backend/read_vocab_file.h src/backend/review.h src/backend/save_restore.h\
           src/gui/qt/mainwindow.h src/gui/qt/learncurveqt.h
SOURCES += src/main.cpp src/backend/boxes.cpp src/backend/htmlgen.cpp\
                     src/backend/initialize.cpp src/backend/read_vocab_file.cpp\
                     src/backend/review.cpp src/backend/save_restore.cpp\
                     src/gui/qt/mainwindow.cpp src/gui/qt/learncurveqt.cpp
