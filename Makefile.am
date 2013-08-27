CLEANFILES = *~

bin_PROGRAMS = learncurve
learncurve_SOURCES = src/main.cpp src/backend/boxes.cpp src/backend/htmlgen.cpp\
                     src/backend/initialize.cpp src/backend/read_vocab_file.cpp\
                     src/backend/review.cpp src/backend/save_restore.cpp\
                     src/gui/qt/mainwindow.cpp src/gui/qt/learncurveqt.cpp

nodist_learncurve_SOURCES = src/gui/qt/moc_mainwindow.cpp src/gui/qt/moc_learncurveqt.cpp

AM_CXXFLAGS = -Wall @LPACKAGE_CFLAGS@ -DDATADIR=\"$(datadir)/@PACKAGE@\"

learncurve_CPPFLAGS = -I. -fpic -fstack-protector-all @XML_CFLAGS@
learncurve_LDADD = -lpthread @LPACKAGE_LIBS@ @XML_LIBS@

learncurvedir = $(datadir)/$(PACKAGE)

EXTRA_DIST = $(learncurve_DATA)

moc_%.cpp: %.h
	moc-qt4 $< -o $@
