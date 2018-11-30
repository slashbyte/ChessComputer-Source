#makefile for ChessComputer
#Author: Slash/byte
CC=g++
CFLAGS=-c -Wall
LDFLAGS= -lpthread
SOURCES=main.cpp ht16k33.cpp starburst.cpp container.cpp backend.cpp frontend.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=ChessByte

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o ChessByte
