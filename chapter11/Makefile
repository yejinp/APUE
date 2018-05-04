CC=gcc
RM=rm -f

CFLAGS=-g
CFLAGS+=-lpthread

TARGET=figure11_2
TARGET+=figure11_3
TARGET+=figure11_4
TARGET+=figure11_5
TARGET+=pthread_equal
TARGET+=pthread_detach

OBJECTS=figure11_10.o
OBJECTS+=figure11_11.o
OBJECTS+=figure11_12.o

all: $(TARGET) $(OBJECTS);

figure11_2: figure11_2.c
	$(CC) $(CFLAGS)  $^ -o $@

figure11_3: figure11_3.c
	$(CC) $(CFLAGS)  $^ -o $@

figure11_4: figure11_4.c
	$(CC) $(CFLAGS)  $^ -o $@

figure11_5: figure11_5.c
	$(CC) $(CFLAGS)  $^ -o $@

figure11_10.o: figure11_10.c
	$(CC) $(CFLAGS) -c  $^ -o $@

figure11_11.o: figure11_11.c
	$(CC) $(CFLAGS) -c $^ -o $@

figure11_12.o: figure11_12.c
	$(CC) $(CFLAGS) -c $^ -o $@

pthread_detach: pthread_detach.c
	$(CC) $(CFLAGS)  $^ -o $@

pthread_equal: pthread_equal.c
	$(CC) $(CFLAGS)  $^ -o $@

clean:
	$(RM) $(TARGET) $(OBJECTS)
