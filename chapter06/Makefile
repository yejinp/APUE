CC=gcc
RM=rm -f

CFLAGS=-g

TARGET=getgrent
TARGET+=getgrgid
TARGET+=getpwent
TARGET+=uname

OBJECTS=figure6_2.o

all: $(TARGET) $(OBJECTS);

uname: uname.c
	$(CC) $(CFLAGS)  $^ -o $@

getgrent: getgrent.c
	$(CC) $(CFLAGS)  $^ -o $@

getgrgid: getgrgid.c
	$(CC) $(CFLAGS)  $^ -o $@

getpwent: getpwent.c
	$(CC) $(CFLAGS)  $^ -o $@

figure6_2.o: figure6_2.c
	$(CC) $(CFLAGS)  $^ -c -o $@

clean:
	$(RM) $(TARGET) $(OBJECTS)
