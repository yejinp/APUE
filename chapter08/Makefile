CC=gcc
RM=rm -f

CFLAGS=-g

TARGET=figure8_1
TARGET+=nice
TARGET+=getlogin
TARGET+=figure8_3
TARGET+=figure8_6
TARGET+=figure8_8
TARGET+=figure8_11
TARGET+=figure8_12
TARGET+=figure8_16
TARGET+=figure8_17
TARGET+=figure8_20
TARGET+=figure8_23
TARGET+=figure8_24
TARGET+=figure8_25
TARGET+=figure8_28
TARGET+=figure8_29
TARGET+=figure8_30

OBJECTS=figure8_5.o
OBJECTS+=figure8_22.o

all: $(TARGET) $(OBJECTS);

getlogin: getlogin.c
	$(CC) $(CFLAGS)  $^ -o $@

nice: nice.c
	$(CC) $(CFLAGS)  $^ -o $@

figure8_1: figure8_1.c
	$(CC) $(CFLAGS)  $^ -o $@

figure8_3: figure8_3.c
	$(CC) $(CFLAGS)  $^ -o $@

figure8_6: figure8_6.c figure8_5.o
	$(CC) $(CFLAGS)  $^ -o $@

figure8_8: figure8_8.c
	$(CC) $(CFLAGS)  $^ -o $@

figure8_11: figure8_11.c
	$(CC) $(CFLAGS)  $^ -o $@

figure8_12: figure8_12.c
	$(CC) $(CFLAGS)  $^ -o $@

figure8_16: figure8_16.c
	$(CC) $(CFLAGS)  $^ -o $@

figure8_17: figure8_17.c
	$(CC) $(CFLAGS)  $^ -o $@

figure8_20: figure8_20.c
	$(CC) $(CFLAGS)  $^ -o $@

figure8_23: figure8_23.c figure8_5.o figure8_22.o
	$(CC) $(CFLAGS)  $^ -o $@

figure8_24: figure8_24.c figure8_5.o
	$(CC) $(CFLAGS)  $^ -o $@

figure8_25: figure8_25.c
	$(CC) $(CFLAGS)  $^ -o $@

figure8_28: figure8_28.c
	$(CC) $(CFLAGS)  $^ -o $@

figure8_29: figure8_29.c
	$(CC) $(CFLAGS)  $^ -o $@

figure8_30: figure8_30.c figure8_5.o
	$(CC) $(CFLAGS)  $^ -o $@

figure8_5.o: figure8_5.c
	$(CC) $(CFLAGS)  $^ -c -o $@

figure8_22.o: figure8_22.c
	$(CC) $(CFLAGS)  $^ -c -o $@

clean:
	$(RM) $(TARGET) $(OBJECTS)
