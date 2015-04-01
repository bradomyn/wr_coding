CFLAGS=-c -Wall -DVERBO_PRINT -Irs/ -Irs/gf/galois -Irs/gf/poly_op
LDFLAGS=
RS_SOURCE=rs/rs.c rs/gf/galois/galois.c rs/gf/poly_op/poly_op.c
SOURCES=wr_coding.c cmd_line.c common.c $(RS_SOURCE)
OBJECTS=$(SOURCES:.c=.o)
TARGET=wr_coding

all: $(TARGET)
    
$(TARGET): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(TARGET) $(OBJECTS)

PHONEY:
	clean 
