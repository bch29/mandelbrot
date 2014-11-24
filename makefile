CC=g++

#Directory containing "SDL.h"
SDL_INCLUDE=/usr/include/SDL2

#Directory containing "libSDL2.so" and "libSDL2main.a"
SDL_LIB=/usr/lib/x86_64-linux-gnu

CFLAGS=-c -Wall -O3 -I$(SDL_INCLUDE) -Iinclude  -std=c++0x
LDFLAGS=-O3 -L$(SDL_LIB) -lSDL2main -lSDL2

SOURCES=main.cpp GradientConverter.cpp mandel.cpp MandelbrotViewer.cpp Viewer.cpp

vpath %.cpp src

OBJECTS=$(SOURCES:.cpp=.o)

EXECUTABLE=mandelbrot

build: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $^ -o $@

run: build
	./$(EXECUTABLE)

clean:
	rm $(OBJECTS) $(EXECUTABLE)
