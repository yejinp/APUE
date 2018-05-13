CC=gcc
RM=rm -f

CFLAGS=-g

THREAD_FLAG=-lpthread

TARGET=figure13_7
TARGET+=figure13_8

OBJECTS=figure13_1.o
OBJECTS+=figure13_6.o

all: $(TARGET) $(OBJECTS);

figure13_7: figure13_7.c figure13_1.o figure13_6.o
	$(CC) $(CFLAGS)  $^ -o $@ $(THREAD_FLAG)

figure13_8: figure13_8.c figure13_1.o figure13_6.o
	$(CC) $(CFLAGS)  $^ -o $@ $(THREAD_FLAG)

figure13_1.o: figure13_1.c
	$(CC) $(CFLAGS)  $^ -c -o $@

figure13_6.o: figure13_6.c
	$(CC) $(CFLAGS)  $^ -c -o $@

clean:
	$(RM) $(TARGET) $(OBJECTS)
