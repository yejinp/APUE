CC=gcc
CFLAGS=-g

RM=rm -f

TARGET=figure15_5
TARGET+=figure15_6
TARGET+=figure15_11
TARGET+=figure15_14
TARGET+=figure15_15
TARGET+=figure15_17
TARGET+=figure15_18
TARGET+=figure15_19

OBJECTS=figure15_7.o
OBJECTS=figure15_12.o

all: $(TARGET) $(OBJECTS);

figure15_5: figure15_5.c
	$(CC) $(CFLAGS)  $^ -o $@ 

figure15_6: figure15_6.c
	$(CC) $(CFLAGS)  $^ -o $@ 

figure15_11: figure15_11.c
	$(CC) $(CFLAGS)  $^ -o $@ 

figure15_14: figure15_14.c
	$(CC) $(CFLAGS)  $^ -o $@ 

figure15_15: figure15_15.c
	$(CC) $(CFLAGS)  $^ -o $@ 

figure15_17: figure15_17.c
	$(CC) $(CFLAGS)  $^ -o $@ 

figure15_18: figure15_18.c
	$(CC) $(CFLAGS)  $^ -o $@ 

figure15_19: figure15_19.c
	$(CC) $(CFLAGS)  $^ -o $@ 

figure15_7.o: figure15_7.c
	$(CC) $(CFLAGS)  $^ -c -o $@ 

figure15_12.o: figure15_12.c
	$(CC) $(CFLAGS)  $^ -c -o $@ 

clean:
	$(RM) $(TARGET) $(OBJECTS)
