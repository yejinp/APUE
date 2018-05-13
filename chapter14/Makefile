CC=gcc
RM=rm -f

CFLAGS=-g

TARGET=figure14_1
TARGET=figure14_12

OBJECTS=figure14_5.o
OBJECTS+=figure14_6.o
OBJECTS+=figure14_9.o

all: $(TARGET) $(OBJECTS);

figure14_1: figure14_1.c
	$(CC) $(CFLAGS)  $^ -o $@

figure14_12: figure14_12.c
	$(CC) $(CFLAGS)  $^ -o $@

figure14_5.o: figure14_5.c
	$(CC) $(CFLAGS)  $^ -c -o $@

figure14_6.o: figure14_6.c
	$(CC) $(CFLAGS)  $^ -c -o $@

figure14_9.o: figure14_9.c
	$(CC) $(CFLAGS)  $^ -c -o $@

clean:
	$(RM) $(TARGET) $(OBJECTS)
