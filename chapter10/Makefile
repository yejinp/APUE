CC=gcc
RM=rm -f

CFLAGS=-g

OBJECTS=figure10_7.o
OBJECTS+=figure10_8.o

TARGET=figure10_2
TARGET+=figure10_5
TARGET+=figure10_6
TARGET+=figure10_9
TARGET+=figure10_10
TARGET+=figure10_11
TARGET+=figure10_14
TARGET+=figure10_15
TARGET+=figure10_30
TARGET+=strsignal

all: $(TARGET) $(OBJECTS);

figure10_2:figure10_2.c
	$(CC) $(CFLAGS)  $^ -o $@ 

figure10_5:figure10_5.c
	$(CC) $(CFLAGS)  $^ -o $@ 

figure10_6:figure10_6.c
	$(CC) $(CFLAGS)  $^ -o $@ 

figure10_7.o:figure10_7.c
	$(CC) $(CFLAGS)  $^ -c -o $@ 

figure10_8.o:figure10_8.c
	$(CC) $(CFLAGS)  $^ -c -o $@ 

figure10_9:figure10_9.c figure10_8.o
	$(CC) $(CFLAGS)  $^ -o $@ 

figure10_10:figure10_10.c
	$(CC) $(CFLAGS)  $^ -o $@ 

figure10_11:figure10_11.c
	$(CC) $(CFLAGS)  $^ -o $@ 

figure10_14:figure10_14.c
	$(CC) $(CFLAGS)  $^ -o $@ 

figure10_15:figure10_15.c
	$(CC) $(CFLAGS)  $^ -o $@ 

figure10_30:figure10_30.c
	$(CC) $(CFLAGS)  $^ -o $@ 

strsignal:strsignal.c
	$(CC) $(CFLAGS)  $^ -o $@ 

clean:
	$(RM)  $(TARGET) *.o
