#Getting fancier with dem makes

CC=g++
CFLAGS=-c
LIBS=-lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
SOURCES=main.cpp win.cpp level4.cpp level3.cpp level2.cpp gib.cpp ball.cpp paddle.cpp block.cpp collision.cpp level1.cpp title.cpp intro.cpp gamestate.cpp timer.cpp globals.cpp image.cpp init.cpp
OBJECTS=$(SOURCES:.cpp=.o)
TARGET=wreckin_rects

#make target executable from sources
all: $(SOURCES) $(TARGET)

#make target from objects
#$@ is target
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LIBS)

#make object from source
#$@ is name of object file
#$< is name of prerequisite .cpp file
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

help:
	@echo "make: execute first rule in the makefile (make all)"
	@echo "make all: makes all"
	@echo "make clean: get rid of compiled files"
	@echo "make help: see this"


clean:
	@rm -v $(TARGET) *.o
