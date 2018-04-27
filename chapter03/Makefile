CC=gcc
RM=rm -f

CFLAGS=-g

TARGET=figure3_1
TARGET+=figure3_2
TARGET+=figure3_4

all: $(TARGET);

figure3_1: figure3_1.c
	$(CC) $(CFLAGS)  $^ -o $@

figure3_2: figure3_2.c
	$(CC) $(CFLAGS)  $^ -o $@

figure3_4: figure3_4.c
	$(CC) $(CFLAGS)  $^ -o $@

clean:
	$(RM) $(TARGET)
