CFLAGS=-c -Wall -DVERBO_PRINT -Irs/ -Irs/gf -I./ 
LDFLAGS=
SOURCES=main.c cmd_line.c common.c ldpc/ldpc.c rs/rs.c
OBJECTS=$(SOURCES:.c=.o)
TARGET=wr_coding

all: $(SOURCES) $(TARGET)
    
$(TARGET): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(TARGET) $(OBJECTS)

PHONEY:
	clean 
