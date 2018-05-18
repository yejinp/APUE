CC=gcc
RM=rm -f

CFLAGS=-g

TARGET=figure16_8
TARGET+=figure16_14
TARGET+=figure16_15

OBJECTS=figure16_9.o
OBJECTS+=figure16_10.o

all: $(TARGET) $(OBJECTS);

figure16_8: figure16_8.c
	$(CC) $(CFLAGS)  $^ -o $@

figure16_14: figure16_14.c figure16_9.o
	$(CC) $(CFLAGS)  $^ -o $@

figure16_15: figure16_15.c figure16_10.o
	$(CC) $(CFLAGS)  $^ -o $@

figure16_9.o: figure16_9.c
	$(CC) $(CFLAGS)  $^ -c -o $@

figure16_10.o: figure16_10.c
	$(CC) $(CFLAGS)  $^ -c -o $@

clean:
	$(RM) $(TARGET) $(OBJECTS)
