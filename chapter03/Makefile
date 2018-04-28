CC=gcc
RM=rm -f

CFLAGS=-g

TARGET=figure3_1
TARGET+=figure3_2
TARGET+=figure3_4
TARGET+=figure3_8
TARGET+=figure3_10

OBJECTS=figure3_11.o

all: $(TARGET) $(OBJECTS);

figure3_1: figure3_1.c
	$(CC) $(CFLAGS)  $^ -o $@

figure3_2: figure3_2.c
	$(CC) $(CFLAGS)  $^ -o $@

figure3_4: figure3_4.c
	$(CC) $(CFLAGS)  $^ -o $@

figure3_8: figure3_8.c
	$(CC) $(CFLAGS)  $^ -o $@

figure3_10: figure3_10.c
	$(CC) $(CFLAGS)  $^ -o $@

figure3_11.o: figure3_11.c
	$(CC) $(CFLAGS)  $^ -c -o $@

clean:
	$(RM) $(TARGET) $(OBJECTS)
