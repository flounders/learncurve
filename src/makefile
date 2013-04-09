CC := clang++
LD := clang++
CFLAGS := `pkg-config --cflags libxml-2.0 gmodule-2.0 gtk+-3.0 webkitgtk-3.0` -Wl,-export-dynamic -Wall
LIBS := `pkg-config --libs libxml-2.0 gmodule-2.0 gtk+-3.0 webkitgtk-3.0`

.PHONY: all

all: learncurve

learncurve: main.o htmlgen.o initialize.o read_vocab_file.o save_restore.o callbacks.o control.o boxes.o review.o
	$(LD) $(CFLAGS) $(LIBS) $^ -o $@

main.o: main.cpp
	$(LD) $(CFLAGS) $(LIBS) -c $^

htmlgen.o: backend/htmlgen.cpp
	$(CC) $(CFLAGS) $(LIBS) -c $^

initialize.o: backend/initialize.cpp
	$(CC) $(CFLAGS) $(LIBS) $^ -c

read_vocab_file.o: backend/read_vocab_file.cpp
	$(CC) $(CFLAGS) $(LIBS) $^ -c

save_restore.o: backend/save_restore.cpp
	$(CC) $(CFLAGS) $(LIBS) $^ -c

callbacks.o: gui/gtk3/callbacks.cpp
	$(CC) $(CFLAGS) $(LIBS) $^ -c

control.o: gui/gtk3/control.cpp
	$(CC) $(CFLAGS) $(LIBS) $^ -c

boxes.o: backend/boxes.cpp
	$(CC) $(CFLAGS) $(LIBS) $^ -c

review.o: backend/review.cpp
	$(CC) $(CFLAGS) $(LIBS) $^ -c

clean:
	rm *.o learncurve
