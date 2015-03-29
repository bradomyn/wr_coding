CFLAGS=-c -Wall -I../galois/
LDFLAGS=
SOURCES=../galois/galois.c poly_op.c
OBJECTS=$(SOURCES:.c=.o)
TARGET=genpoly evalpoly

all: $(TARGET)
    
genpoly :genpoly.o $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) genpoly.o -o $@

evalpoly :evalpoly.o $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) evalpoly.o -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(TARGET) $(OBJECTS) 

PHONEY:
	clean all
