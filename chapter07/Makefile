CC=gcc
RM=rm -f

CFLAGS=-g

TARGET=figure7_1
TARGET+=figure7_3
TARGET+=figure7_4
TARGET+=figure7_8
TARGET+=figure7_9
TARGET+=figure7_13
TARGET+=figure7_16

OBJECTS=figure7_14.o

all: $(TARGET) $(OBJECTS);

figure7_3: figure7_3.c
	$(CC) $(CFLAGS)  $^ -o $@

figure7_1: figure7_1.c
	$(CC) $(CFLAGS)  $^ -o $@

figure7_4: figure7_4.c
	$(CC) $(CFLAGS)  $^ -o $@

figure7_8: figure7_8.c
	$(CC) $(CFLAGS)  $^ -o $@

figure7_9: figure7_9.c
	$(CC) $(CFLAGS)  $^ -o $@

figure7_16: figure7_16.c
	$(CC) $(CFLAGS)  $^ -o $@

figure7_13: figure7_13.c
	$(CC) $(CFLAGS)  $^ -o $@

figure7_14.o: figure7_14.c
	$(CC) $(CFLAGS)  $^ -c -o $@

clean:
	$(RM) $(TARGET) $(OBJECTS)
