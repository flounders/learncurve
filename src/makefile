CC := g++
LD := g++

BIN = learncurve

SRCS = main.cpp backend/htmlgen.cpp backend/initialize.cpp backend/read_vocab_file.cpp backend/save_restore.cpp gui/gtk3/callbacks.cpp gui/gtk3/control.cpp backend/boxes.cpp backend/review.cpp

SOURCES = $(SRCS)

OBJS = $(SRCS:.cpp=.o)

OBJECTS = $(OBJS)

INCLS = `pkg-config --cflags gtk+-3.0 webkitgtk-3.0 gmodule-2.0 libxml-2.0`
CPPFLAGS = $(INCLS) -Wall

LDLIBS =  `pkg-config --libs gtk+-3.0 webkitgtk-3.0 gmodule-2.0 libxml-2.0`

.PHONY: all

all: $(BIN)

$(BIN): $(OBJS)
	$(LD) $^ -o ../build/$@ $(CPPFLAGS) $(LDLIBS) 

.PHONY:	depend clean

clean:
	rm -f $(OBJECTS)

depend:	depend.mk

depend.mk:	$(SOURCES) $(HEADERS)
	$(CC) -MM $(CPPFLAGS) $(SOURCES) > $@

include depend.mk
