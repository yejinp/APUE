CC=gcc
RM=rm -f

CFLAGS=-g

OBJECTS=

TARGET=figure10_2
TARGET+=figure10_5
TARGET+=figure10_6
TARGET+=figure10_7
TARGET+=figure10_8
TARGET+=figure10_9
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

figure10_7:figure10_7.c
	$(CC) $(CFLAGS)  $^ -o $@ 

figure10_8:figure10_8.c
	$(CC) $(CFLAGS)  $^ -o $@ 

figure10_9:figure10_9.c
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
