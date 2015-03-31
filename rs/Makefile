CFLAGS=-c -Wall -DVERBO_PRINT -I./ -Igf/galois/ -I../ -Igf/poly_op
LDFLAGS=
GF_SOURCE=gf/galois/galois.c gf/poly_op/poly_op.c
SOURCES=main.c rs.c $(GF_SOURCE)
OBJECTS=$(SOURCES:.c=.o)
TARGET=rs

all: $(TARGET)
    
rs : $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(TARGET) $(OBJECTS) $(OBJECTS_16)

PHONEY:
	clean all
