OBJS=sdlOpengl3.o
CPPFILES=sdlOpengl3.cpp
HFILES=sdlOpengl3.h

EXE=sdlOpengl3

CXXFLAGS=`sdl2-config --cflags`
LIBS=`sdl2-config --libs` -lGL

CC=g++

default: $(EXE)

$(EXE): $(OBJS)
	$(CC) -o $(EXE) $(OBJS) $(CFLAGS) $(LIBS)

sdlOpengl.o: sdlOpengl.cpp sdlOpengl.h
	$(CC) -c sdlOpengl.cpp

clean:
	rm -rf $(EXE) $(OBJS)
