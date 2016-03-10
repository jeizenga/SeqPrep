CFLAGS=-c -Wall -O0 -g
#recommended options: -ffast-math -ftree-vectorize -march=core2 -mssse3 -O3
COPTS=
LDFLAGS=-lz -lm
SOURCES=SeqPrep.c utils.c stdaln.c CuTest.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=SeqPrep

all: $(SOURCES) $(EXECUTABLE) unit_test

$(EXECUTABLE): $(OBJECTS)
	$(CC) ${COPTS} $(OBJECTS) $(LDFLAGS) -o $@

unit_test.o: $(OBJECTS)
	$(CC) ${COPTS} $(CFLAGS) unit_test.c -o $@
	
unit_test: $(OBJECTS) unit_test.o
	$(CC) ${COPTS} utils.o stdaln.o unit_test.o CuTest.o $(LDFLAGS) -o $@

install: all
	-cp $(EXECUTABLE) $(HOME)/bin

.c.o:
	$(CC) ${COPTS} $(CFLAGS) $< -o $@

clean:
	-rm -f $(OBJECTS) $(EXECUTABLE) unit_test unit_test.o

check-syntax:
	$(CC) ${CFLAGS} -o .nul -S ${CHK_SOURCES}
