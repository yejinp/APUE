CC=gcc
CFLAGS=-g

RM=rm -f

TARGET=figure15_5
TARGET+=figure15_6

OBJECTS=figure15_7.o

all: $(TARGET) $(OBJECTS);

figure15_5: figure15_5.c
	$(CC) $(CFLAGS)  $^ -o $@ 

figure15_6: figure15_6.c
	$(CC) $(CFLAGS)  $^ -o $@ 

figure15_7.o: figure15_7.c
	$(CC) $(CFLAGS)  $^ -c -o $@ 

clean:
	$(RM) $(TARGET) $(OBJECTS)
