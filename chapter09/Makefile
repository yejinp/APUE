CC=gcc
RM=rm -f

CFLAGS=-g

TARGET=figure9_11
TARGET+=getpgid
TARGET+=getpgrp
TARGET+=setsid
TARGET+=tcgetpgrp
TARGET+=tcgetsid

OBJECTS=

all: $(TARGET) $(OBJECTS);

tcgetpgrp: tcgetpgrp.c
	$(CC) $(CFLAGS)  $^ -o $@

getpgrp: getpgrp.c
	$(CC) $(CFLAGS)  $^ -o $@

tcgetsid: tcgetsid.c
	$(CC) $(CFLAGS)  $^ -o $@

setsid: setsid.c
	$(CC) $(CFLAGS)  $^ -o $@

getpgid: getpgid.c
	$(CC) $(CFLAGS)  $^ -o $@

figure9_11: figure9_11.c
	$(CC) $(CFLAGS)  $^ -o $@

clean:
	$(RM) $(TARGET) $(OBJECTS)
