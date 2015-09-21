CC=gcc
CFLAGS=-c -g -Wall
LDFLAGS=
SOURCES=main.c usedata.c createQcaFile.c createQCAHelper.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=useFile

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
