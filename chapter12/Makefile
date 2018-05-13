CC=gcc
RM=rm -f

CFLAGS=-g
CFLAGS+=-lpthread

TARGET=pthread_attr
TARGET+=pthread_concurrency
TARGET+=figure12_8
TARGET+=figure12_14
TARGET+=figure12_16
TARGET+=figure12_17
TARGET+=deadlock

OBJECTS=figure12_4.o
OBJECTS+=figure12_3.o
OBJECTS+=figure12_11.o
OBJECTS+=figure12_12.o
OBJECTS+=figure12_13.o

all: $(TARGET) $(OBJECTS);

figure12_8: figure12_8.c figure12_4.o
	$(CC) $^ -o $@ $(CFLAGS)

figure12_3.o: figure12_3.c
	$(CC) $^ -c -o $@ $(CFLAGS)

figure12_4.o: figure12_4.c
	$(CC) $^ -c -o $@ $(CFLAGS)

figure12_11.o: figure12_11.c
	$(CC) $^ -c -o $@ $(CFLAGS)

figure12_12.o: figure12_12.c
	$(CC) $^ -c -o $@ $(CFLAGS)

figure12_14: figure12_14.c
	$(CC) $^ -o $@ $(CFLAGS)

figure12_16: figure12_16.c
	$(CC) $^ -o $@ $(CFLAGS)

figure12_17: figure12_17.c
	$(CC) $^ -o $@ $(CFLAGS)

figure12_13.o: figure12_13.c
	$(CC) $^ -c -o $@ $(CFLAGS)

pthread_concurrency: pthread_concurrency.c
	$(CC) $^ -o $@ $(CFLAGS)

deadlock: deadlock.c
	$(CC) $^ -o $@ $(CFLAGS)

pthread_attr: pthread_attr.c
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	$(RM) $(TARGET) $(OBJECTS)
