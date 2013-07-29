CLEANFILES = *~
#AM_CPPFLAGS = @GTK_CFLAGS@
#AM_LDADD = @GTK_LIBS@

bin_PROGRAMS = learncurve
learncurve_SOURCES = src/main.cpp src/backend/boxes.cpp src/backend/htmlgen.cpp src/backend/initialize.cpp src/backend/read_vocab_file.cpp src/backend/review.cpp src/backend/save_restore.cpp src/gui/gtk3/callbacks.cpp src/gui/gtk3/control.cpp

learncurve_CPPFLAGS = @GTK_CFLAGS@ $(XML_CFLAGS) $(WEBKITGTK_CFLAGS) $(GMODULE_CFLAGS)
learncurve_LDADD = @GTK_LIBS@ $(XML_LIBS) $(WEBKITGTK_LIBS) $(GMODULE_LIBS)
