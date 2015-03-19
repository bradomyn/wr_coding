CFLAGS=-c -Wall -DVERBO_PRINT -I$(PWD)
LDFLAGS=
SOURCES=main.c gf256.c
SOURCES_16=main.c gf16.c
OBJECTS=$(SOURCES:.c=.o)
OBJECTS_16=$(SOURCES_16:.c=.o)
TARGET=gf256 gf16

all: $(TARGET)
    
gf256 : $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

gf16 : $(OBJECTS_16) 
	$(CC) $(LDFLAGS) $(OBJECTS_16) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(TARGET) $(OBJECTS) $(OBJECTS_16)

PHONEY:
	clean all
