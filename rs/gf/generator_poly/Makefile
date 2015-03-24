CFLAGS=-c -Wall -I../galois/
LDFLAGS=
SOURCES=main.c ../galois/galois.c genpoly.c
OBJECTS=$(SOURCES:.c=.o)
TARGET=genpoly

all: $(TARGET)
    
genpoly : $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(TARGET) $(OBJECTS) $(OBJECTS_16)

PHONEY:
	clean all
