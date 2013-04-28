CC := clang++
LD := clang++

BIN = learncurve

SRCS = main.cpp backend/htmlgen.cpp backend/initialize.cpp backend/read_vocab_file.cpp backend/save_restore.cpp gui/gtk3/callbacks.cpp gui/gtk3/control.cpp backend/boxes.cpp backend/review.cpp

SOURCES = $(SRCS)

OBJS = $(SRCS:.cpp=.o)

OBJECTS = $(OBJS)

INCLS = -I/usr/include/libxml2 -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/gtk-3.0 -I/usr/include/atk-1.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/pango-1.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/harfbuzz -I/usr/include/freetype2 -I/usr/include/pixman-1 -I/usr/include/libpng15 -I/usr/include/libdrm -I/usr/include/webkitgtk-3.0 -I/usr/include/libsoup-2.4

CPPFLAGS = $(INCLS) -pthread -Wall

LDLIBS = -Wl,--export-dynamic -pthread -lxml2 -lgmodule-2.0 -lrt -lwebkitgtk-3.0 -lgtk-3 -lsoup-2.4 -ljavascriptcoregtk-3.0 -lgdk-3 -latk-1.0 -lpangocairo-1.0 -lgdk_pixbuf-2.0 -lcairo-gobject -lpango-1.0 -lcairo -lgio-2.0 -lgobject-2.0 -lglib-2.0

.PHONY: all

all: $(BIN)

$(BIN): $(OBJS)
	$(LD) $(CPPFLAGS) $(LDLIBS) $^ -o ../build/$@

.PHONY:	depend clean

clean:
	rm -f $(OBJECTS)

depend:	depend.mk

depend.mk:	$(SOURCES) $(HEADERS)
	$(CC) -MM $(CPPFLAGS) $(SOURCES) > $@

include depend.mk
