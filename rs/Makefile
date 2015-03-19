CFLAGS=-c -Wall -DVERBO_PRINT -I./ -Igf/ -I../
LDFLAGS=
SOURCES=main.c gf/gf256.c rs.c
SOURCES_16=main.c gf/gf16.c rs.c
OBJECTS=$(SOURCES:.c=.o)
OBJECTS_16=$(SOURCES_16:.c=.o)
TARGET=rs256 rs16

all: $(TARGET)
    
rs256 : $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

rs16 : $(OBJECTS_16) 
	$(CC) $(LDFLAGS) $(OBJECTS_16) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(TARGET) $(OBJECTS) $(OBJECTS_16)

PHONEY:
	clean all
