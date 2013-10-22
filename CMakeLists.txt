cmake_minimum_required(VERSION 2.8)

PROJECT(learncurve)
FIND_PACKAGE(Qt4 REQUIRED)
FIND_PACKAGE(LibXml2 REQUIRED)

SET(learncurve_SOURCES src/main.cpp src/gui/qt/mainwindow.cpp
                       src/gui/qt/learncurveqt.cpp src/backend/boxes.cpp
                       src/backend/htmlgen.cpp src/backend/initialize.cpp
                       src/backend/read_vocab_file.cpp src/backend/review.cpp
                       src/backend/save_restore.cpp
                       )
SET(learncurve_HEADERS src/gui/qt/learncurveqt.h src/gui/qt/mainwindow.h )

QT4_WRAP_CPP(learncurve_HEADERS_MOC ${learncurve_HEADERS})

SET(QT_USE_QTWEBKIT TRUE)

INCLUDE(${QT_USE_FILE})


ADD_DEFINITIONS(${QT_DEFINITIONS})

include_directories(${LIBXML2_INCLUDE_DIR} ${QT_INCLUDE_DIRS})

ADD_EXECUTABLE(learncurve ${learncurve_SOURCES}
                          ${learncurve_HEADERS_MOC})

TARGET_LINK_LIBRARIES(learncurve ${QT_LIBRARIES} ${LIBXML2_LIBRARIES})

SET(CPACK_PACKAGE_VERSION "0.3")
SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "3")
SET(CPACK_SOURCE_GENERATOR "TGZ;TZ")
SET(CPACK_PACKAGE_VENDOR "Steven Williams")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "learncurve ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}")

INCLUDE(CPack)
